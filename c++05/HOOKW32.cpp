#include "HOOKW32.h"



HOOKW32::HOOKW32(TCHAR *className, TCHAR* titleName):
	m_bInit(FALSE),
	m_pid(0),
	m_hwnd(0),
	m_handle(0),
	logger("log.txt")
{
	ZeroMemory(m_className, sizeof(TCHAR));
	ZeroMemory(m_titleName, sizeof(TCHAR));
	if(className)_tcscpy(m_className,className);
	if (titleName)_tcscpy(m_titleName, titleName);

}

HOOKW32::~HOOKW32()
{
	if (m_handle)
	{
		CloseHandle(m_handle);
	}
}

BOOL HOOKW32::findProcess()
{
	//1.如果初始化成功就没必要进行后续操作
	if (m_bInit)return m_bInit;

	//2.获取窗口句柄
	m_hwnd=::FindWindow(strlen(m_className) == 0 ? NULL : m_className, strlen(m_titleName) == 0 ? NULL : m_titleName);
	if (m_hwnd==NULL)
	{
		logger.Log("m_hwnd 为NULL");
		m_bInit == FALSE;
		return FALSE;
	}

	//3.通过窗口句柄获取进程PID
	GetWindowThreadProcessId(m_hwnd, &m_pid);
	if (m_pid==NULL)
	{
		logger.Log("m_pid 为NULL");
		m_bInit == FALSE;
		return FALSE;
	}

	//4.打开进程
	m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pid);
	if (m_handle==NULL)
	{
		//CString info;
		//info.Format("打开进程PID:%d失败", m_pid);
		logger.Log("打开进程PID失败");
		m_bInit == FALSE;
		return FALSE;
	}

	m_bInit = TRUE;
	return m_bInit;
}

BOOL HOOKW32::readMemory(LPVOID adress, LPVOID buffer, DWORD readSize, DWORD* returnSize, BOOL bRe/*=FALSE*/)
{
	if (bRe==FALSE||m_bInit==FALSE)
	{
		if (!findProcess())return FALSE;
	}

	/*
	ReadProcessMemory 将指定地址范围中的数据从指定进程的地址空间复制到当前进程的指定缓冲区中。
	具有PROCESS_VM_READ访问权限的句柄的任何进程都可以调用函数。
	要读取的整个区域必须可访问，如果无法访问，则函数将失败。
	*/
	return ::ReadProcessMemory(m_handle, adress, buffer, readSize, returnSize);
}

BOOL HOOKW32::writeMemory(LPVOID adress, LPVOID buffer, DWORD readSize, DWORD* returnSize, BOOL bRe /*= FALSE*/)
{
	if (bRe == FALSE || m_bInit == FALSE)
	{
		if (!findProcess())return FALSE;
	}
	return ::WriteProcessMemory(m_handle, adress, buffer, readSize, returnSize);
}


BOOL HOOKW32::memoryProtect(LPVOID adress, DWORD size, DWORD newFlAllocationType, DWORD* oldFlAllocationType, BOOL bRe /*= FALSE*/)
{
	if (bRe == FALSE || m_bInit == FALSE)
	{
		if (!findProcess())return FALSE;
	}
	
	return ::VirtualProtectEx(m_handle, adress, size, newFlAllocationType, oldFlAllocationType);
}

LPVOID HOOKW32::allocMemory(DWORD size, BOOL bRe /*= FALSE*/)
{
	if (bRe == FALSE || m_bInit == FALSE)
	{
		if (!findProcess())return FALSE;
	}
	return ::VirtualAllocEx(m_handle, NULL, size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
}

BOOL HOOKW32::freeMemory(LPVOID adress, DWORD size, BOOL bRe /*= FALSE*/)
{
	if (bRe == FALSE || m_bInit == FALSE)
	{
		if (!findProcess())return FALSE;
	}
	return ::VirtualFreeEx(m_handle, adress, size, MEM_DECOMMIT);
}

BOOL HOOKW32::InjeceDLL(TCHAR* fileName, BOOL bRe /*= FALSE*/)
{
	if (bRe == FALSE || m_bInit == FALSE)
	{
		if (!findProcess())return FALSE;
	}

	//1.申请内存
	LPVOID dllAdress=allocMemory(512 * sizeof(TCHAR));
	if (!dllAdress)return FALSE;

	//2.写入dll
	SIZE_T dwTempSize = 0;
	if (!writeMemory(dllAdress, fileName, strlen(fileName) * sizeof(TCHAR), &dwTempSize))
	{
		logger.Log("写入dll失败");
		return FALSE;
	}
	else {

		//3.获取LoadLibraryA的实际地址
		LPTHREAD_START_ROUTINE loadLibraryAfun = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
		if (loadLibraryAfun == NULL) {
			logger.Log("获取LoadLibraryA的实际地址失败");
			return FALSE;
		}
		//4.创建远程线程
		HANDLE  hThread = CreateRemoteThread(m_handle, NULL, 0, loadLibraryAfun, dllAdress, 0, NULL);
		if (hThread == NULL)
		{
			logger.Log("创建远程线程失败");
			return FALSE;
		}
		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		CloseHandle(m_handle);
		if (!freeMemory(dllAdress, 512 * sizeof(TCHAR)))logger.Log("释放内存失败");
	
	}
}
