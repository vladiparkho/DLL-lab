#include "pch.h"
#include <stdio.h>
#include <iostream>
BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char name[] = "Владимир Пархоменко";
    if (buffer == nullptr) {
        *pdwBytesWritten = strlen(name) * sizeof(char)+1;
        return true;
    }
    bool res = strcpy_s(buffer, dwBufferSize, name);
    if (res != 0) {
        return false;
    }
    //?* pdwBytesWritten = ?
    return res;

}
BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char msg[] = "Dll2. Hardware information";
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
    SYSTEM_INFO siSysInfo;
    GetSystemInfo(&siSysInfo);
    printf("Hardware information: \n");
    printf(" Number of processors: %u\n", 
        siSysInfo.dwNumberOfProcessors);
    printf("  Page size: %u\n", siSysInfo.dwPageSize);
    printf("  Processor type: %u\n", siSysInfo.dwProcessorType);

    printf("  Active processor mask: %u\n",
        siSysInfo.dwActiveProcessorMask);
    printf("  The architecture-dependent processor level: %u\n",
        siSysInfo.wProcessorLevel);
    printf("  The architecture-dependent processor revision: %u\n",
        siSysInfo.wProcessorRevision);
}