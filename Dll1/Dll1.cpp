#include "pch.h"
#include <stdio.h>
#include <iostream>

BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char name[] = "Vladimir Parkhomenko";
    if (buffer == nullptr) {
        *pdwBytesWritten = strlen(name) * sizeof(char)+1;
        return true;
    }
    bool res = strcpy_s(buffer, dwBufferSize, name);
    if (res != 0) {
        return false;
    }

    return res;

}
BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char msg[] = "Dll1. Performance Monitor";
    if (buffer == nullptr) {
        *pdwBytesWritten = strlen(msg) * sizeof(char)+1;
        return true;
    }
    bool res = strcpy_s(buffer, dwBufferSize, msg);
    if (res != 0) {
        return false;
    }
    return res;
}
VOID Execute() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    LPCSTR applicationName = "C:\\WINDOWS\\system32\\perfmon.exe";
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(applicationName,NULL,NULL,NULL,FALSE,0,
        NULL,NULL, &si,&pi))
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    // Wait until child process exits.
    WaitForSingleObject(pi.hProcess, INFINITE);
    // Close process and thread handles. 
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}