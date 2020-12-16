#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <psapi.h>
#include "../StaticLib1/framework.h"
#include "../Dll_Menu/framework.h"
//#include "../Dll1/framework.h";
//#include "../Dll3/framework.h"
//#include "Dll1.h"
 /*   1.	Загрузить плагины.
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
    //HelloFromDll3();
    char path[] = "C:\\Users\\Vladimir\\MyFolder\\programming\\c++\\Dll_lab_\\Dll_lab_\\Debug\\plugins";
    size_t listSize = 0;
    //ListDLLs(path, NULL, &listSize);
    LPCSTR* dllList = nullptr;
    //ListDLLs(path, dllList, NULL);
    HINSTANCE* loadedDll = nullptr;
    int count=0;
  
    bool running = true;
    char choice;
    ShowMenu();
    while (running) {
        std::cout << "Option: " << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case '1': {
            WIN32_FIND_DATA file; //описание файла
            HANDLE hFile = FindFirstFile("Plugins\\*.dll", &file);
            ListDLLs(path, NULL, &listSize);
            dllList = new LPCSTR[listSize];
            ListDLLs(path, dllList, NULL);
            loadedDll = new HINSTANCE[listSize];
            for (int i = 0; i < listSize; i++)
            {
                char dllName[MAX_PATH];
                strcpy_s(dllName, MAX_PATH, dllList[i]);
                strcat_s(dllName, MAX_PATH, ".");

                loadedDll[count] = LoadLibrary(dllName);
                count++;

            }
            break;
        }
        case '2': {
            if (count != 0) {
                for (int i = 0; i < count; i++)
                {
                    FreeLibrary(loadedDll[i]);
                }
                delete[] loadedDll;
                count = 0;
            }
            break;
        }

        case '3': {
            ShowModules();
            break;
        }
        case '4': {
            if (count != 0) {
                for (int i = 0; i < count; i++)
                {

                    BOOLEAN value;
                    GetDescription description = (GetDescription)GetProcAddress(loadedDll[i], "GetDescription");
                    if (description != nullptr) {
                        // DWORD bufsize = 0;
                         // info(nullptr, 0, &bufsize);
                        char* buf = new char[512];
                        value = description(buf, 512, nullptr);
                        if (!value) {
                            std::cout << "Descr: " << buf << std::endl;
                        }
                    }
                    GetAuthor info = (GetAuthor)GetProcAddress(loadedDll[i], "GetAuthor");
                    if (info != nullptr) {
                        DWORD bufsize = 0;
                        char* buf = new char[512];
                        value = info(buf, 512, nullptr);
                        if (!value) {
                            std::cout << "Author: " << buf << std::endl;
                        }
                    }
                }
            }
            break;
        }
        case '5': {
            if (count != 0) {
                for (int i = 0; i < count; i++) {
                    ProcExecute function = (ProcExecute)GetProcAddress(loadedDll[i], "Execute");
                    if (function != nullptr) {
                        function();
                    }
                }
            }
            break;
        }
        case '6': {
            if (count != 0) {
                for (int i = 0; i < count; i++)
                {
                    FreeLibrary(loadedDll[i]);
                }
                delete[] loadedDll;
            }
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