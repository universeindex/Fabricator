#pragma once
#include <windows.h>
#include <cmath>
#include "define.h"
#include "vscreen.h"
#include <time.h>

int x = GetSystemMetrics(0);
int y = GetSystemMetrics(1);

void Payload1(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	for (int xx = 0; xx < x; xx++) {
		BitBlt(hdcTempScreen, xx+(xx/(rand() % (x-1) + 1)), 0, 1, y, hdcTempScreen, xx, 0, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload2(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 2 + (rand() % 2 * 2); // main effect comes from bitcount here
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	BitBlt(hdcTempScreen, rand() % 3 - 1, rand() % 3 - 1, x, y, hdcTempScreen, 0, 0, (rand() % 2) ? SRCCOPY : NOTSRCCOPY);

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload3(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	bool LR = rand() % 2;
	bool FY = rand() % 2;
	bool FX = rand() % 2;

	BitBlt(hdcTempScreen, LR ? 0 : x / 2, 0, x / 2, y, hdcTempScreen, LR ? x / 2 : 0, 0, SRCCOPY);
	if (FY) {
		StretchBlt(hdcTempScreen, 0, y, 0, -y, hdcTempScreen, 0, 0, x, y, SRCCOPY);
	}
	if (FX) {
		StretchBlt(hdcTempScreen, x, 0, -x, 0, hdcTempScreen, 0, 0, x, y, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload4(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	for (int yy = 0; yy < y; yy += 8) {
		for (int xx = 0; xx < x; xx += 8) {
			BitBlt(hdcTempScreen, xx, yy, 8, 8, hdcTempScreen, xx + ((rand() % 3 - 1) * 8), yy + ((rand() % 3 - 1) * 8), SRCCOPY);
		}
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload5(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	for (int yy = 0; yy < y; yy += 16) {
		for (int xx = 0; xx < x; xx += 16) {
			BitBlt(hdcTempScreen, xx, yy, 16, 16, hdcTempScreen, xx + ((rand() % 3 - 1) * 16), yy + ((rand() % 3 - 1) * 16), SRCCOPY);
		}
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload6(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	for (int yy = 0; yy < y; yy += 32) {
		for (int xx = 0; xx < x; xx += 32) {
			BitBlt(hdcTempScreen, xx, yy, 32, 32, hdcTempScreen, xx + ((rand() % 3 - 1) * 32), yy + ((rand() % 3 - 1) * 32), SRCCOPY);
		}
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload7(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	for (int yy = 0; yy < y; yy += 64) {
		for (int xx = 0; xx < x; xx += 64) {
			BitBlt(hdcTempScreen, xx, yy, 64, 64, hdcTempScreen, xx + ((rand() % 3 - 1) * 64), yy + ((rand() % 3 - 1) * 64), SRCCOPY);
		}
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload8(HDC hdc) {
	SIZE szScreen = GetVirtualScreenSize();
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = szScreen.cx;
	bmi.bmiHeader.biHeight = szScreen.cy;
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen = CreateCompatibleDC(hdc);
	HBITMAP hbmScreen = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);
	

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}