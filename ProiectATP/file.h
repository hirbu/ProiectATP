#pragma once

#include "utils.h"

#define MAX_FILE_LENGTH 100

extern char currentFile[MAX_FILE_LENGTH];

bool checkIfFileExists(char* filename);
bool createFile(char* filename);
bool openFile(FILE** file, char* filename, char* mode);
bool closeFile(FILE* file);
void loadFile(char* filename);
