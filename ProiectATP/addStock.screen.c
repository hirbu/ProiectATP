#include "addStock.screen.h"

void screenAddStock()
{
	if (currentFile[0] == '\0')
	{
		changeMessage("Nu a fost incarcat niciun fisier.");
		goToMainMenu();
		return;
	}

	Stock stock = getNewStock();

	while (strlen(stock.name) == 0 || !isAlpha(stock.name))
	{
		printf_s("Introduceti numele actiunii: ");
		scanf_s("%s", stock.name, MAX_STOCK_NAME_LENGTH);

		if (strlen(stock.name) == 0 || !isAlpha(stock.name))
		{
			changeMessage("Numele actiunii trebuie sa contina doar litere.");
			displayMessage(false);
		}
	}

	transformToUpperCase(stock.name);

	while (stock.price <= 0)
	{
		printf_s("Introduceti pretul actiunii: ");
		scanf_s("%f", &stock.price);

		if (stock.price <= 0)
		{
			changeMessage("Pretul actiunii trebuie sa fie un numar pozitiv.");
			displayMessage(false);
		}
	}

	stock.originalPrice = stock.price;

	while (stock.quantity <= 0)
	{
		printf_s("Introduceti cantitatea actiunii: ");
		scanf_s("%d", &stock.quantity);

		if (stock.quantity <= 0)
		{
			changeMessage("Cantitatea actiunii trebuie sa fie un numar pozitiv.\n");
			displayMessage(false);
		}
	}

	int count = 0;
	Stock stocks[MAX_STOCKS];
	getStocks(stocks, &count);

	if (count == MAX_STOCKS)
	{
		changeMessage("Numarul maxim de actiuni a fost atins.");
		goToMainMenu();
		return;
	}

	addStock(stock);

	goToMainMenu();
}
