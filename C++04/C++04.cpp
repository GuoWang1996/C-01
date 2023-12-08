#include <Windows.h>
#include <iostream>

int main() {
	// 打开已经存在的文件映射对象
	HANDLE hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS, // 可读写访问权限
		FALSE,               // 不继承句柄
		L"MySharedMemory");  // 映射对象的名称

	if (hMapFile == NULL) {
		std::cout << "OpenFileMapping failed with error code: " << GetLastError() << std::endl;
		return 1;
	}

	// 映射共享内存到进程地址空间
	LPVOID pBuf = MapViewOfFile(
		hMapFile,
		FILE_MAP_READ,  // 只读访问权限
		0,
		0,
		0);

	if (pBuf == NULL) {
		std::cout << "MapViewOfFile failed with error code: " << GetLastError() << std::endl;
		CloseHandle(hMapFile);
		return 1;
	}

	// 从共享内存中读取数据并打印
	const char* data = static_cast<const char*>(pBuf);
	std::cout << "Received data from shared memory: " << data << std::endl;

	// 释放共享内存和相关资源
	UnmapViewOfFile(pBuf);
	CloseHandle(hMapFile);

	return 0;
}
