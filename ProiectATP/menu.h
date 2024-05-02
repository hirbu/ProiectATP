#pragma once

#include "utils.h"

#define STATE_MAIN_MENU 0
#define STATE_CREATE_FILE 1
#define STATE_LOAD_FILE 2
#define STATE_ADD_STOCK 3
#define STATE_EDIT_STOCK 4
#define STATE_UPDATE_PRICES 5
#define STATE_DELETE_STOCK 6
#define STATE_REPORTS 7

#define STATE_REPORTS_ALL 101
#define STATE_REPORTS_PROFITABLE 102
#define STATE_REPORTS_SINGLE 103

#define STATE_EXIT -1

#define MAX_MESSAGE_LENGTH 100

extern short currentState;
extern char message[MAX_MESSAGE_LENGTH];

void displayScreen();
void changeMessage(char newMessage[MAX_MESSAGE_LENGTH]);
void displayMessage(bool fancy);
void displayCurrentFile();
void changeState(short newState);
void goToMainMenu();
