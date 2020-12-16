#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include "../StaticLib1/framework.h"
#include "../Dll_Menu/framework.h"
 /*  1.	Загрузить плагины.
    2.	Выгрузить плагины.
    3.	Показать на экране список плагинов. (просто имена модулей).
    4.	Показать информацию о каждом плагине(включая имя модуля, автора, описание).
    5.	Выполнить действие, предоставляемое плагином.*/
typedef VOID (*ProcExecute)();
typedef BOOLEAN(*GetDescription)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
typedef BOOLEAN(*GetAuthor)(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten);
int ShowModules();
int main() {
    setlocale(LC_ALL, "ru");
    char path[] = "..\\Debug\\plugins";
    std::vector<HINSTANCE> loadedDLL;
    bool running = true;
    char choice;
    ShowMenu();
    while (running) {
        std::cout << "Option: " << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case '1': {
            std::vector<LPSTR> dllList;
            auto result = ListDLLs(path,dllList);
            for (int i = 0; i < dllList.size(); i++)
            {
                char dllName[MAX_PATH];
                strcpy_s(dllName, MAX_PATH, dllList[i]);
                strcat_s(dllName, MAX_PATH, ".");//dll without .dll
                HINSTANCE library = LoadLibrary(dllName);
                if (library != NULL) {
                    loadedDLL.push_back(library);
                }
                else {
                    _tprintf(TEXT("Error loading library %s\n"),dllList[i]);
                }
            }
            break;
        }
        case '2': {
            for (int i = 0; i < loadedDLL.size(); i++)
            {
                FreeLibrary(loadedDLL[i]);
            }
            loadedDLL.clear();
            break;
        }
        case '3': {
            ShowModules();
            break;
        }
        case '4': {
            for (int i = 0; i < loadedDLL.size(); i++)
            {
                BOOLEAN value;
                DWORD pdwBytesWritten;
                GetDescription description = (GetDescription)GetProcAddress(loadedDLL[i], "GetDescription");
                if (description != nullptr) {
                    char* buf = new char[512];
                    value = description(buf, 512, &pdwBytesWritten);
                    if (value) {
                        std::cout << "Description: " << buf << std::endl;
                    }
                }
                GetAuthor info = (GetAuthor)GetProcAddress(loadedDLL[i], "GetAuthor");
                if (info != nullptr) {
                    char* buf = new char[512];
                    value = info(buf, 512, &pdwBytesWritten);
                    if (value) {
                        std::cout << "Author: " << buf << std::endl;
                    }
                }
            }
            break;
        }
        case '5': {
            for (int i = 0; i < loadedDLL.size(); i++) {
                ProcExecute function = (ProcExecute)GetProcAddress(loadedDLL[i], "Execute");
                if (function != nullptr) {
                    function();
                }
            }
            break;
        }
        case '6': {
            for (int i = 0; i < loadedDLL.size(); i++)
            {
                FreeLibrary(loadedDLL[i]);
            }
            loadedDLL.clear();
            running = false;
            break;
        }
        default: std::cout << "Error";
            break;
        }
    }
}
int ShowModules() {
    HMODULE hMods[1024];
    HANDLE hProcess;
    DWORD cbNeeded;
    unsigned int i;

    hProcess = GetCurrentProcess();
    if (NULL == hProcess)
        return 1;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
    {
        for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
        {
            TCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, hMods[i], szModName,
                sizeof(szModName) / sizeof(TCHAR)))
            {
                _tprintf(TEXT("%s\n"), szModName);
            }
        }
    }

    CloseHandle(hProcess);
    return 0;
}