#pragma once
#pragma warning(push)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#ifdef _WIN32
#include<ntddk.h>
#include<wdm.h>
#include <ntimage.h>
#include <intrin.h>
#else
#include "win_compat.h"
#endif
#pragma warning(pop)
#define HUN_NANO_SEC_TO_SEC 10000000

void kernel_sleep(long time_interval_sec);
PVOID kernel_malloc(size_t size);
BOOLEAN kernel_compare_memory(PBYTE s1, PBYTE s2);
BOOLEAN kernel_compare_unicode_strings(PWCHAR s1, PWCHAR s2);
void kernel_memory_move(PVOID dst, PVOID src, size_t size);

