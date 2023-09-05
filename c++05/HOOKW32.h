#pragma once
#include <Windows.h>
#include <tchar.h>

#include "Logger.h"


class HOOKW32
{
public:
	Logger logger; // ����һ��Logger������Ϊ��Ա����
public:
	HOOKW32(TCHAR *className, TCHAR* titleName);
	~HOOKW32();
private:
	BOOL m_bInit;//�Ƿ��ʼ��
	TCHAR m_className[126];
	TCHAR m_titleName[126];
	DWORD m_pid;// GetWindowThreadProcessId
	HWND m_hwnd;//���ھ��  FindWindow
	HANDLE m_handle;//���̾��  OpenProcess
public:

	/************************************
	* ������:    findProcess
	* �� �� : 
	* ����ֵ:   BOOL
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	BOOL findProcess();
	
	
	/************************************
	* ������:    readMemory
	* �� �� :���ڴ�
	* �� �� : LPVOID adress  ָ��Ҫ��ȡ���ڴ��ַ
	* �� �� : LPVOID buffer	 ָ���ָ�����̵ĵ�ַ�ռ�������ݵĻ�������ָ�롣
	* �� �� : DWORD readSize Ҫ��ָ�����̶�ȡ���ֽ�����
	* �� �� : DWORD returnSize ָ�������ָ�룬�ñ������մ��䵽ָ�����������ֽ���
	* �� �� : BOOL bRe
	* ����ֵ:   BOOL
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	BOOL readMemory(LPVOID adress,LPVOID buffer,DWORD readSize,DWORD* returnSize,BOOL bRe=FALSE);//


	/************************************
	* ������:    writeMemory
	* �� �� :д�ڴ�
	* �� �� : LPVOID adress ��ַ
	* �� �� : LPVOID buffer ������
	* �� �� : DWORD readSize ����С
	* �� �� : DWORD returnSize ���ض���С
	* �� �� : BOOL bRe
	* ����ֵ:   BOOL
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	BOOL writeMemory(LPVOID adress, LPVOID buffer, DWORD readSize, DWORD* returnSize, BOOL bRe = FALSE);//
	
	

	/************************************
	* ������:    memoryProtect
	* �� �� : �����ڴ�ҳ������
	* �� �� : LPVOID adress  ָ��Ҫ��������ʱ������Ե�ҳ����Ļ�ַ��ָ�롣
	* �� �� : DWORD size ���ʱ��������Ѹ��ĵ�����Ĵ�С�����ֽ�Ϊ��λ
	* �� �� : DWORD newFlAllocationType �µ�ҳ������
	* �� �� : DWORD oldFlAllocationType �ɵ�ҳ������
	* ����ֵ:   BOOL
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	BOOL memoryProtect(LPVOID adress, DWORD size, DWORD  newFlAllocationType, DWORD*  oldFlAllocationType, BOOL bRe = FALSE);

	/************************************
	* ������:    allocMemory
	* �� �� : �����ڴ�
	* �� �� : DWORD size �����С
	* �� �� : BOOL bRe
	* ����ֵ:   LPVOID
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	LPVOID allocMemory(DWORD size, BOOL bRe = FALSE);

	/************************************
	* ������:    freeMemory
	* �� �� : �ͷ��ڴ�
	* �� �� : LPVOID adress �ͷ��ڴ��ַָ��
	* �� �� : DWORD size �ͷ��ڴ��С
	* �� �� : BOOL bRe 
	* ����ֵ:   BOOL
	* ������: Simple
	* ����ʱ��  : 2023��9��5��
	************************************/
	BOOL freeMemory(LPVOID adress, DWORD size, BOOL bRe = FALSE);


	BOOL InjeceDLL(TCHAR* fileName, BOOL bRe = FALSE);//Զ�߳�ע��DLL

};	


