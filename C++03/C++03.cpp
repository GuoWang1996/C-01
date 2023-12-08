// C++03.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <tchar.h>

DWORD WINAPI ThreadProc(LPVOID lpParam) {
	//线程代码
	return 0;
}
int main()
{
	const char* filePath = "E://VS项目//MFC01//Debug//DLL1.dll";  // 替换成你的可执行文件路径
	const char* filePath2 = "E://VS项目//MFC01//Debug//DLL2.dll";  // 替换成你的可执行文件路径

	HINSTANCE h = GetModuleHandle(filePath);
	if (h == NULL)
	{
		HMODULE hMoudle = LoadLibrary(filePath);
		HMODULE hMoudle2 = LoadLibrary(filePath2);

		HANDLE hThread = CreateThread(NULL, 0, ThreadProc, hMoudle2, 0, NULL);

		while (true)
		{
			printf("主线程代码\n");
			Sleep(1000);

		}
		FreeLibrary(hMoudle);

	}

	return 0;
}