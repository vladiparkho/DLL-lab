#include <stdbool.h>
#include "pch.h"
#include <tchar.h>
#include <strsafe.h>
#include <stdlib.h>

bool IsDLL(LPSTR filename) {

	HANDLE hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hFileMapping == NULL)
		return false;

	LPVOID lpFileBase = MapViewOfFile(hFileMapping, FILE_MAP_READ, 0, 0, 0);

	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)lpFileBase;

	if (pDosHeader == NULL || pDosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return false;

	PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader + (DWORD)pDosHeader->e_lfanew);

	bool result = false;
	if ((pNTHeader->FileHeader.Characteristics & IMAGE_FILE_DLL))
		result = true;

	UnmapViewOfFile(lpFileBase);
	CloseHandle(hFileMapping);
	CloseHandle(hFile);

	return result;
}

void ListDLLs(LPCSTR path, LPCSTR* dll_list, size_t* ret_dll_count) {
	TCHAR szDir[MAX_PATH];
	strcpy_s(szDir, MAX_PATH, path);
	strcat_s(szDir, MAX_PATH, TEXT("\\*"));

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile(szDir, &ffd);
	if (INVALID_HANDLE_VALUE == hFind) {
		_tprintf(TEXT("Error finding first file\n"));
		return;
	}

	bool was_dll_count_allocated = false;
	if (ret_dll_count == NULL) {
		ret_dll_count = (size_t*)malloc(sizeof(size_t));
		if (ret_dll_count == NULL) {
			perror("Couldn't allocate ret_dll_count");
			return;
		}
		*ret_dll_count = 0;
		was_dll_count_allocated = true;
	}

	do {
		LPSTR newPath = (char*)malloc(sizeof(char) * MAX_PATH);
		if (newPath == NULL) {
			perror("Couldn't allocate newPath");
			return;
		}
		strcpy_s(newPath, MAX_PATH, path);
		strcat_s(newPath, MAX_PATH, TEXT("\\"));
		strcat_s(newPath, MAX_PATH, TEXT(ffd.cFileName));
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if ((strcmp(ffd.cFileName, ".") == 0) || (strcmp(ffd.cFileName, "..") == 0))
				continue;
			ListDLLs(newPath, dll_list, ret_dll_count);
		}
		else {
			if (IsDLL(newPath)) {
				if (dll_list != NULL) {
					dll_list[*ret_dll_count] = newPath;
				}
				if (ret_dll_count != NULL) {
					++* ret_dll_count;
				}
			}
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	if (was_dll_count_allocated) {
		free(ret_dll_count);
	}

	FindClose(hFind);
}
