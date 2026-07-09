#pragma once
#pragma warning(push)
#pragma warning(disable: 4005)  // Suppress macro redefinition warnings
#pragma warning(disable: 4668)  // Suppress undefined preprocessor macro warnings
#pragma warning(disable: 4820)  // Suppress padding warnings
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Ntddk.h>
#include <wdm.h>
#include <intrin.h>
#else
#include "win_compat.h"
#endif
#pragma warning(pop)

#pragma pack(push,1)
typedef struct gdt_entry {
	UINT16 limit_1;
	UINT16 base_1;
	UCHAR base_2;
	UCHAR access_byte;
	UCHAR limit_2 : 4;
	UCHAR flags : 4;
	UCHAR base_3;
	UINT32 base_4;
	UINT32 reserved;
}gdt_entry, *pgdt_entry;
#pragma pack(pop)

