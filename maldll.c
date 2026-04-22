#include <windows.h>


BOOL __stdcall DllMain(HINSTANCE hModule,DWORD dwReason, LPVOID lpvReserved){
switch(dwReason){
case DLL_PROCESS_ATTACH:
	MessageBoxW(NULL,L"Hacked",L"IFNECESSARY",MB_OK);

}
return TRUE;
}
