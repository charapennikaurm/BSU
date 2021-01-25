//-----------------------------------------------
//главный файл
//-----------------------------------------------
#include "Head1.h"


int main(int argc, char* argv[])
{
	char  orig_file1[] = "tickets.txt"; 
	char orig_file2[] = "avia.txt";
	char bin_orig[] = "M1.bin";
	char bin_orig1[] = "tickets.bin";
	char bin_orig2[] = "avia.bin";
	char  txt_out[] = "out.txt";   

	SortT(orig_file1);
	FTxtToBinFile(orig_file1, bin_orig1);
	TxtToBinFile(orig_file2, bin_orig2);
	SortC(bin_orig2);
	//исходные файлы отсортированы и бинарные
	//слияние двух бинарных файлов

	string s;
	double time;
	int fln;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	//SortAndMerge(orig_file1, orig_file2, orig_merge);
	const int n = 10;
	string xPrmt[n] =
	{
	 "1.Записать текстовые файлы в бинарный файл",
	 "2.Вывод содержимого бинарного файла",
	 "3.Наличие свободных мест на рейс(по месту прибытия и времени отправления)",
	 "4.Получить номер и пункт назначения рейса с наибольшим временем полета",
	 "5.Обновить для указанного рейса время вылета и время прибытия",
	 "6.Удалить из списка рейсы на Берлин и Варшаву",
	 "7.Поменять местами рейсы на Москву",
	 "8.Упорядочить рейсы по пункту назначения",
	 "9.Записать данные в текстовый файл",
	 "0.Завершить"
	};
	for (;;)
	{
		//system("cls");
		for (int i = 0; i < n; ++i)
			cout << xPrmt[i] << endl;
		cout << endl;
		int nMenu;
		cin >> nMenu;
		switch (nMenu)
		{
		case 0:
			break;
		case 1:
			BinMerge(bin_orig1, bin_orig2, bin_orig);
			break;
		case 2:
			FFileToScreen(bin_orig);
			break;
		case 3:
			cout << "Введите время отправления: ";
			cin >> time;
			cout << "Введите место прибытие: ";
			cin >> s;
			char depar[20]; strcpy(depar, s.c_str());
			if (FreeSpaces(bin_orig, depar, time) == -1) cout << "Такого рейса не существует" << endl;
			else cout << "Осталось " << FreeSpaces(bin_orig, depar, time) << " мест" << endl;
			break;
		case 4:
			MaxFlightTime(bin_orig);
			break;
		case 5:
			cout << "Введите номер рейса,для которого необходимо внести изменения: ";
			cin >> fln;
			Update(bin_orig, fln);
			break;
		case 6:
			DeleteWB(bin_orig);
			cout << "Рейсы на Берлин и Варшаву удалены!" << endl;
			break;
		case 7:
			SwapMSC(bin_orig);
			break;
		case 8:
			SortByDestination(bin_orig);
			cout << "Файл отсортирован по пункту назначения!" << endl;
			break;
		case 9:
			FBinToTxtFile(bin_orig, txt_out);
			cout << endl;
			break;
		}
		if (nMenu == 0) break;
	}
	return 0;
}