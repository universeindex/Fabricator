#pragma once
#include <windows.h>
#include <cmath>
#include "define.h"
#include "vscreen.h"
#include <time.h>

int x = GetSystemMetrics(0);
int y = GetSystemMetrics(1);

void Payload1(HDC hdc) {
	int rx = random() % (int)(x / 1.5);
	int ry = random() % y;

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));


	SIZE ts;
	GetTextExtentPoint(hdc, L"you are not safe :)", wcslen(L"you are not safe :)"), &ts);
	TextOutW(hdc, rx, ry, L"you are not safe :)", wcslen(L"you are not safe :)"));
	StretchBlt(hdc, rx, ry, ts.cx * ((float)(rand() % 1500)) / 100, ts.cy * ((float)(rand() % 750)) / 100, hdc, rx, ry, ts.cx, ts.cy, SRCCOPY);
	Sleep(2000);
}

bool alt = false;
void Payload2(HDC hdc) {
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
	for (int i = 0; i <= x; i += 4) {
		if (alt == true) {
			BitBlt(hdcTempScreen, i, -sin(clock() / 64) * 5, 4, y, hdcTempScreen, i, 0, SRCCOPY);
		} else {
			BitBlt(hdcTempScreen, i, sin(clock() / 64) * 5, 4, y, hdcTempScreen, i, 0, SRCCOPY);
		}
		alt = not alt;
	}
	alt = not alt;
	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

int t = 0;
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

	POINT ptScreen = GetVirtualScreenPos();

	POINT pt[3];
	pt[0] = { (long)sin(clock() / 256) * x, (long)cos(clock() / 256) * y };
	pt[1] = { (long)cos(clock() / 128) * x, (long)sin(clock() / 512) * y };
	pt[2] = { (long)sin(clock() / 384) * x, (long)cos(clock() / 128) * y };
	PlgBlt(hdcTempScreen, pt, hdcTempScreen, ptScreen.x, ptScreen.y, szScreen.cx, szScreen.cy, NULL, 0, 0);

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

	BLENDFUNCTION blf = { 0 };
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 64;
	blf.AlphaFormat = 0;

	for (int i = 0; i < 15; i++) {
		int rx = rand() % x;
		int ry = rand() % y;
		if (rand() % 2 == 0) {
			BitBlt(hdcTempScreen, rx - 250, ry - 250, 500, 500, hdcTempScreen, rx - 250, ry - 251, SRCCOPY);
		} else {
			BitBlt(hdcTempScreen, rx - 250, ry + 250, 500, 500, hdcTempScreen, rx - 250, ry + 251, SRCCOPY);
		}
	}

	AlphaBlend(hdc, 0, t, szScreen.cx, szScreen.cy, hdcTempScreen, 0, 0, szScreen.cx, szScreen.cy, blf);
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

	BLENDFUNCTION blf = { 0 };
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = rand() % 255;
	blf.AlphaFormat = 0;

	SelectObject(hdcTempScreen, CreatePen(PS_NULL, NULL, NULL));

	int rx = rand() % x;
	int ry = rand() % y;
	POINT verts[] = { {200 + (rx - 100), 125 + (ry - 62)}, {300 + (rx - 150), 300 + (ry - 150)}, {100 + (rx - 50), 300 + (ry - 150)} };
	Polygon(hdcTempScreen, verts, sizeof(verts) / sizeof(verts[0]));

	AlphaBlend(hdc, 0, t, szScreen.cx, szScreen.cy, hdcTempScreen, 0, 0, szScreen.cx, szScreen.cy, blf);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
	Sleep(250);
}

