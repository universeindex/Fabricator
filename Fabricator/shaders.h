#pragma once
#include <windows.h>
#include <cmath>
#include <time.h>
#include "define.h"

void Shader1(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		int Value = float(rand() % 255) * ((sin(clock() + 1.0) * 0.5));
		prgbScreen[i].rgb = RGB(Value, Value, Value);
	}
}

void Shader2(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		prgbScreen[i].rgb += 1;
		prgbScreen[i].rgb %= RGB(i * ((rand() % 255 + 1) / (w * h)) * rand() % 255, i * ((rand() % 255 + 1) / (w * h)) * rand() % 255, i * ((rand() % 255 + 1) / (w * h)) * rand() % 255) + RGB(1, 1, 1);
	}
}

void Shader3(int w, int h, PRGBQUAD prgbScreen) {
	int min = rand() % (w * h);
	int max = rand() % (w * h);
	if (min > max) {
		max = min;
	}
	for (int i = min; i < max; i++) {
		prgbScreen[i].rgb += 1;
		prgbScreen[i].rgb %= RGB(rand() % i, rand() % i, rand() % i);
	}
}