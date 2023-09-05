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
}

BOOL HOOKW32::findProcess()
{
	//1.�����ʼ���ɹ���û��Ҫ���к�������
	if (m_bInit)return m_bInit;

	//2.��ȡ���ھ��
	m_hwnd=::FindWindow(strlen(m_className) == 0 ? NULL : m_className, strlen(m_titleName) == 0 ? NULL : m_titleName);
	if (m_hwnd==NULL)
	{
		logger.Log("m_hwnd ΪNULL");
		m_bInit == FALSE;
		return FALSE;
	}

	//3.ͨ�����ھ����ȡ����PID
	GetWindowThreadProcessId(m_hwnd, &m_pid);
	if (m_pid==NULL)
	{
		logger.Log("m_pid ΪNULL");
		m_bInit == FALSE;
		return FALSE;
	}

	//4.�򿪽���
	m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_pid);
	if (m_handle==NULL)
	{
		//CString info;
		//info.Format("�򿪽���PID:%dʧ��", m_pid);
		logger.Log("�򿪽���PIDʧ��");
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
	ReadProcessMemory ��ָ����ַ��Χ�е����ݴ�ָ�����̵ĵ�ַ�ռ临�Ƶ���ǰ���̵�ָ���������С�
	����PROCESS_VM_READ����Ȩ�޵ľ�����κν��̶����Ե��ú�����
	Ҫ��ȡ�������������ɷ��ʣ�����޷����ʣ�������ʧ�ܡ�
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