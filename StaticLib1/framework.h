#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <windows.h>

void ListDLLs(LPCSTR path, LPCSTR* dll_list, size_t* ret_dll_count);
