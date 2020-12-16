#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#pragma once
#ifdef DLL3_EXPORTS
#define DLL3_API __declspec(dllexport)
#else
#define DLL3_API __declspec(dllimport)
#endif

//extern "C" DLL2_API BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD * pdwBytesWritten);
//extern "C" DLL2_API BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD * pdwBytesWritten);
extern "C" DLL3_API VOID Execute();