#include <iostream>
#include <chrono>
#include <iomanip>
#include <thread>
#include <fstream>
#include <ShlObj.h> // 使用 SHGetFolderPath
#include <Windows.h>
#include "TCHAR.H"


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE:
		// 设置窗口样式为无边框、透明
		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);

		// 将窗口置于桌面最外层
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		// 设置窗口透明度
		SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// 从窗口获取剩余寿命
		int remainingDays = static_cast<int>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

		// 转换显示天、时、分、秒
		int days = remainingDays / (24 * 3600);
		int hours = (remainingDays % (24 * 3600)) / 3600;
		int mins = (remainingDays % 3600) / 60;
		int secs = remainingDays % 60;

		// 格式化显示
		wchar_t buffer[256];
		swprintf_s(buffer, L"你的生命还剩%d 天 %d 时 %d 分 %d 秒", days, hours, mins, secs);

		// 在窗口中心绘制文本
		RECT rect;
		GetClientRect(hwnd, &rect);
		DrawText(hdc, buffer, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(hwnd, &ps);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void createShortcut(const wchar_t* targetPath, const wchar_t* shortcutPath) {
	CoInitialize(NULL);

	// 获取启动目录
	wchar_t startupPath[MAX_PATH];
	SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, 0, startupPath);

	// 构建快捷方式路径
	std::wstring shortcut = startupPath;
	shortcut += L"\\";
	shortcut += shortcutPath;

	// 创建快捷方式
	HRESULT hres;
	IShellLink* psl;

	// 创建IShellLink对象
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres)) {
		psl->SetPath(targetPath);
		psl->SetDescription(L"MyLifeCounter"); // 设置快捷方式的描述信息

		// 创建IPersistFile对象
		IPersistFile* ppf;
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres)) {
			// 保存快捷方式
			hres = ppf->Save(shortcut.c_str(), TRUE);
			ppf->Release();
		}
		psl->Release();
	}

	CoUninitialize();
}

int WINAPI _tWinMain(
	HINSTANCE hInctance,
	HINSTANCE hPrevInctance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	// 出生日期
	std::tm birthTime = {};
	birthTime.tm_year = 1996 - 1900;
	birthTime.tm_mon = 10;
	birthTime.tm_mday = 2;
	birthTime.tm_hour = 20;
	birthTime.tm_min = 0;
	birthTime.tm_sec = 0;

	// 将出生日期转换为时间点
	auto birthDate = std::chrono::system_clock::from_time_t(std::mktime(&birthTime));

	// 平均寿命
	int avgLifeSpan = 75;

	// 获取当前目录，用于生成启动目录的快捷方式
	wchar_t exePath[MAX_PATH];
	GetModuleFileName(NULL, exePath, MAX_PATH);

	// 检查是否是首次运行
	std::ifstream checkFile("first_run.txt");
	if (!checkFile.is_open()) {
		// 如果是首次运行，创建快捷方式
		createShortcut(exePath, L"MyLifeCounter.lnk");

		// 创建标记文件，表示已经运行过一次
		std::ofstream markFile("first_run.txt");
		markFile.close();
	}
	checkFile.close();
	 // 注册窗口类
    WNDCLASS wndClass = {};
    wndClass.lpfnWndProc = WndProc;
    wndClass.hInstance = GetModuleHandle(NULL);
    wndClass.lpszClassName = L"FloatingWindowClass";
    RegisterClass(&wndClass);

    // 创建窗口
    HWND hwnd = CreateWindowEx(
        0, L"FloatingWindowClass", L"Floating Window",
        WS_OVERLAPPEDWINDOW, // 使用默认的窗口样式
        CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );


	// 消息循环
	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {
		// 获取当前时间
		auto now = std::chrono::system_clock::now();

		// 计算距离结束的总秒数
		auto totalSeconds = std::chrono::duration_cast<std::chrono::seconds>(birthDate + std::chrono::hours(avgLifeSpan * 365 * 24) - now);

		// 将剩余寿命的秒数传递给窗口
		SetWindowLongPtr(hwnd, GWLP_USERDATA, static_cast<LONG_PTR>(totalSeconds.count()));


		PostMessage(hwnd, WM_PAINT,0,0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
