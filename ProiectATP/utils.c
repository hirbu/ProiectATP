#include "utils.h"

bool isAlpha(char* string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (!isalpha(string[i]))
		{
			return false;
		}
	}

	return true;
}

void transformToUpperCase(char* string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		string[i] = toupper(string[i]);
	}
}

void clearBuffer()
{
	while (getchar() != '\n');
}

void clearScreen()
{
	system("cls");
}
