#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

class Logger
{
private:
	std::string logFileName_;
	std::ofstream logFile_;
public:
	Logger(const std::string& logFileName) : logFileName_(logFileName) {
		logFile_.open(logFileName_, std::ios::app); // 打开文件以追加模式写入日志
		if (!logFile_.is_open()) {
			std::cerr << "无法打开日志文件: " << logFileName_ << std::endl;
		}
	}
	~Logger();
	void Log(const std::string& message);
};

