// C++01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Base1.h"
#include "Base2.h"
#include <windows.h>

using namespace std;

void test01()
{
	short** s1;
	//short* s;
	s1 = (short**)200;
	//s = s + 1;
	printf("i:%d", s1);
}
void scopy(char* desc,const char* src)
{
	while (*src!=0)
	{
		*desc = *src;
		src++;
		desc++;
	}
	*desc = 0;
}
struct MyStruct
{
	int x;
	int y;
};
int main()
{
	const char* filePath = "D:/阿里云下载/往日不再 官方中文 v1.07 综合MOD合集+完全通关存档 支持手柄 解压即玩/Days Gone v1.07/Days Gone v1.07/BendGame/Binaries/Win64/DaysGone.exe";  // 替换成你的可执行文件路径

	// 加载可执行文件
	HMODULE module = LoadLibraryEx(filePath, nullptr, DONT_RESOLVE_DLL_REFERENCES);
	if (module == nullptr)
	{
		std::cout << "Failed to load the executable file." << std::endl;
		return 1;
	}

	// 获取NT头
	LONG ntHeader = *(LONG *)((BYTE*)module+0x3c);

	//获取节表数量
	WORD numberOfSections = *((BYTE*)module + ntHeader+0x6);
	printf("节数量:%d\n", numberOfSections);

	//获取可选头大小
	WORD sizeOfOptionalHeade = *((BYTE*)module + ntHeader + 0x14);

	//获取节表目录
		BYTE* sectionTable = ((BYTE*)module + ntHeader + sizeOfOptionalHeade + 0x18);
		char name[10];
	for (int i=0;i< numberOfSections;i++)
	{
		
		strncpy(name, (char*)sectionTable, 8); 
		name[8] = '\0';
		printf("%s\n", name);
		sectionTable += sizeof(IMAGE_SECTION_HEADER);
	
	}




	

	// 卸载可执行文件
	FreeLibrary(module);

	return 0;
}
