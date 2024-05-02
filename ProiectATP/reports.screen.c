#include "reports.screen.h"

void screenReports()
{
	if (currentFile[0] == '\0')
	{
		changeMessage("Nu exista niciun fisier incarcat.");
		goToMainMenu();
		return;
	}

	printf_s("1. Exporteaza toate actiunile\n");
	printf_s("2. Exporteaza actiunile profitabile\n");
	printf_s("3. Vizualizeaza o actiune\n");

	printf_s("\n-1. Inapoi\n\n\n");

	// Get user input
	short newState;
	printf_s("Selecteaza optiunea dorita: ");
	scanf_s("%hd", &newState);

	if (newState == -1)
	{
		goToMainMenu();
		return;
	}

	changeState(100 + newState);

	// Clear input buffer
	clearBuffer();
}
