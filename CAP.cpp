#include <hwinfo/hwinfo.h>
#include <hwinfo/utils/unit.h>
#include "third_party/CAPL/capl.h"
#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <filesystem>

caplib::capl capl;

std::string ver = "0.3.1 WIP";
std::string author = "Чупиков Андрей | ostap_bender";
int inp;

using hwinfo::unit::bytes_to_MiB;
namespace fs = std::filesystem;

const auto cpus = hwinfo::getAllCPUs();
const auto gpus = hwinfo::getAllGPUs();
const auto disks = hwinfo::getAllDisks();
const auto mainboard = hwinfo::MainBoard();
const auto ram = hwinfo::Memory();
const auto batteries = hwinfo::getAllBatteries();
const auto net = hwinfo::getAllNetworks();
const auto os = hwinfo::OS();




int main()
{



	capl.init(capl.get_appdata_path());


	std::string file_path = capl.get_appdata_path().string() + "/CAP/report.txt";
	file_path = capl.to_utf8(file_path);


	DISPLAY_DEVICE dd;
	dd.cb = sizeof(dd);
	int deviceIndex = 0;
	

	setlocale(LC_ALL, "ru_RU.UTF-8");
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);


	std::ofstream f;
	f.open(file_path, std::ios::app); // Режим добавления
	f.close(); // Просто создаём/открываем и закрываем

	std::cout << "Версия" << "\t\t" << ver << "\n";
	std::cout << "Разработчик" << "\t" << author << "\n";
	std::cout << "--------------------------------------------" << "\n\n\n";





	do {
		std::cout << "\n\n1 - CPU\t\t\t\t2 - GPU\t\t3 - Материнская плата\t\t4 - Диск\n5 - Оперативная память\t\t6 - Батарея\t7 - Оперативная система (OS)\t8 - Cеть\n9 - Дисплей\t\t\t\t\t10- Составить отчет\n\n88 - Благодарность\n ";
		std::cout << "\n>>Ввод: "; 
		std::cin >> inp;

		switch (inp)
		{
			case 0:
				std::cout << "\n\n << ЗАВЕРШЕНИЕ ПРОГРАММЫ >>" << "\n\n";
				break;
			// CPU
			case 1:
				system("CLS");

				for (const auto& cpu : cpus)
				{
					std::cout << " Производитель: " << "\t\t" << capl.to_utf8(cpu.vendor()) << "\n"; 
					std::cout << " Название: " << "\t\t\t" << capl.to_utf8(cpu.modelName()) << "\n\n";

					std::cout << " Физические ядра: " << "\t\t" << cpu.numPhysicalCores() << "\n";
					std::cout << " Логические ядра: " << "\t\t" << cpu.numLogicalCores() << "\n";
					std::cout << " Частота по умолчанию: " << "\t\t" << cpu.regularClockSpeed_MHz() << " MHz" << "\n\n\n";

					std::cout << " Размер кэша:" << "\n";
					std::cout << " !Может выводить некорректную информацию!" << "\n";
					std::cout << " >L1 \t\t\t\t" << cpu.L1CacheSize_Bytes() << " Кб\n";
					std::cout << " >L2 \t\t\t\t" << cpu.L2CacheSize_Bytes() << " Кб\n";
					std::cout << " >L3 \t\t\t\t" << cpu.L3CacheSize_Bytes() << " Кб\n\n";
				}
				std::cout << "------------------------------------------\n->1 CPU\n";
				break;
			// GPU
			case 2:
				system("CLS");

				for (const auto& gpu : gpus)
				{
					
					std::cout << " Производитель: " << "\t\t" << capl.to_utf8(gpu.vendor()) << "\n";
					std::cout << " Наименование: " << "\t\t\t" << capl.to_utf8(gpu.name()) << "\n";
					std::cout << " Видеопамять: " << "\t\t\t" << bytes_to_MiB(gpu.memory_Bytes()) << " MB" << "\n";
					std::cout << " Версия драйвера: " << "\t\t" << gpu.driverVersion() << "\n";
					std::cout << "---\n";
					std::cout << " vendor_id: " << "\t\t\t" << gpu.vendor_id() << "\n";
					std::cout << " device_id: " << "\t\t\t" << gpu.device_id() << "\n\n\n";
				}

				std::cout << "------------------------------------------\n->2 GPU\n";

				break;
			// MAINBOARD
			case 3:
				system("CLS");

				std::cout << " Производитель: " << "\t\t" << capl.to_utf8(mainboard.vendor()) << "\n";
				std::cout << " Наименование: " << "\t\t\t" << capl.to_utf8(mainboard.name()) << "\n";
				std::cout << " Версия: " << "\t\t\t" << mainboard.version() << "\n";
				std::cout << " Серийный номер: " << "\t\t" << mainboard.serialNumber() << "\n\n";
				

				std::cout << "------------------------------------------\n->3 Материнская плата\n";
				break;
			// DISK
			case 4: 
				system("CLS");

				for (const auto& disk : disks)
				{
					//std::cout << " Производитель: " << "\t\t" << to_utf8(disk.vendor())  << "\n";
					std::cout << " Наименование: " << "\t\t\t" << capl.to_utf8(disk.model()) << "\n";
					std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(disk.size_Bytes()) << " MB" << "\n";
					std::cout << " Серийный номер: " << "\t\t" << disk.serialNumber() << "\n\n";

				}

				std::cout << "------------------------------------------\n->4 Диск \n";
				break; 
			// RAM
			case 5:

				system("CLS");
				for (const auto& module : ram.modules())
				{
					
					std::cout << " Производитель: " << "\t\t" << capl.to_utf8(module.vendor) << "\n";
					std::cout << " Наименование: " << "\t\t\t" << capl.to_utf8(module.name) << "\n";
					std::cout << " Модель: " << "\t\t\t" << capl.to_utf8(module.model) << "\n";
					std::cout << " Серийный номер: " << "\t\t" << module.serial_number << "\n";
					std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(module.total_Bytes) << " MB" << "\n";
					std::cout << " Частота: " << "\t\t\t" << module.frequency_Hz/1000000 << " MHz" << "\n\n";
				}

				std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(ram.total_Bytes()) << " MB" << "\n";
				//std::cout << " Используется: " << "\t\t" << bytes_to_MiB((ram.total_Bytes() - ram.free_Bytes())) << " MB" << "\n";
				//std::cout << " Доступно: " << "\t\t" << bytes_to_MiB(ram.free_Bytes())<< " MB" << "\n\n";

				std::cout << "------------------------------------------\n->5 Оперативная память\n";

				break;

			// BATTERIES
			case 6:

				system("CLS");
				for (const auto& bat : batteries)
				{
					std::cout << " Производитель:" << "\t\t" << capl.to_utf8(bat.getVendor()) << "\n";
					std::cout << " Модель:" << "\t\t" << capl.to_utf8(bat.getModel()) << "\n";
					std::cout << " Серийный номер:" << "\t" << bat.getSerialNumber() << "\n";
					std::cout << " Технология:" << "\t\t" << capl.to_utf8(bat.getTechnology()) << "\n\n";
				}
				std::cout << "------------------------------------------\n->6 Батарея\n";

				break;

			// OS
			case 7:
				system("CLS");
				std::cout << " Имя:" << "\t\t" << capl.to_utf8(os.name()) << "\n";
				if (os.is32bit())  std::cout << " Система: \t32 бита\n";
				if (os.is64bit())  std::cout << " Система: \t64 бита\n";
				std::cout << " Сборка:" << "\t" << os.version() << "\n";
				std::cout << " Ядро:" << "\t\t" << os.kernel() << "\n";
				std::cout << "\n\n";
				//std::cout << " 32 бит:" << "\t" << os.is32bit() << "\n";
				//std::cout << " 64 бит:" << "\t" << os.is64bit() << "\n\n";
				std::cout << "------------------------------------------\n->7 Операционная система\n";



				break;
			// NET
			case 8:

				system("CLS");

				for (const auto& net : net)
				{
					if (net.ip4().size() > 0 || net.ip6().size() > 0)
					{
						std::cout << " interfaceIndex:" << "\t" << net.interfaceIndex() << "\n";
						std::cout << " Описание:" << "\t\t" << capl.to_utf8(net.description()) << "\n";
						std::cout << " MAC:" << "\t\t\t" << net.mac() << "\n";
						std::cout << " ip4:" << "\t\t\t" << net.ip4() << "\n";
						std::cout << " ip6:" << "\t\t\t" << net.ip6() << "\n\n";
					}
				}
				std::cout << "------------------------------------------\n->8 Cеть\n";

				break;
			// DISPLAY
			case 9:
				system("CLS");

				capl.printMonitorInfo();

				std::cout << "------------------------------------------\n->9 Дисплей\n";

				break;

			case 10:
				system("CLS");
				f.open(file_path, std::ios::binary);

				for (const auto& cpu : cpus)
				{

					f << "=================CPU=================" << "\n";
					f << " Производитель: " << "\t\t" << capl.to_utf8(cpu.vendor()) << "\n";
					f << " Название: " << "\t\t\t" << capl.to_utf8(cpu.modelName()) << "\n\n";

					f << " Физические ядра: " << "\t\t" << cpu.numPhysicalCores() << "\n";
					f << " Логические ядра: " << "\t\t" << cpu.numLogicalCores() << "\n";
					f << " Частота по умолчанию: " << "\t\t" << cpu.regularClockSpeed_MHz() << " MHz" << "\n\n\n";

					f << " Размер кэша:" << "\n";
					f << " !Может выводить некорректную информацию!" << "\n";
					f << " >L1 \t\t\t\t" << cpu.L1CacheSize_Bytes() << " Кб\n";
					f << " >L2 \t\t\t\t" << cpu.L2CacheSize_Bytes() << " Кб\n";
					f << " >L3 \t\t\t\t" << cpu.L3CacheSize_Bytes() << " Кб\n\n";
					
				}

				f << "=================GPU=================\r\n" << "\n";
				for (const auto& gpu : gpus)
				{
					f << " Производитель: " << "\t\t" << capl.to_utf8(gpu.vendor()) << "\n";
					f << " Наименование: " << "\t\t\t" << capl.to_utf8(gpu.name()) << "\n";
					f << " Видеопамять: " << "\t\t\t" << bytes_to_MiB(gpu.memory_Bytes()) << " MB" << "\n";
					f << " Версия драйвера: " << "\t\t" << gpu.driverVersion() << "\n";
					f << "---\n";
					f << " vendor_id: " << "\t\t\t" << gpu.vendor_id() << "\n";
					f << " device_id: " << "\t\t\t" << gpu.device_id() << "\n\n";
				}
				std::cout << "\n\n\n";

				f << "==========Материнская плата==========\r\n" << "\n";
				f << " Производитель: " << "\t\t" << capl.to_utf8(mainboard.vendor()) << "\n";
				f << " Наименование: " << "\t\t\t" << capl.to_utf8(mainboard.name()) << "\n";
				f << " Версия: " << "\t\t\t" << mainboard.version() << "\n";
				f << " Серийный номер: " << "\t\t" << mainboard.serialNumber() << "\n\n";


				f << "================Диск=================\r\n" << "\n";
				for (const auto& disk : disks)
				{
					//f << " Производитель: " << "\t\t" << disk.vendor() << "\n";
					f << " Наименование: " << "\t\t\t" << capl.to_utf8(disk.model()) << "\n";
					f << " Память: " << "\t\t\t" << bytes_to_MiB(disk.size_Bytes()) << " MB" << "\n";
					f << " Серийный номер: " << "\t\t" << disk.serialNumber() << "\n\n";

				}

				f << "=================ОЗУ=================\r\n" << "\n";
				for (const auto& module : ram.modules())
				{

					f << " Производитель: " << "\t\t" << capl.to_utf8(module.vendor) << "\n";
					f << " Наименование: " << "\t\t\t" << capl.to_utf8(module.name) << "\n";
					f << " Модель: " << "\t\t\t" << capl.to_utf8(module.model) << "\n";
					f << " Серийный номер: " << "\t\t" << module.serial_number << "\n";
					f << " Память: " << "\t\t\t" << bytes_to_MiB(module.total_Bytes) << " MB" << "\n";
					f << " Частота: " << "\t\t\t" << module.frequency_Hz / 1000000 << " MHz" << "\n\n";
				}

				f << " Память: " << "\t\t" << bytes_to_MiB(ram.total_Bytes()) << " MB" << "\n";

				f << "===============БАТАРЕЯ===============\r\n" << "\n";
				for (const auto& bat : batteries)
				{
					f << " Производитель:" << "\t\t" << capl.to_utf8(bat.getVendor()) << "\n";
					f << " Модель:" << "\t\t" << capl.to_utf8(bat.getModel()) << "\n";
					f << " Серийный номер:" << "\t" << bat.getSerialNumber() << "\n";
					f << " Технология:" << "\t\t" << bat.getTechnology() << "\n\n";
				}

				f << "==================OS=================\r\n" << "\n";
				f << " Имя:" << "\t\t" << capl.to_utf8(os.name()) << "\n";
				if (os.is32bit())  f << " Система: \t32 бита\n";
				if (os.is64bit())  f << " Система: \t64 бита\n";
				f << " Сборка:" << "\t" << os.version() << "\n";
				f << " Ядро:" << "\t\t" << os.kernel() << "\n";
				f << "\n\n";

				f << "================СЕТЬ================\r\n" << "\n";
				for (const auto& net : net)
				{
					if (net.ip4().size() > 0 || net.ip6().size() > 0)
					{
						f << " interfaceIndex:" << "\t" << capl.to_utf8(net.interfaceIndex()) << "\n";
						f << " Описание:" << "\t\t" << capl.to_utf8(net.description()) << "\n";
						f << " MAC:" << "\t\t\t" << net.mac() << "\n";
						f << " ip4:" << "\t\t\t" << net.ip4() << "\n";
						f << " ip6:" << "\t\t\t" << net.ip6() << "\n\n";
					}
				}

				f << "==============МОНИТОР==============\r\n" << "\n";



				while (EnumDisplayDevices(NULL, deviceIndex, &dd, 0)) {


					// Получение информации о конфигурации монитора
					DEVMODE dm;
					dm.dmSize = sizeof(dm);
					if (EnumDisplaySettings(dd.DeviceName, ENUM_CURRENT_SETTINGS, &dm))
					{
						f << "Монитор #" << deviceIndex + 1 << ": \t\t" << dd.DeviceName << "\n";
						f << " Имя: \t\t\t" << dm.dmDeviceName << "\n";
						f << " Разрешение: \t\t" << dm.dmPelsWidth << "x" << dm.dmPelsHeight << "\n";
						f << " Частота обновления: \t" << dm.dmDisplayFrequency << " Гц" << "\n";
						f << " Цвет: \t\t\t" << dm.dmBitsPerPel << " бит" << "\n\n";
					}

					deviceIndex++;
				}

				f.close();
				capl.StartMainDir(file_path);
				std::cout << "!!! ГОТОВО !!!\n";
				std::cout << "------------------------------------------\n->10 Отчет\n";

				break;

			// DEFAULT
			default:
				system("CLS");

				std::cout << "Версия" << "\t\t" << ver << "\n";
				std::cout << "Разработчик" << "\t" << author << "\n";
				std::cout << "--------------------------------------------" << "\n\n\n";

				break;
			// CREDITS
			case 88:
				system("CLS");
				std::cout << "Хочу выразить свою благодарность своему другу, Dadaskis, спасибо, что решил помочь мне с этой запарой\n\n";
				std::cout << "Источники:\n HWinfo - https://github.com/lfreist/hwinfo\n\n";

				break;
			// INDEX
			case 2005:
				system("CLS");
				
				std::cout << "ДОБРО ПОЖАЛОВАТЬ В INDEX-0, ЭТО ЛУЧШИЙ ГОРОД ИЗ ОСТАВШИХСЯ\n\nhttps://store.steampowered.com/app/2742480/Index_Purger/\n";
				std::cout << "------------------------------------------\n->2005 INDEX: PURGER\n";
				break;

		}
	} while (inp != 0);

	system("Pause");
}



