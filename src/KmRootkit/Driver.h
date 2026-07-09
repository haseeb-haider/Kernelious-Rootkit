#pragma once
#pragma warning(push)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include<ntddk.h>
#include<wdm.h>
#include <intrin.h>
#else
#include "win_compat.h"
#endif
#pragma warning(pop)
#include "Process.h"
#include "SSDTHook.h"
#include "IDTHook.h"
#include "SYSENTERHook.h"
#include "PagetableHook.h"
#include "Utilities.h"
#include "File.h"



NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pUnicodeString);
NTSTATUS DriverUnload(PDRIVER_OBJECT pDriverObject);
void x64_deprotect();
void x64_protect();
