#include "createFile.screen.h"

void screenCreateFile()
{
	char filename[MAX_FILE_LENGTH];
	printf_s("Introduceti numele fisierului: ");
	scanf_s("%s", filename, MAX_FILE_LENGTH);

	if (createFile(filename) == true)
	{
		changeMessage("Fisierul a fost creat cu succes.");

		if (checkIfFileExists(filename) == true)
		{
			loadFile(filename);
		}
		else
		{
			changeMessage("Fisierul nu a putut fi incarcat.");
		}
	}
	else
	{
		changeMessage("Fisierul nu a putut fi creat.");
	}

	goToMainMenu();
}
