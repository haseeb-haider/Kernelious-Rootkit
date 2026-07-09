#pragma warning(disable: 4100)
#pragma warning(disable: 4820 4619 4668)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#include <ntddk.h>
#include "SSDTHook.h"

char original_nt_function_bytes[12] = { 0 };
PVOID nt_version_function_ptr = NULL;

int get_syscall_number(PVOID function_pointer)
{
    PUCHAR func = (PUCHAR)function_pointer;
    return (int)*(PINT32)((PUCHAR)(((PUINT32)func) + 5) + 1);
}

PVOID get_function_base_address(PCWSTR func_name)
{
    UNICODE_STRING func_unicode_string = { 0 };
    RtlInitUnicodeString(&func_unicode_string, func_name);

    return (PVOID)MmGetSystemRoutineAddress(&func_unicode_string);
}

PVOID get_ntoskrnl_base_address()
{
    PVOID ntoskrnl_base_address;
    UNICODE_STRING pc_to_file_header_string;

    RtlInitUnicodeString(&pc_to_file_header_string, L"RtlPcToFileHeader");
    prtl_pc_to_file_header rtl_pc_to_file_header_function = (prtl_pc_to_file_header)MmGetSystemRoutineAddress(&pc_to_file_header_string);
    rtl_pc_to_file_header_function((PVOID)&ZwQueryKey, &ntoskrnl_base_address);

    return ntoskrnl_base_address;
}

BOOLEAN is_address_start_of_pattern(PVOID address)
{
    PUCHAR addr = (PUCHAR)address;
    char pattern[] = PATTERN;
    for (int i = 0; i < sizeof(pattern); i++)
    {
        if ((char)*(pattern + i) != (char)*(addr + i))
        {
            return FALSE;
        }
    }
    return TRUE;
}

PVOID get_ki_systen_service_start(PVOID ntoskrnl_image_base)
{
    PBYTE base = (PBYTE)ntoskrnl_image_base;
    int i = 0;
    while (TRUE)
    {
        if (is_address_start_of_pattern((PVOID)(base + i)))
        {
            return (PVOID)(base + i);
        }
        i++;
    }
}

PVOID get_sdt_address(PVOID ki_systen_service_start_address)
{
    PUCHAR base = (PUCHAR)ki_systen_service_start_address;
    PUCHAR lea_r10_sdt_instruction_pointer = (PUCHAR)(base + SDT_SYMBOL_OFFSET);
    int* offset_pointer = (int*)(lea_r10_sdt_instruction_pointer + 3);
    int offset = *offset_pointer;

PUCHAR next_instruction_irp_value = lea_r10_sdt_instruction_pointer + 7;
	PUCHAR sdt_address = next_instruction_irp_value + offset;

    return (PVOID)sdt_address;
}

PVOID get_ssdt_base_address(PVOID sdt_address)
{
    psystem_descriptor_table sdt = (psystem_descriptor_table)sdt_address;
    return (PVOID)sdt->system_service_descriptor_table;
}

PVOID get_nt_version_function(PVOID ssdt_base_address, int syscall_number)
{
    PUCHAR base = (PUCHAR)ssdt_base_address;
    int ssdt_entry_offset = *((int*)(base + 4 * syscall_number));
    nt_version_function_ptr = (PVOID)(base + (ssdt_entry_offset >> 4));
    return nt_version_function_ptr;
}

void write_trampoline(PVOID hooking_function, PVOID hooked_memory)
{
    DbgPrint("Building Trampoline...\n");
    PUCHAR hooked = (PUCHAR)hooked_memory;
    PUCHAR hook = (PUCHAR)hooking_function;
    RtlCopyMemory(original_nt_function_bytes, hooked, 12);
    *(hooked) = 0x48;
    *(hooked + 1) = 0xb8;
    PUCHAR func_ptr = hook;
    RtlCopyMemory(hooked + 2, &func_ptr, sizeof(func_ptr));
    *(hooked + 10) = 0xff;
    *(hooked + 11) = 0xe0;
}