int p6counter = 0;
void Payload6(HDC hdc) {
	SetGraphicsMode(hdc, GM_ADVANCED);

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
	SetGraphicsMode(hdcTempScreen, GM_ADVANCED);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

	if (p6counter == 50) {
		bool toggle = false;
		for (int ii = 0; ii < x; ii += 4) {
			if (toggle == true) {
				BitBlt(hdcTempScreen, ii, 0, 4, y, hdcTempScreen, ii, 2, SRCCOPY);
			} else {
				BitBlt(hdcTempScreen, ii, 0, 4, y, hdcTempScreen, ii, -2, SRCCOPY);
			}
			toggle = not toggle;
		}
	}

	for (int i = 0; i < 5; i++) {
		int rx = rand() % x;
		int ry = rand() % y;
		if (p6counter == 50) {
			BitBlt(hdcTempScreen, rx - 250, ry - 250, 500, 500, hdcTempScreen, rx - (250 + (rand() % 3 - 1)), ry - (250 + (rand() % 3 - 1)), SRCCOPY);

			p6counter = 0;
		} else {
			BitBlt(hdcTempScreen, rx - 250, ry - 250, 500, 500, hdcTempScreen, rx - (250 + (rand() % 3 - 1)), ry - (250 + (rand() % 3 - 1)), SRCCOPY);
		}
	}

	p6counter++;

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload7(HDC hdc) {
	SetGraphicsMode(hdc, GM_ADVANCED);

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
	SetGraphicsMode(hdcTempScreen, GM_ADVANCED);
	SelectObject(hdcTempScreen, hbmScreen);
	BitBlt(hdcTempScreen, 0, 0, x, y, hdc, 0, 0, SRCCOPY);



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

	for (int i = 1; i < y - 1; i++) {
		BitBlt(hdcTempScreen, 0, i, x, 1, hdcTempScreen, 0, i + (rand() % 3 - 1), SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload9(HDC hdc) {
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

	for (int i = 1; i < x - 1; i++) {
		BitBlt(hdcTempScreen, i, 0, 1, y, hdcTempScreen, i + (rand() % 3 - 1), 0, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload10(HDC hdc) {
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

	for (int i = 1; i < x - 1; i++) {
		BitBlt(hdcTempScreen, i, 0, 1, y, hdcTempScreen, i + (rand() % 3 - 1), 0, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

void Payload11(HDC hdc) {
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
			BitBlt(hdcTempScreen, xx, yy, rand() % 16 + 1, rand() % 16 + 1, hdcTempScreen, xx + (rand() % 3 - 1), yy + (rand() % 3 - 1), SRCCOPY);
		}
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}

int p12tick = 0;
void Payload12(HDC hdc) {
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

	for (int yy = 0; yy < y; yy++) {
		BitBlt(hdcTempScreen, 0, yy, x, 1, hdcTempScreen, (sin(yy + p12tick) * 2), yy, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
	p12tick++;
}

int p13tick = 0;
void Payload13(HDC hdc) {
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
		BitBlt(hdcTempScreen, xx, 0, 1, y, hdcTempScreen, xx, (sin(xx + p13tick) * 2), SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
	p13tick++;
}

int p14tick = 0;
void Payload14(HDC hdc) {
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

	for (int yy = 0; yy < y; yy++) {
		BitBlt(hdcTempScreen, 0, yy, x, 1, hdcTempScreen, (sin((float)yy / 16 + (float)p14tick / 4) * 2), yy, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
	p14tick++;
}

int p15tick = 0;
void Payload15(HDC hdc) {
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
		BitBlt(hdcTempScreen, xx, 0, 1, y, hdcTempScreen, xx, (sin((float)xx / 16 + (float)p15tick / 4) * 2), SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
	p15tick++;
}

void Payload16(HDC hdc) {
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

	for (int i = 0; i < y; i++) {
		BitBlt(hdcTempScreen, rand() % 3 - 1, i, x, 1, hdcTempScreen, 0, i, SRCCOPY);
	}

	BitBlt(hdc, 0, 0, x, y, hdcTempScreen, 0, 0, SRCCOPY);
	DeleteDC(hdcTempScreen);
	DeleteObject(hbmScreen);
}