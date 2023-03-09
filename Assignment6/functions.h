#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void getFileData(char *fileName, char *flags[]);
int newLineCount(char *input);
int byteCount(char *input);
int maxLineLen(char *input);
int wordCount(char *input);
void frequency(char *input);
int includes(char **arr, char *target);