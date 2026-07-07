#pragma once
#include<wdm.h>
#include<ntddk.h>
#include <intrin.h>
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
