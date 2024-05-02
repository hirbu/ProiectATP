#include "single.reports.screen.h"

void screenSingleReports() 
{
	Stock stoks[MAX_STOCKS];
	int count = 0;

	getStocks(stoks, &count);

	if (count == 0)
	{
		changeMessage("Nu exista actiuni in fisier.");
		goToMainMenu();
		return;
	}

	printf_s("Actiuni disponibile:\n");
	for (int i = 0; i < count; i++)
	{
		printf_s("%d. %s\n", i + 1, stoks[i].name);
	}
	printf_s("\n-1. Revenire la meniul principal\n");
	printf_s("\n---\n\n");

	int stockId = 0;

	while (stockId < 1 || stockId > count)
	{
		printf_s("Selecteaza actiunea pe care doresti sa o vezi: ");
		scanf_s("%d", &stockId);

		if (stockId == -1)
		{
			goToMainMenu();
			return;
		}

		if (stockId < 1 || stockId > count)
		{
			changeMessage("Actiunea selectata nu exista.");
			displayMessage(false);
		}
	}

	printf_s("\n---\n\n");

	Stock stock = stoks[stockId - 1];

	printf_s("ID:        %llu\n", stock.id);
	printf_s("Nume:      %s\n", stock.name);
	printf_s("Pret:      %f\n", stock.price);
	printf_s("Cantitate: %d\n", stock.quantity);

	printf_s("\n---\n\nApasa orice tasta pentru a reveni la meniul principal.");
	char c = _getch();
	goToMainMenu();
}
