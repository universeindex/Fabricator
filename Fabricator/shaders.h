#pragma once
#include <windows.h>
#include <cmath>
#include <time.h>
#include "define.h"

void Shader1(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		prgbScreen[i].rgb = ((prgbScreen[i].rgb - (RGB(
			(i + 1 / (w * h)) * 2,
			(i + 1 / (w * h)) * 2,
			(i + 1 / (w * h)) * 2
		)) / 2) * 2) % RGB(255, 255, 255);
	}
}

void Shader2(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		prgbScreen[i].rgb = ((prgbScreen[i].rgb + (RGB(
			(i + 1 / (w * h)) * 2,
			(i + 1 / (w * h)) * 2,
			(i + 1 / (w * h)) * 2
		)) / 2) * 2) % RGB(8, 8, 8);
	}
}

int hue = 0;
void Shader3(int w, int h, PRGBQUAD prgbScreen) {
	COLORREF clr = HtoRGB(hue);
	for (int i = 0; i < w * h; i++) {
		prgbScreen[i].rgb = ((((float)prgbScreen[i].r + (float)prgbScreen[i].g + (float)prgbScreen[i].b) / 3) / 255) * clr;
	}
	if (hue == 360) {
		hue = 0;
	}
	hue++;
}

void Shader4(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		if (i > 4 && i < (w * h) - 5) {
			if (rand() % 2 == 0) {
				prgbScreen[i].r = prgbScreen[i - (rand() % 3 - 1)].r;
				prgbScreen[i].b = prgbScreen[i + (rand() % 3 - 1)].b;
			} else {
				if (i - w > 4 && i + w < (w * h) - 5) {
					if (rand() % 2 == 0) {
						for (int ii = 0; ii < 5; ii++) {
							prgbScreen[i].r = (prgbScreen[i].r + prgbScreen[i - w].r) / 2;
							prgbScreen[i].b = (prgbScreen[i].b + prgbScreen[i + w].b) / 2;
						}
					} else {
						for (int ii = 0; ii < 5; ii++) {
							prgbScreen[i].r = (prgbScreen[i].r + prgbScreen[i + w].r) / 2;
							prgbScreen[i].b = (prgbScreen[i].b + prgbScreen[i - w].b) / 2;
						}
					}
				}
			}
		}
	}
}

void Shader5(int w, int h, PRGBQUAD prgbScreen) {
	for (int i = 0; i < w * h; i++) {
		if (i > 0) {
			prgbScreen[i].rgb = RGB(((int)i / (w * h) + 1) * 255, ((int)i / (w * h) + 1) * 255, ((int)i / (w * h) + 1) * 255);
		}
	}
}

bool posdef = false;
int imgpos[8][2];
void Shader6(int w, int h, PRGBQUAD prgbScreen) {
	if (posdef == false) {
		srand(rand());
		for (int y = 0; y < 8; y++) {
			imgpos[y][0] = rand() % (GetSystemMetrics(0) - 512);
			imgpos[y][1] = rand() % (GetSystemMetrics(1) - 512);
		}
		posdef = true;
	}
	int img[8][8] = {
		{0,0,0,0,0,0,0,0},
		{0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0},
		{0,1,0,0,0,0,1,0},
		{0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,1,0},
		{0,1,1,1,1,1,1,0},
		{0,0,1,1,1,1,0,0}
	};
	for (int p = 0; p < 8; p++) {
		for (int y = 1; y <= 64; y++) {
			for (int x = 0; x < 8; x++) {
				if (img[(int)y / 8][x] == 1) {
					prgbScreen[((h - (y + imgpos[p][0])) * w) + (x * 8) + imgpos[p][1]].rgb += RGB(rand() % (255 * 2) - 255, rand() % (255 * 2) - 255, rand() % (255 * 2) - 255);
					for (int i = 1; i <= 7; i++) {
						prgbScreen[((h - (y + imgpos[p][0])) * w) + (x * 8) + imgpos[p][1] + i].rgb += RGB(rand() % (255 * 2) - 255, rand() % (255 * 2) - 255, rand() % (255 * 2) - 255);
					}
				}
			}
		}
	}
}

void Shader7(int w, int h, PRGBQUAD prgbScreen) {
	int i = 0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			COLORREF clr = HtoRGB((
				(((double)x / (double)w) * (sin(clock() / 256 / 2) + 0.5)) + ((double)y / (double)h) * (1.0 - ((cos(clock() / 256 / 2)) + 0.5)) / 2
				) * 360);
			double r = prgbScreen[i].r;
			double g = prgbScreen[i].g;
			double b = prgbScreen[i].b;

			double average;

			average = (r + g + b) / 255;
			//r = average * (((float)GetRValue(clr)) / 255);
			//g = average * (((float)GetGValue(clr)) / 255);
			//b = average * (((float)GetBValue(clr)) / 255);
			r = average + GetRValue(clr);
			g = average + GetGValue(clr);
			b = average + GetBValue(clr);
			//r = ((((((double)average) / 255) * (((double)GetRValue(clr)))) * 0.1) + ((average / 255) * 1.1) * 75);
			//g = ((((((double)average) / 255) * (((double)GetGValue(clr)))) * 0.1) + ((average / 255) * 1.1) * 75); //(((double)average) / 255) * (((double)GetGValue(clr)));
			//b = ((((((double)average) / 255) * (((double)GetBValue(clr)))) * 0.1) + ((average / 255) * 1.1) * 75); //(((double)average) / 255) * (((double)GetBValue(clr)));
			//r *= (((float)GetRValue(clr)) / 255);
			//g *= (((float)GetGValue(clr)) / 255);
			//b *= (((float)GetBValue(clr)) / 255);

			prgbScreen[i].rgb = RGB(r, g, b);

			i++;
		}
	}
}