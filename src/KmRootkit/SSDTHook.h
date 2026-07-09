#pragma once
#pragma warning(push)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#include<ntddk.h>
#include<wdm.h>
#include <ntimage.h>
#include <intrin.h>
#pragma warning(pop)
#define SDT_SYMBOL L"KeServiceDescriptorTable"
#define SSDT_ENTRY_SIZE 4
#define PATTERN {0x48,0x89,0xa3,0x90,0x00,0x00,0x00,0x8b,0xf8,0xc1,0xef,0x07};
#define PATTERN_SIZE 12
#define MAX_DISTANCE_RVA 0xfffffff
#define SHELLCODE_SIZE 12	
#define SDT_SYMBOL_OFFSET 0X14
#define ARGUMENTS_VIA_REGISTERS_COUNT 4

extern PVOID nt_version_function_ptr;

typedef NTSYSAPI PVOID (*prtl_pc_to_file_header)(PVOID PcValue, PVOID* BaseOfImage);


typedef struct system_descriptor_table
{
	PLONG64 system_service_descriptor_table;
	PLONG64 null_padding1;
	PLONG64 null_padding2;
	PLONG64 params;
}system_descriptor_table, *psystem_descriptor_table;




int get_syscall_number(PVOID function_pointer);

PVOID get_function_base_address(PCWSTR func_name);

PVOID get_ntoskrnl_base_address();

BOOLEAN is_address_start_of_pattern(PVOID address);

PVOID get_ki_systen_service_start(PVOID ntoskrnl_image_base);

PVOID get_sdt_address(PVOID ki_systen_service_start_address);

PVOID get_ssdt_base_address(PVOID sdt_address);

PVOID get_nt_version_function(PVOID ssdt_base_address, int syscall_number);


void write_trampoline(PVOID hooking_function, PVOID hooked_memory);

void restore_nt_function(PVOID nt_version_function);

BOOLEAN hook_ssdt_with_code_cave(PCWSTR hooked_function_name, PVOID hooking_function);

extern NTSTATUS ZwProtectVirtualMemory(IN HANDLE ProcessHandle, IN PVOID* BaseAddress, IN SIZE_T* NumberOfBytesToProtect, IN ULONG NewAccessProtection, OUT PULONG OldAccessProtection);