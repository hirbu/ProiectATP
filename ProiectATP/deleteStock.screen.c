#include "deleteStock.screen.h"

void screenDeleteStock()
{
	if (currentFile[0] == '\0')
	{
		changeMessage("Nu exista niciun fisier incarcat.");
		goToMainMenu();
		return;
	}

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
		printf_s("%d. %s %f %d\n", i + 1, stoks[i].name, stoks[i].price, stoks[i].quantity);
	}
	printf_s("\n-1. Revenire la meniul principal\n");
	printf_s("\n---\n\n");

	int stockId = 0;

	while (stockId < 1 || stockId > count)
	{
		printf_s("Selecteaza actiunea pe care doresti sa o stergi: ");
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

	deleteStock(stoks[stockId - 1].id);

	printf_s("\n---\n\n");
}