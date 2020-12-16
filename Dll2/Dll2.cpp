#include "pch.h"
#include <stdio.h>
#include <iostream>
BOOLEAN GetAuthor(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char name[] = "Vladimir Parkhomenko";
    bool res = strcpy_s(buffer, dwBufferSize, name);
    return res == 0;

}
BOOLEAN GetDescription(LPSTR buffer, DWORD dwBufferSize, DWORD* pdwBytesWritten) {
    char msg[] = "Dll2. Hardware information";
    bool res = strcpy_s(buffer, dwBufferSize, msg);
    return res == 0;
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