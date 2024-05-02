#include "updatePrice.screen.h"

void screenUpdatePrice()
{
	if (currentFile[0] == '\0')
	{
		changeMessage("Nu exista niciun fisier incarcat.");
		goToMainMenu();
		return;
	}

	updatePrices();

	printf_s("\n---\n\nApasa orice tasta pentru a reveni la meniul principal");
	char c = _getch();
	goToMainMenu();
}
