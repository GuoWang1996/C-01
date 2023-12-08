#pragma once
#include "stdio.h"
#include <Windows.h>
#include <tchar.h>
#include <tlhelp32.h>

class HOOKW32
{
public:
	HOOKW32();
	~HOOKW32();
public:
	BOOL InjeceDLL(DWORD pid, const char* fileName);//远线程注入DLL
	PROCESSENTRY32 GetProcessIdByName(TCHAR *szProcessName);//获取进程id
};

