#include <hwinfo/hwinfo.h>
#include <hwinfo/utils/unit.h>
#include <string>
#include <filesystem>
#include "capl.h"



namespace fs = std::filesystem;

namespace caplib
{
	

	void capl::printMonitorInfo() {
		// Получаем информацию о различный дисплеях
		DISPLAY_DEVICE dd;
		dd.cb = sizeof(dd);
		int deviceIndex = 0;

		while (EnumDisplayDevices(NULL, deviceIndex, &dd, 0)) {


			// Получение информации о конфигурации монитора
			DEVMODE dm;
			dm.dmSize = sizeof(dm);
			if (EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
			{
				std::cout << "Монитор #" << deviceIndex + 1 << ": \t\t" << dd.DeviceName << "\n";
				std::cout << " Имя: \t\t\t" << dm.dmDeviceName << "\n";
				std::cout << " Разрешение: \t\t" << dm.dmPelsWidth << "x" << dm.dmPelsHeight << "\n";
				std::cout << " Частота обновления: \t" << dm.dmDisplayFrequency << " Гц" << "\n";
				std::cout << " Цвет: \t\t\t" << dm.dmBitsPerPel << " бит" << "\n\n";
			}
			//else
			//{
			//	std::cerr << " Не удалось получить настройки дисплея или дисплей отсутствует!" << "\n\n";
			//}

			deviceIndex++;
		}
	}

	void capl::init(const fs::path path)
	{
		fs::path dir_path = path / "CAP";

		if (fs::exists(dir_path))
		{

		}
		else
		{
			fs::create_directory(dir_path);
		}
	}

	void capl::OpenMainDir(const std::string path)
	{

		std::string fullpath = "explorer " + path;
		std::replace(fullpath.begin(), fullpath.end(), '/', '\\');
		system(fullpath.c_str());


	}

	void capl::StartMainDir(const std::string path)
	{

		std::string fullpath = "start " + path;
		std::replace(fullpath.begin(), fullpath.end(), '/', '\\');
		//fullpath = to_utf8(fullpath);
		system(fullpath.c_str());


	}
}