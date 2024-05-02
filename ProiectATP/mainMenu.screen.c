#include "mainMenu.screen.h"

void screenMainMenu()
{
	printf_s("1. Creare fisier\n");
	printf_s("2. Incarcare fisier\n");
	printf_s("3. Adaugare actiune\n");
	printf_s("4. Editare actiune\n");
	printf_s("5. Actualizare preturi\n");
	printf_s("6. Stergere actiune\n");
	printf_s("7. Rapoarte\n");

	printf_s("\n-1. Iesire\n\n\n");

	// Get user input
	short newState;
	printf_s("Selecteaza optiunea dorita: ");
	scanf_s("%hd", &newState);
	changeState(newState);

	// Clear input buffer
	clearBuffer();
}
