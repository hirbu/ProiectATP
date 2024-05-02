#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>

#include "menu.h"
#include "file.h"
#include "stock.h"
#include "screens.h"

#ifdef __has_include
#  if __has_include(<curl/curl.h>)
#    include <curl/curl.h>
#    define CURL_AVAILABLE
#  endif
#endif

bool isAlpha(char* string);
void transformToUpperCase(char* string);
void clearBuffer();
void clearScreen();
