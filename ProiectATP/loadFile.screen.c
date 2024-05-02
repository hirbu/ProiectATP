#include "loadFile.screen.h"

void screenLoadFile()
{
	char filename[MAX_FILE_LENGTH];
	printf_s("Introduceti numele fisierului: ");
	scanf_s("%s", filename, MAX_FILE_LENGTH);

	if (checkIfFileExists(filename))
	{
		loadFile(filename);
		changeMessage("Fisierul a fost incarcat cu succes.");
	}
	else
	{
		changeMessage("Fisierul nu a putut fi incarcat.");
	}

	goToMainMenu();
}
