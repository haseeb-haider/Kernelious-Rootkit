#pragma once
#ifdef _WIN32
// On Windows use actual headers
#else
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>
#include <stdlib.h>
#include <inttypes.h>

typedef uint8_t UCHAR;
typedef int8_t CHAR;
typedef unsigned short USHORT;
typedef uint16_t UINT16;
typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef unsigned long ULONG;
typedef uint64_t ULONG64;
typedef uint64_t ULONGLONG;

typedef int BOOLEAN;
#define TRUE 1
#define FALSE 0

typedef void* PVOID;
typedef unsigned char* PBYTE;
typedef wchar_t* PWCHAR;
typedef wchar_t* PCWSTR;
typedef void* PEPROCESS;
typedef void* PKPROCESS;
typedef void* HANDLE;
typedef void* PDRIVER_OBJECT;
typedef void* PFILE_OBJECT;

typedef size_t SIZE_T;

typedef int NTSTATUS;

typedef long LONG;
typedef unsigned int UINT;
typedef uintptr_t ULONG_PTR;

typedef ULONG* PULONG;
typedef int32_t* PINT32;
typedef uint32_t* PUINT32;
typedef uint64_t* PUINT64;
typedef uint64_t* PULONGLONG;
typedef long long* PLONG64;
typedef uint64_t* PULONG64;
typedef unsigned char* PUCHAR;
typedef char* PCHAR;
typedef wchar_t WCHAR;
typedef char CCHAR;
typedef long long INT64;

typedef struct _UNICODE_STRING { USHORT Length; USHORT MaximumLength; PWCHAR Buffer; } UNICODE_STRING, *PUNICODE_STRING;
typedef struct _LIST_ENTRY { struct _LIST_ENTRY* Flink; struct _LIST_ENTRY* Blink; } LIST_ENTRY, *PLIST_ENTRY;
typedef int FILE_INFORMATION_CLASS;

typedef struct _LARGE_INTEGER { long long QuadPart; } LARGE_INTEGER;

typedef struct _IO_STATUS_BLOCK { NTSTATUS Status; ULONG_PTR Information; } IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;

typedef void (*PIO_APC_ROUTINE)(void);

#define NTSYSAPI
#define IN
#define OUT
#define WINAPI

#define DbgPrint(...) ((void)0)
#define UNREFERENCED_PARAMETER(x) ((void)(x))

#define FileDirectoryInformation 1
#define FileFullDirectoryInformation 2
#define FileBothDirectoryInformation 3
#define FileNamesInformation 4
#define FileIdBothDirectoryInformation 5
#define FileIdFullDirectoryInformation 6
#define STATUS_NO_MORE_FILES 0x80000006

static inline void RtlInitUnicodeString(void* s, const wchar_t* w) { (void)s; (void)w; }
static inline void* MmGetSystemRoutineAddress(void* p) { (void)p; return NULL; }
static inline void* IoGetCurrentProcess(void) { return NULL; }
static inline void* ZwCurrentProcess(void) { return NULL; }
static inline void* PsGetCurrentProcess(void) { return NULL; }
static inline HANDLE PsGetCurrentProcessId(void) { return NULL; }
static inline NTSTATUS ZwQueryKey(void) { return 0; }
static inline NTSTATUS ZwProtectVirtualMemory(HANDLE ProcessHandle, PVOID* BaseAddress, SIZE_T* NumberOfBytesToProtect, ULONG NewAccessProtection, PULONG OldAccessProtection) { (void)ProcessHandle; (void)BaseAddress; (void)NumberOfBytesToProtect; (void)NewAccessProtection; (void)OldAccessProtection; return 0; }
static inline void KeDelayExecutionThread(int a, BOOLEAN b, void* p) { (void)a; (void)b; (void)p; }
static inline void* ExAllocatePool2(int poolType, size_t size, int tag) { (void)poolType; (void)tag; return malloc(size); }
static inline void ExFreePool(void* buffer_ptr) { free(buffer_ptr); }

#define NonPagedPool 0
#define PAGE_EXECUTE_READWRITE 0
#define KernelMode 0

static inline unsigned long long __readcr3(void) { return 0; }
static inline unsigned long long __readcr4(void) { return 0; }
static inline void __writecr4(unsigned long long v) { (void)v; }
static inline unsigned long long __readcr0(void) { return 0; }
static inline void __writecr0(unsigned long long v) { (void)v; }
static inline unsigned long long __readmsr(unsigned int m) { (void)m; return 0; }
static inline void __writemsr(unsigned int m, unsigned long long v) { (void)m; (void)v; }
static inline void __sidt(void* dest) { (void)dest; }
static inline void _disable(void) { }
static inline void _enable(void) { }

#define STATUS_SUCCESS 0
#define STATUS_FAILED_DRIVER_ENTRY 0xC0000001

#endif
