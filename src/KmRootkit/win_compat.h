#pragma once
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>
#include <stdlib.h>
#include <inttypes.h>

#ifndef UCHAR
typedef uint8_t UCHAR;
#endif
#ifndef CHAR
typedef int8_t CHAR;
#endif
#ifndef USHORT
typedef unsigned short USHORT;
#endif
#ifndef UINT16
typedef uint16_t UINT16;
#endif
#ifndef UINT32
typedef uint32_t UINT32;
#endif
#ifndef UINT64
typedef uint64_t UINT64;
#endif
#ifndef ULONG
typedef unsigned long ULONG;
#endif
#ifndef ULONG64
typedef uint64_t ULONG64;
#endif
#ifndef ULONGLONG
typedef uint64_t ULONGLONG;
#endif

#ifndef BOOLEAN
typedef int BOOLEAN;
#define TRUE 1
#define FALSE 0
#endif

#ifndef PVOID
typedef void* PVOID;
#endif
#ifndef PBYTE
typedef unsigned char* PBYTE;
#endif
#ifndef PWCHAR
typedef wchar_t* PWCHAR;
#endif
#ifndef PCWSTR
typedef const wchar_t* PCWSTR;
#endif
#ifndef PEPROCESS
typedef void* PEPROCESS;
#endif
#ifndef PKPROCESS
typedef void* PKPROCESS;
#endif
#ifndef HANDLE
typedef void* HANDLE;
#endif
#ifndef PDRIVER_OBJECT
typedef void* PDRIVER_OBJECT;
#endif
#ifndef PFILE_OBJECT
typedef void* PFILE_OBJECT;
#endif

#ifndef SIZE_T
typedef size_t SIZE_T;
#endif

#ifndef NTSTATUS
typedef int NTSTATUS;
#endif

#ifndef LONG
typedef long LONG;
#endif
#ifndef UINT
typedef unsigned int UINT;
#endif
#ifndef ULONG_PTR
typedef uintptr_t ULONG_PTR;
#endif

#ifndef PULONG
typedef ULONG* PULONG;
#endif
#ifndef PINT32
typedef int32_t* PINT32;
#endif
#ifndef PUINT32
typedef uint32_t* PUINT32;
#endif
#ifndef PUINT64
typedef uint64_t* PUINT64;
#endif
#ifndef PULONGLONG
typedef uint64_t* PULONGLONG;
#endif
#ifndef PLONG64
typedef long long* PLONG64;
#endif
#ifndef PULONG64
typedef uint64_t* PULONG64;
#endif
#ifndef PUCHAR
typedef unsigned char* PUCHAR;
#endif
#ifndef PCHAR
typedef char* PCHAR;
#endif
#ifndef WCHAR
typedef wchar_t WCHAR;
#endif
#ifndef CCHAR
typedef char CCHAR;
#endif
#ifndef INT64
typedef long long INT64;
#endif

#ifndef _UNICODE_STRING_DEFINED
#define _UNICODE_STRING_DEFINED
typedef struct _UNICODE_STRING { USHORT Length; USHORT MaximumLength; PWCHAR Buffer; } UNICODE_STRING, *PUNICODE_STRING;
#endif
#ifndef _LIST_ENTRY_DEFINED
#define _LIST_ENTRY_DEFINED
typedef struct _LIST_ENTRY { struct _LIST_ENTRY* Flink; struct _LIST_ENTRY* Blink; } LIST_ENTRY, *PLIST_ENTRY;
#endif

#ifndef FILE_INFORMATION_CLASS
typedef int FILE_INFORMATION_CLASS;
#endif

#ifndef _LARGE_INTEGER_DEFINED
#define _LARGE_INTEGER_DEFINED
typedef struct _LARGE_INTEGER { long long QuadPart; } LARGE_INTEGER;
#endif

#ifndef _IO_STATUS_BLOCK_DEFINED
#define _IO_STATUS_BLOCK_DEFINED
typedef struct _IO_STATUS_BLOCK { NTSTATUS Status; ULONG_PTR Information; } IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
#endif

#ifndef PIO_APC_ROUTINE
typedef void (*PIO_APC_ROUTINE)(void);
#endif

#ifndef NTSYSAPI
#define NTSYSAPI
#endif
#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef WINAPI
#define WINAPI
#endif
#ifndef NULL
#define NULL 0
#endif

#ifndef DbgPrint
#define DbgPrint(...) ((void)0)
#endif
#ifndef UNREFERENCED_PARAMETER
#define UNREFERENCED_PARAMETER(x) ((void)(x))
#endif

