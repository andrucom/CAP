// CAP.cpp: определяет точку входа для приложения.
//

#include <hwinfo/hwinfo.h>
#include <hwinfo/utils/unit.h>

#include <string>
#include <cassert>
#include <vector>

char ver[10] = "0.2.2";
char author[44] = "Чупиков Андрей | ostap_bender";
int inp;

using hwinfo::unit::bytes_to_MiB;
using namespace std;

const auto cpus = hwinfo::getAllCPUs();
const auto gpus = hwinfo::getAllGPUs();
const auto disks = hwinfo::getAllDisks();
const auto mainboard = hwinfo::MainBoard();
const auto ram = hwinfo::Memory();
const auto batteries = hwinfo::getAllBatteries();
const auto os = hwinfo::OS();
const auto net = hwinfo::getAllNetworks();

int main()
{
	cout << "Версия" << "\t\t" << ver << "\n";
	cout << "Разработчик" << "\t" << author << "\n";
	cout << "--------------------------------------------" << "\n\n\n";
	


	do {
		cout << "\n0 - Завершение программы\n1 - CPU\t\t\t\t2 - GPU\t\t3 - Материнская плата\t\t4 - Диск\n5 - Оперативная память\t\t6 - Батарея\t7 - Оперативная система (OS)\t8 - Cеть \n88 - Благодарность\n ";
		cout << "\n>>Ввод:"; 
		cin >> inp;

		switch (inp)
		{
			case 0:
				cout << "\n\n << ЗАВЕРШЕНИЕ ПРОГРАММЫ >>" << "\n\n";
				break;
			case 1:
				system("CLS");

				for (const auto& cpu : cpus)
				{
					cout << " Название: " << "\t\t\t" << cpu.modelName() << "\n";
					cout << " Физические ядра: " << "\t\t" << cpu.numPhysicalCores() << "\n";
					cout << " Логические ядра: " << "\t\t" << cpu.numLogicalCores() << "\n";
					cout << " Макс. Частота: " << "\t\t" << cpu.maxClockSpeed_MHz() - 1 << " GHz" << "\n";
					cout << " Частота по умолчанию: " << "\t\t" << cpu.regularClockSpeed_MHz() - 1 << " GHz" << "\n\n\n";
					cout << " Размер кэша:" << "\n";
					cout << " >L1 \t\t\t\t" << cpu.L1CacheSize_Bytes() << " Кб\n";
					cout << " >L2 \t\t\t\t" << cpu.L2CacheSize_Bytes() << " Кб\n";
					cout << " >L3 \t\t\t\t" << cpu.L3CacheSize_Bytes() << " Кб\n\n";
				}
				cout << "------------------------------------------\n->1 CPU\n";
				break;
			case 2:
				system("CLS");

				for (const auto& gpu : gpus)
				{
					cout << " Производитель: " << "\t\t" << gpu.vendor() << "\n";
					cout << " Наименование: " << "\t\t\t" << gpu.name() << "\n";
					cout << " Память: " << "\t\t\t" << bytes_to_MiB(gpu.memory_Bytes()) << " MB" << "\n";
					cout << " Версия драйвера: " << "\t\t" << gpu.driverVersion() << "\n";
					cout << " vendor_id: " << "\t\t\t" << gpu.vendor_id() << "\n";
					cout << " device_id: " << "\t\t\t" << gpu.device_id() << "\n\n";

				}

				cout << "------------------------------------------\n->2 GPU\n";

				break;
			case 3:
				system("CLS");

				cout << " Производитель: " << "\t\t" << mainboard.vendor() << "\n";
				cout << " Наименование: " << "\t\t\t" << mainboard.name() << "\n";
				cout << " Версия: " << "\t\t\t" << mainboard.version() << "\n";
				cout << " Серийный номер: " << "\t\t" << mainboard.serialNumber() << "\n\n";
				

				cout << "------------------------------------------\n->3 Материнская плата\n";
				break;

			case 4: 
				system("CLS");

				for (const auto& disk : disks)
				{
					cout << " Производитель: " << "\t\t" << disk.vendor() << "\n";
					cout << " Наименование: " << "\t\t\t" << disk.model() << "\n";
					cout << " Память: " << "\t\t\t" << bytes_to_MiB(disk.size_Bytes()) << " MB" << "\n";
					cout << " Серийный номер: " << "\t\t" << disk.serialNumber() << "\n\n";

				}

				cout << "------------------------------------------\n->4 Диск \n";
				break; 
			case 5:

				system("CLS");
				for (const auto& module : ram.modules())
				{
					
					cout << " Производитель: " << "\t\t" << module.vendor << "\n";
					cout << " Наименование: " << "\t\t\t" << module.name << "\n";
					cout << " Модель: " << "\t\t\t" << module.model << "\n";
					cout << " Серийный номер: " << "\t\t" << module.serial_number << "\n";
					cout << " Память: " << "\t\t\t" << bytes_to_MiB(module.total_Bytes) << " MB" << "\n";
					cout << " Частота: " << "\t\t\t" << module.frequency_Hz/1000000 << " MHz" << "\n\n";
				}

				cout << " Память: " << "\t\t" << bytes_to_MiB(ram.total_Bytes()) << "MB" << "\n";
				cout << " Используется: " << "\t\t" << bytes_to_MiB((ram.total_Bytes() - ram.free_Bytes())) << "MB" << "\n";
				cout << " Доступно: " << "\t\t" << bytes_to_MiB(ram.free_Bytes()) << "MB" << "\n\n";

				cout << "------------------------------------------\n->5 Оперативная память\n";

				break;
			case 6:

				system("CLS");
				for (const auto& bat : batteries)
				{
					cout << " Производитель:" << "\t\t" << bat.getVendor() << "\n";
					cout << " Модель:" << "\t\t" << bat.getModel() << "\n";
					cout << " Серийный номер:" << "\t" << bat.getSerialNumber() << "\n";
					cout << " Технология:" << "\t\t" << bat.getTechnology() << "\n\n";
				}
				cout << "------------------------------------------\n->6 Батарея\n";

				break;

			case 7:
				system("CLS");
				cout << " Имя:" << "\t\t" << os.name() << "\n";
				cout << " Сборка:" << "\t" << os.version() << "\n";
				cout << " Ядро:" << "\t\t" << os.kernel() << "\n";
				cout << " 32 бит:" << "\t" << os.is32bit() << "\n";
				cout << " 64 бит:" << "\t" << os.is64bit() << "\n\n";
				cout << "------------------------------------------\n->7 Операционная система\n";



				break;

			case 8:

				system("CLS");
				for (const auto& net : net)
				{
					cout << " interfaceIndex:" << "\t" << net.interfaceIndex() << "\n";
					cout << " Описание:" << "\t\t" << net.description() << "\n";
					cout << " MAC:" << "\t\t\t" << net.mac() << "\n";
					cout << " ip4:" << "\t\t\t" << net.ip4() << "\n";
					cout << " ip6:" << "\t\t\t" << net.ip6() << "\n\n";
				}
				cout << "------------------------------------------\n->8 Cеть\n";

				break;

			default:
				system("CLS");

				cout << "Версия" << "\t\t" << ver << "\n";
				cout << "Разработчик" << "\t" << author << "\n";
				cout << "--------------------------------------------" << "\n\n\n";

				break;

			case 88:
				system("CLS");
				cout << "Хочу выразить свою благодарность своему другу, Dadaskis, спасибо, что решил помочь мне с этой запарой\n\n";
				cout << "Источники:\n HWinfo - https://github.com/lfreist/hwinfo\n\n";

				break;

			case 2005:
				system("CLS");
				
				cout << "ДОБРО ПОЖАЛОВАТЬ В INDEX-0, ЭТО ЛУЧШИЙ ГОРОД ИЗ ОСТАВШИХСЯ\n\nhttps://store.steampowered.com/app/2742480/Index_Purger/\n";
				cout << "------------------------------------------\n->2005 INDEX: PURGER\n";
				break;
		}
	} while (inp != 0);

	system("Pause");
}
