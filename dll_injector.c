#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MEM_ALLOC_ERR "Memory Allocation Error"
#define MEM_WR_ERR "Memory Write Error"
#define  TH_CR_ERR "Thread Creation Error"

int main(int argc, char* argv[]) {
if(argc<3) {
printf("Insufficient Arguments");
return EXIT_FAILURE;
}
DWORD PID=atoi(argv[1]);
const char* DLL_PATH=argv[2];
SIZE_T PATH_SIZE=strlen(DLL_PATH)+1;

hProcess=OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
if(!hProcess){
printf("Process with PID: %d does not exist!",PID);
return EXIT_FAILURE;
}

HMODULE hKernel32=GetModuleHandleA("kernel32"); // base addr of kernel32.dll 
LPTHREAD_START_ROUTINE bDllProc=(LPTHREAD_START_ROUTINE)GetProcAddress(hKernel32,"LoadLibraryA"); // base addr of dll procedure

SIZE_T BYTES_WR=0; 
LPVOID hMem=VirtualAllocEx(hProcess,NULL,PATH_SIZE,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);
if(!hMem) {
printf(MEM_ALLOC_ERR);
return EXIT_FAILURE;
}
if(!WriteProcessMemory(hProcess,hMem,DLL_PATH,PATH_SIZE,&BYTES_WR) || PATH_SIZE!=BYTES_WR){
printf(MEM_WR_ERR);
return EXIT_FAILURE;
}

HANDLE hThread=CreateRemoteThread(hProcess,NULL,NULL,bDllProc,hMem,0,NULL);
if(!hThread){
printf(TH_CR_ERR);
return EXIT_FAILURE;
}
WaitForSingleObject(hThread,INFINITE);
CLEANUP:
 CloseHandle(hThread);
 CloseHandle(hProcess);


return EXIT_SUCCESS;
}
