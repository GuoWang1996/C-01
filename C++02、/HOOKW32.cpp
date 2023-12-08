#include "HOOKW32.h"

BOOL HOOKW32::InjeceDLL(DWORD pid, const char*  fileName)
{
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == INVALID_HANDLE_VALUE)return FALSE;
	SIZE_T dwNameSize = (lstrlen(fileName) + 1) * sizeof(WCHAR);
	LPVOID fileRemote = (PWSTR)VirtualAllocEx(hProcess, NULL, dwNameSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (fileRemote == NULL)return FALSE;
	//2.��dll·���������ѷ����ڴ���
	SIZE_T dwTempSize = 0;
	WriteProcessMemory(hProcess, fileRemote, fileName, dwNameSize, &dwTempSize);
	if (dwTempSize != dwNameSize)
	{
		printf("WriteProcessMemoryʧ��\n");
		return FALSE;
	}

	//3.��ȡLoadLibraryA��ʵ�ʵ�ַ
	LPTHREAD_START_ROUTINE fLibraryAdress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	//4.����Զ���߳�
	HANDLE  hThread = CreateRemoteThread(hProcess, NULL, 0, fLibraryAdress, fileRemote, 0, NULL);
	if (hThread == NULL)
	{
		printf("����Զ���߳�ʧ��\n");
		return FALSE;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	CloseHandle(hProcess);

	return TRUE;
}

PROCESSENTRY32 HOOKW32::GetProcessIdByName(TCHAR *szProcessName)
{
	// ��ȡ���̿���
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot == INVALID_HANDLE_VALUE)
	{
		return PROCESSENTRY32();
	}

	// ��ȡ��һ������
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(hSnapshot, &pe);
	while (bRet)
	{
		// �жϽ�����
		if (_tcscmp(pe.szExeFile, szProcessName) == 0)
		{
			// �رտ��վ��
			CloseHandle(hSnapshot);
			return pe;
		}

		// ��ȡ��һ������
		bRet = Process32Next(hSnapshot, &pe);
	}

	// �رտ��վ��
	CloseHandle(hSnapshot);
	return pe;
}
