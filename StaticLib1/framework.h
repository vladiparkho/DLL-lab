#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include <vector>
#include <windows.h>

BOOL ListDLLs(LPCSTR path, std::vector<LPSTR>& dll_list);
