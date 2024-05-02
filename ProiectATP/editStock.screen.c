#include "editStock.screen.h"

void screenEditStock()
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
		printf_s("Selecteaza actiunea pe care doresti sa o editezi: ");
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
	Stock editedStock = getNewStock();

	while (strlen(editedStock.name) == 0 || !isAlpha(editedStock.name))
	{
		printf_s("Introduceti noul nume al actiunii (OLD '%s'): ", stock.name);
		scanf_s("%s", editedStock.name, MAX_STOCK_NAME_LENGTH);

		if (strlen(editedStock.name) == 0 || !isAlpha(editedStock.name))
		{
			changeMessage("Numele actiunii trebuie sa contina doar litere.");
			displayMessage(false);
		}
	}

	transformToUpperCase(editedStock.name);

	while (editedStock.price <= 0)
	{
		printf_s("Introduceti noul pret al actiunii (OLD %f): ", stock.price);
		scanf_s("%f", &editedStock.price);

		if (editedStock.price <= 0)
		{
			changeMessage("Pretul actiunii trebuie sa fie un numar pozitiv.");
			displayMessage(false);
		}
	}

	while (editedStock.quantity <= 0)
	{
		printf_s("Introduceti noua cantitate a actiunii (OLD %d): ", stock.quantity);
		scanf_s("%d", &editedStock.quantity);

		if (editedStock.quantity <= 0)
		{
			changeMessage("Cantitatea actiunii trebuie sa fie un numar pozitiv.\n");
			displayMessage(false);
		}
	}

	editStock(stock.id, editedStock);
}
