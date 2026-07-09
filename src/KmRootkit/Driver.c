#pragma warning(disable: 4100)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#include <ntddk.h>
#include <wdm.h>
#include "Driver.h"
#include "PagetableHook.h"

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING RegistryPath)
{
	x64_deprotect();
	get_pml4_base_address_cr3();
	get_pml4_base_address_eprocess();
	parse_virtual_address((PVOID)0xfffff8034ac05000);
	return STATUS_SUCCESS;
}

NTSTATUS DriverUnload(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("Driver unloaded, deleting symbolic links and devices\n");
	x64_protect();

	return STATUS_SUCCESS;
}


void x64_deprotect()
{
	_disable();
	__writecr0(__readcr0() & (~(1 << 16)));
	_enable();
}


void x64_protect()
{
	_disable();
	__writecr0(__readcr0() | (1 << 16));
	_enable();
}

