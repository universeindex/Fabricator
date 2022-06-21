#include <windows.h>
#include "shaderthreads.h"
#include "payloadthreads.h"
#include "define.h"
//#include "audiothread.h" initially from orion, will implement later

#pragma comment(lib, "Msimg32.lib")

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	int msgResult = MessageBox(NULL, L"Hold it there... you just executed malware!!\nThis malware wasn't made for malicious purposes, which is why I am warning you incase you ran this by accident!", L"Orion.exe", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}
	msgResult = MessageBox(NULL, L"FINAL WARNING! IF YOU CONTINUE, YOUR SYSTEM WILL BECOME COMPLETELY UNUSABLE!!\nDO NOT RUN THIS ON YOUR PERSONAL COMPUTER!\nStill continue?!", L"Hydrogen.exe - LAST WARNING", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}

	

	//HANDLE Payload12H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload15T, NULL, 0, NULL);
	//Sleep(10000);


	//HANDLE Payload16H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload16T, NULL, 0, NULL);
	//Sleep(10000);

	return 0;
}