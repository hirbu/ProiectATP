#include "stock.h"

Stock getNewStock()
{
	Stock stock;
	time(&stock.id);
	strcpy_s(stock.name, MAX_STOCK_NAME_LENGTH, "");
	stock.originalPrice = 0.0f;
	stock.price = 0.0f;
	stock.quantity = 0;

	return stock;
}

void addStock(Stock stock)
{
	FILE* file = NULL;

	if (openFile(&file, currentFile, "a") == false)
	{
		changeMessage("Eroare la deschiderea fisierului.");
		return;
	}

	fprintf_s(file, "%llu %s %f %f %d\n", stock.id, stock.name, stock.originalPrice, stock.price, stock.quantity);
	changeMessage("Actiunea a fost adaugata cu succes.");
	closeFile(file);
}

void getStocks(Stock stocks[], int* count)
{
	FILE* file = NULL;

	if (openFile(&file, currentFile, "r") == false)
	{
		changeMessage("Eroare la deschiderea fisierului.");
		return;
	}

	*count = 0;
	while (fscanf_s(file, "%llu %s %f %f %d\n", &stocks[*count].id, stocks[*count].name, MAX_STOCK_NAME_LENGTH, &stocks[*count].originalPrice, &stocks[*count].price, &stocks[*count].quantity) != EOF)
	{	
		(*count)++;
	}

	closeFile(file);
}

void editStock(uint64_t stockId, Stock editedStock)
{
	char tempFileName[MAX_FILE_LENGTH] = "temp";
	FILE* file = NULL;
	FILE* tempFile = NULL;

	if (openFile(&file, currentFile, "r") == false)
	{
		changeMessage("Eroare la deschiderea fisierului.");
		return;
	}

	if (createFile(tempFileName) == false)
	{
		changeMessage("Eroare la creearea fisierului temporar.");
		closeFile(file);
		return;
	}

	if (openFile(&tempFile, tempFileName, "w") == false)
	{
		changeMessage("Eroare la deschiderea fisierului temporar.");
		closeFile(file);
		return;
	}

	Stock stock;
	while (fscanf_s(file, "%llu %s %f %f %d\n", &stock.id, stock.name, MAX_STOCK_NAME_LENGTH, &stock.originalPrice, &stock.price, &stock.quantity) != EOF)
	{
		if (stock.id == stockId)
		{
			fprintf_s(tempFile, "%llu %s %f %f %d\n", stock.id, editedStock.name, stock.originalPrice, editedStock.price, editedStock.quantity);
		}
		else
		{
			fprintf_s(tempFile, "%llu %s %f %f %d\n", stock.id, stock.name, stock.originalPrice, stock.price, stock.quantity);
		}
	}

	closeFile(file);
	closeFile(tempFile);

	if (remove(currentFile) != 0)
	{
		changeMessage("Eroare la stergerea fisierului vechii.");
		return;
	}

	if (rename(tempFileName, currentFile) != 0)
	{
		changeMessage("Eroare la redenumirea fisierului temporar.");
		return;
	}

	changeMessage("Actiunea a fost editata cu succes.");
	goToMainMenu();
}

void editStocks(Stock stocks[], int count)
{
	FILE* file = NULL;

	if (openFile(&file, currentFile, "w") == false)
	{
		changeMessage("Eroare la deschiderea fisierului.");
		return;
	}

	for (int i = 0; i < count; i++)
	{
		fprintf_s(file, "%llu %s %f %f %d\n", stocks[i].id, stocks[i].name, stocks[i].originalPrice, stocks[i].price, stocks[i].quantity);
	}

	changeMessage("Actiunile au fost editate cu succes.");
	closeFile(file);
}

#ifdef CURL_AVAILABLE
size_t writeCallback(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realSize = size * nmemb;
	char* dataString = (char*)data;

	for (size_t i = 0; i < realSize; i++)
	{
		dataString[i] = *((char*)ptr + i);
	}

	return realSize;
}

void updatePrices()
{
	Stock stocks[MAX_STOCKS];
	int count = 0;

	getStocks(stocks, &count);
	
	char* url = "https://api.mockaroo.com/api/427b1ba0?count=25&key=d5036270";
	char data[MAX_DATA_LENGTH] = "";

	CURL* curl = curl_easy_init();
	CURLcode res;

	if (!curl)
	{
		changeMessage("Eroare la initializarea CURL.");
		return;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, data);

	printf_s("Se executa request-ul HTTP...\n\n");

	res = curl_easy_perform(curl);

	if (res != CURLE_OK)
	{
		changeMessage("Eroare la request-ul HTTP.");
		return;
	}

	char* context = NULL;
	char* line = strtok_s(data, "\n", &context);
	while (line != NULL)
	{
		char* token = strtok_s(line, ",", &line);
		char name[MAX_STOCK_NAME_LENGTH] = "";
		strcpy_s(name, MAX_STOCK_NAME_LENGTH, token);

		token = strtok_s(NULL, ",", &line);
		
		if (token != NULL)
		{
			bool found = false;
			for (int i = 0; i < count; i++)
			{
				if (strcmp(stocks[i].name, name) == 0)
				{
					stocks[i].price = strtof(token, NULL);
					printf_s("Noul pret al actiunii '%s' este de %f\n", stocks[i].name, stocks[i].price);
					found = true;
					break;
				}
			}
		}

		line = strtok_s(NULL, "\n", &context);
	}

	editStocks(stocks, count);
	curl_easy_cleanup(curl);

	changeMessage("Preturile actiunilor au fost actualizate cu succes.");
}
#else
void updatePrices()
{
	Stock stocks[MAX_STOCKS];
	int count = 0;

	getStocks(stocks, &count);

	for (int i = 0; i < count; i++)
	{
		stocks[i].price = (float)(rand() % 1000) / 100;
		printf_s("Noul pret al actiunii '%s' este de %f\n", stocks[i].name, stocks[i].price);
	}

	editStocks(stocks, count);

	changeMessage("Preturile actiunilor au fost actualizate cu succes.");
}
#endif

void deleteStock(uint64_t stockId)
{
	char tempFileName[MAX_FILE_LENGTH] = "temp";
	FILE* file = NULL;
	FILE* tempFile = NULL;

	if (openFile(&file, currentFile, "r") == false)
	{
		changeMessage("Eroare la deschiderea fisierului.");
		return;
	}

	if (createFile(tempFileName) == false)
	{
		changeMessage("Eroare la creearea fisierului temporar.");
		closeFile(file);
		return;
	}

	if (openFile(&tempFile, tempFileName, "w") == false)
	{
		changeMessage("Eroare la deschiderea fisierului temporar.");
		closeFile(file);
		return;
	}

	Stock stock;
	while (fscanf_s(file, "%llu %s %f %f %d\n", &stock.id, stock.name, MAX_STOCK_NAME_LENGTH, &stock.originalPrice, &stock.price, &stock.quantity) != EOF)
	{
		if (stock.id != stockId)
		{
			fprintf_s(tempFile, "%llu %s %f %f %d\n", stock.id, stock.name, stock.originalPrice, stock.price, stock.quantity);
		}
	}

	closeFile(file);
	closeFile(tempFile);

	if (remove(currentFile) != 0)
	{
		changeMessage("Eroare la stergerea fisierului vechii.");
		return;
	}

	if (rename(tempFileName, currentFile) != 0)
	{
		changeMessage("Eroare la redenumirea fisierului temporar.");
		return;
	}

	changeMessage("Actiunea a fost stearsa cu succes.");
	goToMainMenu();
}
