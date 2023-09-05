#include "Logger.h"



Logger::~Logger()
{
}

void Logger::Log(const std::string& message)
{
	if (logFile_.is_open()) {
		std::time_t now = std::time(nullptr);
		char timestamp[20];
		std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

		logFile_ << "[" << timestamp << "] " << message << std::endl;
		logFile_.flush(); // 立即将日志写入文件
	}
}
