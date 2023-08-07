// C++03.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <tchar.h>
PROCESSENTRY32 GetProcessIdByName(LPCTSTR szProcessName);
BOOL InjeceDLL(DWORD pid, const wchar_t* fileName) {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (hProcess == INVALID_HANDLE_VALUE)return FALSE;
	SIZE_T dwNameSize = (wcslen(fileName) + 1) * sizeof(WCHAR);
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
	LPTHREAD_START_ROUTINE fLibraryAdress = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryW");

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

int main() {
	PROCESSENTRY32 pe = GetProcessIdByName(L"ͨѶ¼����ϵͳ.exe");
	if (InjeceDLL(pe.th32ProcessID, L"E:\\VS��Ŀ\\MFC01\\Debug\\DLL1.dll"))
	{
		printf("ע��ɹ�\n");
	}
	else {
		printf("ע��ʧ��\n");
	}
	system("pause");
	return 0;
}


//��ȡ����id
PROCESSENTRY32 GetProcessIdByName(LPCTSTR szProcessName)
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