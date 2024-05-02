#pragma once

#include "utils.h"

#define MAX_STOCK_NAME_LENGTH 10
#define MAX_STOCKS 100
#define MAX_DATA_LENGTH 5000

typedef struct
{
	uint64_t id; // since I'm using UNIX time, I'm using uint64_t to handle year 2038 problem
	char name[MAX_STOCK_NAME_LENGTH];
	float originalPrice;
	float price;
	int quantity;
} Stock;

Stock getNewStock();
void recalculateChangeStocks();
void addStock(Stock stock);
void getStocks(Stock stocks[], int* count);
void editStock(uint64_t stock, Stock editedStock);
void updatePrices();
void deleteStock(uint64_t stockId);
