#include "HOOKW32.h"

BOOL HOOKW32::InjeceDLL(DWORD pid, const char*  fileName)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == INVALID_HANDLE_VALUE)return FALSE;
	SIZE_T dwNameSize = (lstrlen(fileName) + 1) * sizeof(WCHAR);
	LPVOID fileRemote = (PWSTR)VirtualAllocEx(hProcess, NULL, dwNameSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (fileRemote == NULL)return FALSE;
	//2.将dll路径拷贝到已分配内存上
	SIZE_T dwTempSize = 0;
	WriteProcessMemory(hProcess, fileRemote, fileName, dwNameSize, &dwTempSize);
	if (dwTempSize != dwNameSize)
	{
		printf("WriteProcessMemory失败\n");
		return FALSE;
	}

	//3.获取LoadLibraryA的实际地址
	LPTHREAD_START_ROUTINE fLibraryAdress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	//4.创建远程线程
	HANDLE  hThread = CreateRemoteThread(hProcess, NULL, 0, fLibraryAdress, fileRemote, 0, NULL);
	if (hThread == NULL)
	{
		printf("创建远程线程失败\n");
		return FALSE;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}

PROCESSENTRY32 HOOKW32::GetProcessIdByName(TCHAR *szProcessName)
{
	// 获取进程快照
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return PROCESSENTRY32();
	}

	// 获取第一个进程
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(hSnapshot, &pe);
	while (bRet)
	{
		// 判断进程名
		if (_tcscmp(pe.szExeFile, szProcessName) == 0)
		{
			// 关闭快照句柄
			CloseHandle(hSnapshot);
			return pe;
		}

		// 获取下一个进程
		bRet = Process32Next(hSnapshot, &pe);
	}

	// 关闭快照句柄
	CloseHandle(hSnapshot);
	return pe;
}
