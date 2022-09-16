#pragma once
#include <windows.h>

HWND EffectDisplayWindow;
HDC EffectDisplayDC;

void InitLayeredWindow(HINSTANCE module) {
	WNDCLASS wc = {};
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hInstance = module;
	wc.lpszClassName = L"window";
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc =
		[](HWND window, UINT message, WPARAM wparam,
			LPARAM lparam) -> LRESULT {
				if (WM_DESTROY == message) {
					PostQuitMessage(0);
					return 0;
				}
				return DefWindowProc(window, message, wparam, lparam);
	};
	RegisterClass(&wc);
	EffectDisplayWindow = CreateWindowExW(
		WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
		wc.lpszClassName, L"Fabricator",
		WS_POPUP | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
		0, 0,
		GetSystemMetrics(0), GetSystemMetrics(1),
		nullptr, nullptr, module, nullptr
	);


	ShowWindow(EffectDisplayWindow, 1);
	SetLayeredWindowAttributes(EffectDisplayWindow, 0, 255, LWA_ALPHA);

	EffectDisplayDC = GetDC(EffectDisplayWindow);
}

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, PRECT prcBounds, LPARAM lParam) {
	PRECT prcParam = (RECT*)lParam;
	UnionRect(prcParam, prcParam, prcBounds);
	return 1;
}
RECT GetVirtualScreen() {
	RECT rcScreen = { 0 };
	EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, (LPARAM)&rcScreen);
	return rcScreen;
}
POINT GetVirtualScreenPos() {
	RECT rcScreen = GetVirtualScreen();
	POINT ptScreen = {
		rcScreen.left,
		rcScreen.top
	};
	return ptScreen;
}
SIZE GetVirtualScreenSize() {
	RECT rcScreen = GetVirtualScreen();
	SIZE szScreen = {
		rcScreen.right - rcScreen.left,
		rcScreen.bottom - rcScreen.top
	};
	return szScreen;
}