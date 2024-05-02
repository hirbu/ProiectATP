#include "menu.h"

short currentState = STATE_MAIN_MENU;
char message[MAX_MESSAGE_LENGTH] = "";

void changeMessage(char newMessage[MAX_MESSAGE_LENGTH])
{
	strcpy_s(message, MAX_MESSAGE_LENGTH, newMessage);
}

void displayMessage(bool fancy)
{
	if (message[0] != '\0')
	{
		printf_s("Mesaj: %s\n", message);

		if (fancy == true)
		{
			printf_s("\n---\n\n");
		}

		message[0] = '\0';
	}
}

void displayCurrentFile()
{
	if (currentFile[0] == '\0')
	{
		printf_s("Niciun fisier incarcat\n\n---\n\n");
		return;
	}

	printf_s("Fisier curent: %s\n\n---\n\n", currentFile);
}

void displayScreen()
{
	// Clear screen
	clearScreen();

	// Display title & separator
	printf_s("\\\\\\ ATA - Aplicatie de Tranzactionare a Actiunilor - Andrei Hirbu ///\n\n---\n\n");

	displayCurrentFile();
	displayMessage(true);

	// Display the screen based on the current state
	switch(currentState)
	{
		case STATE_MAIN_MENU:
			screenMainMenu();
			break;
		case STATE_CREATE_FILE:
			screenCreateFile();
			break;
		case STATE_LOAD_FILE:
			screenLoadFile();
			break;
		case STATE_ADD_STOCK:
			screenAddStock();
			break;
		case STATE_EDIT_STOCK:
			screenEditStock();
			break;
		case STATE_UPDATE_PRICES:
			screenUpdatePrice();
			break;
		case STATE_DELETE_STOCK:
			screenDeleteStock();
			break;
		case STATE_REPORTS:
			screenReports();
			break;
		case STATE_REPORTS_ALL:
			screenAllReports();
			break;
		case STATE_REPORTS_PROFITABLE:
			screenProfitableReports();
			break;
		case STATE_REPORTS_SINGLE:
			screenSingleReports();
			break;
		case STATE_EXIT:
			clearScreen();
			break;
		default:
			break;
	}
}

void changeState(short newState)
{
	switch (newState)
	{
		case STATE_MAIN_MENU:
		case STATE_CREATE_FILE:
		case STATE_LOAD_FILE:
		case STATE_ADD_STOCK:
		case STATE_EDIT_STOCK:
		case STATE_UPDATE_PRICES:
		case STATE_DELETE_STOCK:
		case STATE_REPORTS:
		case STATE_REPORTS_ALL:
		case STATE_REPORTS_PROFITABLE:
		case STATE_REPORTS_SINGLE:
		case STATE_EXIT:
			currentState = newState;
			break;
		default:
			changeMessage("Optiunea selectata nu exista.");
			break;
	}
}

void goToMainMenu()
{
	changeState(STATE_MAIN_MENU);
}