void restore_nt_function(PVOID nt_version_function)
{
    RtlCopyMemory(nt_version_function, original_nt_function_bytes, 12);
}

BOOLEAN is_valid_code_cave_code_segment(PVOID start_address)
{
    PUCHAR start = (PUCHAR)start_address;
    for (int i = 0; i < SHELLCODE_SIZE; i++)
    {
        if (*(start + i) != 0x90 && *(start + i) != 0xcc)
        {
            return FALSE;
        }
    }
    return TRUE;
}

BOOLEAN is_valid_code_cave_data_segment(PVOID start_address)
{
    PUINT64 zero_memory_segment = (PUINT64)start_address;
    for (int i = 0; i < 10; i++)
    {
        if (*(zero_memory_segment + i) != 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

PVOID scan_for_code_cave(PVOID start_address, ULONG limit)
{
    PUCHAR current_address = (PUCHAR)start_address;
    PUCHAR last_address = (PUCHAR)((current_address - SHELLCODE_SIZE - 80) + limit);
    while (current_address < last_address)
    {
        if (is_valid_code_cave_code_segment(current_address))
        {
            DbgPrint("valid code cave found in code segment: %p", current_address);
            return (PVOID)current_address;
        }
        else if (is_valid_code_cave_data_segment(current_address))
        {
            DbgPrint("valid code cave found in data segment: %p", current_address);
            return (PVOID)current_address;
        }
        current_address++;
    }
    return NULL;
}

BOOLEAN hook_nt_function(PCWSTR hooked_function_name, PVOID hooking_function)
{
    PVOID nt_function_address = get_nt_version_function(
        get_ssdt_base_address(get_sdt_address(get_ki_systen_service_start(get_ntoskrnl_base_address()))),
        get_syscall_number(get_function_base_address(hooked_function_name)));
    write_trampoline(nt_function_address, hooking_function);
    return TRUE;
}

UINT32 calcultae_ssdt_entry(PVOID ssdt_base_address, PVOID code_cave_address, UINT32 args_number)
{
    UINT32 rva_to_code_cave = (UINT32)((PUCHAR)code_cave_address - (PUCHAR)ssdt_base_address);
    UINT32 valid_ssdt_entry = rva_to_code_cave << 4;
    valid_ssdt_entry |= (args_number - ARGUMENTS_VIA_REGISTERS_COUNT);
    DbgPrint("ssdt entry: %x \n", valid_ssdt_entry);
    return valid_ssdt_entry;
}

BOOLEAN hook_ssdt_with_code_cave(PCWSTR hooked_function_name, PVOID hooking_function)
{
    PVOID ssdt_base_address = get_ssdt_base_address(get_sdt_address(get_ki_systen_service_start(get_ntoskrnl_base_address())));
    int syscall_number = get_syscall_number(get_function_base_address(hooked_function_name));
    get_nt_version_function(ssdt_base_address, syscall_number);

    PUINT32 ssdt_entry_ptr = (PUINT32)((PUCHAR)ssdt_base_address + (SSDT_ENTRY_SIZE * syscall_number));
    PVOID code_cave_address = scan_for_code_cave(ssdt_base_address, MAX_DISTANCE_RVA);
    if (code_cave_address == NULL)
    {
        return FALSE;
    }

    UINT32 fixed_ssdt_entry = calcultae_ssdt_entry(ssdt_base_address, code_cave_address, 11);
    *(ssdt_entry_ptr) = fixed_ssdt_entry;

    SIZE_T patched_bytes = 0x1000;
    PVOID base_address = code_cave_address;
    ULONG old_protection = 0;
    NTSTATUS page_protection_status = ZwProtectVirtualMemory(ZwCurrentProcess(), &base_address, &patched_bytes, PAGE_EXECUTE_READWRITE, &old_protection);
    UNREFERENCED_PARAMETER(page_protection_status);
    write_trampoline(hooking_function, code_cave_address);

    return TRUE;
}
