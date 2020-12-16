#include "pch.h"
#include <stdio.h>
#include <iostream>

BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char name[] = "Vladimir Parkhomenko";
    bool res = strcpy_s(buffer, dwBufferSize, name);
    return res == 0;

}
BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char msg[] = "Dll1. Performance Monitor";
    bool res = strcpy_s(buffer, dwBufferSize, msg);
    return res == 0;
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