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
	BOOL InjeceDLL(DWORD pid, const char* fileName);//Զ�߳�ע��DLL
	PROCESSENTRY32 GetProcessIdByName(TCHAR *szProcessName);//��ȡ����id
};