#ifndef FileDirectoryInformation
#define FileDirectoryInformation 1
#endif
#ifndef FileFullDirectoryInformation
#define FileFullDirectoryInformation 2
#endif
#ifndef FileBothDirectoryInformation
#define FileBothDirectoryInformation 3
#endif
#ifndef FileNamesInformation
#define FileNamesInformation 4
#endif
#ifndef FileIdBothDirectoryInformation
#define FileIdBothDirectoryInformation 5
#endif
#ifndef FileIdFullDirectoryInformation
#define FileIdFullDirectoryInformation 6
#endif
#ifndef STATUS_NO_MORE_FILES
#define STATUS_NO_MORE_FILES 0x80000006
#endif

#ifndef RtlInitUnicodeString
static inline void RtlInitUnicodeString(void* s, const wchar_t* w) { (void)s; (void)w; }
#endif
#ifndef MmGetSystemRoutineAddress
static inline void* MmGetSystemRoutineAddress(void* p) { (void)p; return NULL; }
#endif
#ifndef IoGetCurrentProcess
static inline void* IoGetCurrentProcess(void) { return NULL; }
#endif
#ifndef ZwCurrentProcess
static inline void* ZwCurrentProcess(void) { return NULL; }
#endif
#ifndef PsGetCurrentProcess
static inline void* PsGetCurrentProcess(void) { return NULL; }
#endif
#ifndef PsGetCurrentProcessId
static inline HANDLE PsGetCurrentProcessId(void) { return NULL; }
#endif
#ifndef ZwQueryKey
static inline NTSTATUS ZwQueryKey(void) { return 0; }
#endif
#ifndef ZwProtectVirtualMemory
static inline NTSTATUS ZwProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, SIZE_T* NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection) { (void)ProcessHandle; (void)BaseAddress; (void)NumberOfBytesToProtect; (void)NewAccessProtection; (void)OldAccessProtection; return 0; }
#endif
#ifndef KeDelayExecutionThread
static inline void KeDelayExecutionThread(int a, BOOLEAN b, void* p) { (void)a; (void)b; (void)p; }
#endif
#ifndef ExAllocatePool2
static inline void* ExAllocatePool2(int poolType, size_t size, int tag) { (void)poolType; (void)tag; return malloc(size); }
#endif
#ifndef ExFreePool
static inline void ExFreePool(void* buffer_ptr) { free(buffer_ptr); }
#endif

#ifndef NonPagedPool
#define NonPagedPool 0
#endif
#ifndef PAGE_EXECUTE_READWRITE
#define PAGE_EXECUTE_READWRITE 0
#endif
#ifndef KernelMode
#define KernelMode 0
#endif
#ifndef POOL_FLAG_NON_PAGED
#define POOL_FLAG_NON_PAGED 0x0000000000000001ULL
#endif

#ifndef _MDL_DEFINED
#define _MDL_DEFINED
typedef struct _MDL {
	struct _MDL *Next;
	SHORT Size;
	SHORT MdlFlags;
	ULONGLONG StartVa;
	ULONG ByteCount;
	ULONG ByteOffset;
} MDL, *PMDL;
#endif

#ifndef __readcr3
static inline unsigned long long __readcr3(void) { return 0; }
#endif
#ifndef __readcr4
static inline unsigned long long __readcr4(void) { return 0; }
#endif
#ifndef __writecr4
static inline void __writecr4(unsigned long long v) { (void)v; }
#endif
#ifndef __readcr0
static inline unsigned long long __readcr0(void) { return 0; }
#endif
#ifndef __writecr0
static inline void __writecr0(unsigned long long v) { (void)v; }
#endif
#ifndef __readmsr
static inline unsigned long long __readmsr(unsigned int m) { (void)m; return 0; }
#endif
#ifndef __writemsr
static inline void __writemsr(unsigned int m, unsigned long long v) { (void)m; (void)v; }
#endif
#ifndef __sidt
static inline void __sidt(void* dest) { (void)dest; }
#endif
#ifndef _disable
static inline void _disable(void) { }
#endif
#ifndef _enable
static inline void _enable(void) { }
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS 0
#endif
#ifndef STATUS_FAILED_DRIVER_ENTRY
#define STATUS_FAILED_DRIVER_ENTRY 0xC0000001
#endif
#ifndef STATUS_NO_SUCH_FILE
#define STATUS_NO_SUCH_FILE 0xC000000F
#endif
#ifndef STANDARD_RIGHTS_REQUIRED
#define STANDARD_RIGHTS_REQUIRED 0x000F0000
#endif

#ifndef UNREACHABLE
#define UNREACHABLE() { __asm__("ud2"); }
#endif
#ifndef __pragma
#define __pragma(x)
#endif
#ifndef __declspec
#define __declspec(x)
#endif
