#include "file.h"

char currentFile[MAX_FILE_LENGTH] = "";

bool checkIfFileExists(char* filename)
{
	if (filename == NULL || filename[0] == '\0') 
	{
		return false;
	}

	FILE* file;
	fopen_s(&file, filename, "r");

	if (file == NULL) 
	{
		return false;
	}

	fclose(file);
	return true;
}

bool createFile(char* filename)
{
	FILE* file;
	fopen_s(&file, filename, "w");

	if (file == NULL)
	{
		return false;
	}

	if (closeFile(file) == false)
	{
		return false;
	}

	return true;
}

bool openFile(FILE** file, char* filename, char* mode)
{
	if (checkIfFileExists(filename) == false)
	{
		return false;
	}

	fopen_s(file, filename, mode);

	return true;
}

bool closeFile(FILE* file)
{
	if (file == NULL)
	{
		return false;
	}

	fclose(file);
	return true;
}

void loadFile(char* filename)
{
	strcpy_s(currentFile, MAX_FILE_LENGTH, filename);
}
