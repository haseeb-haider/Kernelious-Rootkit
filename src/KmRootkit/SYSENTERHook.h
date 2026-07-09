#pragma once
#pragma warning(push)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#include<ntddk.h>
#include<wdm.h>
#include <intrin.h>
#pragma warning(pop)
#define STAR_NUMBER 0xC0000081
#define LSTAR_NUMBER 0xC0000082
#define CSTAR_NUMBER 0xC0000083
#define SFMASK_NUMBER 0xC0000084


typedef struct sysenter_msrs {
	ULONG64 STAR;
	ULONG64 LSTAR;
	ULONG64 CSTAR;
	ULONG64 SFMASK;
}sysenter_msrs, *psysenter_msrs;

typedef VOID (*pSysenterHandler)(VOID);

sysenter_msrs get_sysenter_msrs();
void print_sysenter_msrs();
void hook_sysenter_instruction(PBYTE hooking_function);
void hooking_function_sysenter();