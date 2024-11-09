// CAP.cpp: определяет точку входа для приложения.
//

#include <hwinfo/hwinfo.h>
#include <hwinfo/utils/unit.h>

#include <string>
#include <cassert>
#include <vector>

char ver[10] = "0.2.3";
char author[44] = "Чупиков Андрей | ostap_bender";
int inp;

using hwinfo::unit::bytes_to_MiB;


const auto cpus = hwinfo::getAllCPUs();
const auto gpus = hwinfo::getAllGPUs();
const auto disks = hwinfo::getAllDisks();
const auto mainboard = hwinfo::MainBoard();
const auto ram = hwinfo::Memory();
const auto batteries = hwinfo::getAllBatteries();
const auto os = hwinfo::OS();
const auto net = hwinfo::getAllNetworks();

void printMonitorInfo() {
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
			std::cout << "Монитор #" << deviceIndex + 1 <<": \t\t" << dd.DeviceName << "\n";
			std::cout << " Имя: \t\t\t" << dm.dmDeviceName<< "\n";
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

int main()
{
	std::cout << "Версия" << "\t\t" << ver << "\n";
	std::cout << "Разработчик" << "\t" << author << "\n";
	std::cout << "--------------------------------------------" << "\n\n\n";

	do {
		std::cout << "\n\n1 - CPU\t\t\t\t2 - GPU\t\t3 - Материнская плата\t\t4 - Диск\n5 - Оперативная память\t\t6 - Батарея\t7 - Оперативная система (OS)\t8 - Cеть\n9 - Дисплей\n88 - Благодарность\n ";
		std::cout << "\n>>Ввод: "; 
		std::cin >> inp;

		switch (inp)
		{
			case 0:
				std::cout << "\n\n << ЗАВЕРШЕНИЕ ПРОГРАММЫ >>" << "\n\n";
				break;
			case 1:
				system("CLS");

				for (const auto& cpu : cpus)
				{
					std::cout << " Название: " << "\t\t\t" << cpu.modelName() << "\n";
					std::cout << " Физические ядра: " << "\t\t" << cpu.numPhysicalCores() << "\n";
					std::cout << " Логические ядра: " << "\t\t" << cpu.numLogicalCores() << "\n";
					std::cout << " Частота по умолчанию: " << "\t\t" << cpu.regularClockSpeed_MHz() << " GHz" << "\n\n\n";
					std::cout << " Размер кэша:" << "\n";
					std::cout << " >L1 \t\t\t\t" << cpu.L1CacheSize_Bytes() << " Кб\n";
					std::cout << " >L2 \t\t\t\t" << cpu.L2CacheSize_Bytes() << " Кб\n";
					std::cout << " >L3 \t\t\t\t" << cpu.L3CacheSize_Bytes() << " Кб\n\n";

				}
				std::cout << "------------------------------------------\n->1 CPU\n";
				break;
			case 2:
				system("CLS");

				for (const auto& gpu : gpus)
				{
					std::cout << " Производитель: " << "\t\t" << gpu.vendor() << "\n";
					std::cout << " Наименование: " << "\t\t\t" << gpu.name() << "\n";
					std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(gpu.memory_Bytes()) << " MB" << "\n";
					std::cout << " Версия драйвера: " << "\t\t" << gpu.driverVersion() << "\n";
					std::cout << " vendor_id: " << "\t\t\t" << gpu.vendor_id() << "\n";
					std::cout << " device_id: " << "\t\t\t" << gpu.device_id() << "\n\n";
				}

				std::cout << "------------------------------------------\n->2 GPU\n";

				break;
			case 3:
				system("CLS");

				std::cout << " Производитель: " << "\t\t" << mainboard.vendor() << "\n";
				std::cout << " Наименование: " << "\t\t\t" << mainboard.name() << "\n";
				std::cout << " Версия: " << "\t\t\t" << mainboard.version() << "\n";
				std::cout << " Серийный номер: " << "\t\t" << mainboard.serialNumber() << "\n\n";
				

				std::cout << "------------------------------------------\n->3 Материнская плата\n";
				break;

			case 4: 
				system("CLS");

				for (const auto& disk : disks)
				{
					std::cout << " Производитель: " << "\t\t" << disk.vendor() << "\n";
					std::cout << " Наименование: " << "\t\t\t" << disk.model() << "\n";
					std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(disk.size_Bytes()) << " MB" << "\n";
					std::cout << " Серийный номер: " << "\t\t" << disk.serialNumber() << "\n\n";

				}

				std::cout << "------------------------------------------\n->4 Диск \n";
				break; 
			case 5:

				system("CLS");
				for (const auto& module : ram.modules())
				{
					
					std::cout << " Производитель: " << "\t\t" << module.vendor << "\n";
					std::cout << " Наименование: " << "\t\t\t" << module.name << "\n";
					std::cout << " Модель: " << "\t\t\t" << module.model << "\n";
					std::cout << " Серийный номер: " << "\t\t" << module.serial_number << "\n";
					std::cout << " Память: " << "\t\t\t" << bytes_to_MiB(module.total_Bytes) << " MB" << "\n";
					std::cout << " Частота: " << "\t\t\t" << module.frequency_Hz/1000000 << " MHz" << "\n\n";
				}

				std::cout << " Память: " << "\t\t" << bytes_to_MiB(ram.total_Bytes()) << " MB" << "\n";
				std::cout << " Используется: " << "\t\t" << bytes_to_MiB((ram.total_Bytes() - ram.free_Bytes())) << " MB" << "\n";
				std::cout << " Доступно: " << "\t\t" << bytes_to_MiB(ram.free_Bytes()) << " MB" << "\n\n";

				std::cout << "------------------------------------------\n->5 Оперативная память\n";

				break;
			case 6:

				system("CLS");
				for (const auto& bat : batteries)
				{
					std::cout << " Производитель:" << "\t\t" << bat.getVendor() << "\n";
					std::cout << " Модель:" << "\t\t" << bat.getModel() << "\n";
					std::cout << " Серийный номер:" << "\t" << bat.getSerialNumber() << "\n";
					std::cout << " Технология:" << "\t\t" << bat.getTechnology() << "\n\n";
				}
				std::cout << "------------------------------------------\n->6 Батарея\n";

				break;

			case 7:
				system("CLS");
				std::cout << " Имя:" << "\t\t" << os.name() << "\n";
				std::cout << " Сборка:" << "\t" << os.version() << "\n";
				std::cout << " Ядро:" << "\t\t" << os.kernel() << "\n";
				std::cout << " 32 бит:" << "\t" << os.is32bit() << "\n";
				std::cout << " 64 бит:" << "\t" << os.is64bit() << "\n\n";
				std::cout << "------------------------------------------\n->7 Операционная система\n";



				break;

			case 8:

				system("CLS");

				for (const auto& net : net)
				{
					if (net.ip4().size() > 0 || net.ip6().size() > 0)
					{
						std::cout << " interfaceIndex:" << "\t" << net.interfaceIndex() << "\n";
						std::cout << " Описание:" << "\t\t" << net.description() << "\n";
						std::cout << " MAC:" << "\t\t\t" << net.mac() << "\n";
						std::cout << " ip4:" << "\t\t\t" << net.ip4() << "\n";
						std::cout << " ip6:" << "\t\t\t" << net.ip6() << "\n\n";
					}
				}
				std::cout << "------------------------------------------\n->8 Cеть\n";

				break;

			case 9:
				system("CLS");

				printMonitorInfo();

				std::cout << "------------------------------------------\n->9 Дисплей\n";

				break;

			default:
				system("CLS");

				std::cout << "Версия" << "\t\t" << ver << "\n";
				std::cout << "Разработчик" << "\t" << author << "\n";
				std::cout << "--------------------------------------------" << "\n\n\n";

				break;

			case 88:
				system("CLS");
				std::cout << "Хочу выразить свою благодарность своему другу, Dadaskis, спасибо, что решил помочь мне с этой запарой\n\n";
				std::cout << "Источники:\n HWinfo - https://github.com/lfreist/hwinfo\n\n";

				break;

			case 2005:
				system("CLS");
				
				std::cout << "ДОБРО ПОЖАЛОВАТЬ В INDEX-0, ЭТО ЛУЧШИЙ ГОРОД ИЗ ОСТАВШИХСЯ\n\nhttps://store.steampowered.com/app/2742480/Index_Purger/\n";
				std::cout << "------------------------------------------\n->2005 INDEX: PURGER\n";
				break;

		}
	} while (inp != 0);

	system("Pause");
}



