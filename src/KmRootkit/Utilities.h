#pragma once
#ifdef _WIN32
#include<ntddk.h>
#include<wdm.h>
#include <ntimage.h>
#include <intrin.h>
#else
#include "win_compat.h"
#endif
#define HUN_NANO_SEC_TO_SEC 10000000

void kernel_sleep(long time_interval_sec);
PVOID kernel_malloc(size_t size);
BOOLEAN kernel_compare_memory(PBYTE s1, PBYTE s2);
BOOLEAN kernel_compare_unicode_strings(PWCHAR s1, PWCHAR s2);
void kernel_memory_move(PVOID dst, PVOID src, size_t size);

