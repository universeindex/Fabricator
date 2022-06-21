#pragma once
#include <windows.h>

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