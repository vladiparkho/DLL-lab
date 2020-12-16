#pragma once

#define WIN32_LEAN_AND_MEAN             // Исключите редко используемые компоненты из заголовков Windows
// Файлы заголовков Windows
#include <windows.h>
#pragma once
#ifdef DLL2_EXPORTS
#define DLL2_API __declspec(dllexport)
#else
#define DLL2_API __declspec(dllimport)
#endif
extern "C" DLL2_API BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD * pdwBytesWritten);
extern "C" DLL2_API BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD * pdwBytesWritten);
extern "C" DLL2_API VOID Execute();