#pragma once

#include <filesystem>
#include <stringapiset.h>

namespace fs = std::filesystem;

namespace caplib
{
	class capl
	{
	public:
		std::string to_utf8(const std::string& str) 
		{
			int size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
			std::wstring wstr(size, 0);
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wstr[0], size);

			int utf8_size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
			std::string utf8_str(utf8_size, 0);
			WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &utf8_str[0], utf8_size, nullptr, nullptr);

			return utf8_str;
		}

		fs::path get_appdata_path()
		{
		#ifdef _WIN32
			return fs::path(std::getenv("LOCALAPPDATA"));
		#else
			return fs::path(std::getenv("LOCALAPPDATA"));
			std::string placeholder;
			std::cout << "!!! ме WINDOWS !!!";
			return placeholder;
		#endif

		}

		void printMonitorInfo();

		void init(const fs::path path);

		void OpenMainDir(const std::string path);

		void StartMainDir(const std::string path);

	};
}