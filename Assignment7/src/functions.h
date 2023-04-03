#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

void legendMaker();
char *stringToMorse(char* inputBuf, int* errorCode);
char* morseToString( char* inputBuf, int* errorCode);
int endsWithTXT(const char* str);
void commandOperators(int *wrapInt, int *justifyInt, bool *encode, bool *decode, bool *justify, bool *wrap, char **filename, int argc, char *argv[]);
bool errorCheck(FILE *inputFile, char *filename);
void justify(char *string, int max);
void wrap(char *string, int max);

#endif
