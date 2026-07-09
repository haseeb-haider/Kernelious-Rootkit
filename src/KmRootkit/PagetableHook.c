#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#include "PagetableHook.h"

void x64_turn_smep_off()
{
	_disable();
    __writecr4(__readcr4() & (~(1 << SMEP_BIT_INDEX)));
	_enable();
}

void x64_turn_smep_on()
{
	_disable();
	__writecr4(__readcr4() | (1<<SMEP_BIT_INDEX));
	_enable();
}

void x64_turn_smap_off()
{
	_disable();
	__writecr4(__readcr4() & (~(1 << SMAP_BIT_INDEX)));
	_enable();
}

void x64_turn_smap_on()
{
	_disable();
	__writecr4(__readcr4() | (1 << SMAP_BIT_INDEX));
	_enable();
}

ULONGLONG get_pml4_base_address_cr3()
{
	ULONGLONG CR3 = __readcr3();
	CR3 >>= 12;
	DbgPrint("cr3 shred: %p", CR3);
	CR3 &= CR3_ZERO_MASK;
	DbgPrint("CR3 is: %p\n", CR3);
	return CR3;
}


ULONGLONG get_pml4_base_address_eprocess()
{
	PEPROCESS current_process_eprocess = IoGetCurrentProcess();
	PKPROCESS current_process_kprocess = (PKPROCESS)current_process_eprocess;
	DbgPrint("kprocess is at %p\n", current_process_kprocess);
	ULONGLONG pml4_base_address = *((PULONGLONG)(((PBYTE)current_process_kprocess + PAGE_DIRECTORY_TABLE_OFFSET)));
	DbgPrint("pml4 is at: %p\n", pml4_base_address);
	return pml4_base_address;

}

void parse_virtual_address(PVOID virtual_address)
{
	virtual_address_parts* parts = (virtual_address_parts*)virtual_address;
	DbgPrint("Virtual Address: %p\n", virtual_address);
	DbgPrint("Sign Extended: %d\n", parts->sign_extended);
	DbgPrint("PML4 Offset: %d\n", parts->pml4_offset);
	DbgPrint("Page Directory Pointer Offset: %d\n", parts->page_directory_pointer_offset);
	DbgPrint("Page Directory Offset: %d\n", parts->page_directory_offset);
	DbgPrint("Page Table Offset: %d\n", parts->page_table_offset);
	DbgPrint("Physical Frame Offset: %d\n", parts->physical_frame_offset);
}
