#include "all.reports.screen.h"

void screenAllReports()
{
	char fileName[MAX_FILE_LENGTH];
	printf_s("Introdu numele fisierului in care vrei sa salvezi raportul (formatul csv): ");
	scanf_s("%s", fileName, MAX_FILE_LENGTH);

	if (createFile(fileName) == false)
	{
		printf_s("Eroare la crearea fisierului!\n");
		return;
	}

	Stock stocks[MAX_STOCKS];
	int count = 0;

	getStocks(stocks, &count);

	FILE* file = NULL;
	if (openFile(&file, fileName, "w") == false)
	{
		printf_s("Eroare la deschiderea fisierului!\n");
		return;
	}

	fprintf_s(file, "ID,Nume,Pret Actual,Pret Initial,Crestere,Cantitate\n");
	for (int i = 0; i < count; i++)
	{
		float growth = 100;
		if (stocks[i].originalPrice != 0)
		{
			growth = ((stocks[i].price - stocks[i].originalPrice) / stocks[i].originalPrice) * 100;
		}

		fprintf_s(file, "%llu,%s,%f,%f,%f%%,%d\n", stocks[i].id, stocks[i].name, stocks[i].price, stocks[i].originalPrice, growth, stocks[i].quantity);
	}

	closeFile(file);

	changeMessage("Raportul a fost salvat cu succes!");
	goToMainMenu();
}
