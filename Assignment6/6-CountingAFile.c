#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <C:\Users\antho\Desktop\C-Programming-223C\Assignment6\functions.h>

int main(int argc, char *argv[])
{
  char *flags[5];
  int arrayCounter = 0;

  for (int idx = 1; idx < argc - 1; idx++)
  {
    flags[arrayCounter] = argv[idx];
    arrayCounter++;
  }

  getFileData(argv[argc - 1], flags);

  return 0;
}

// gcc -c functions.c
// gcc -c 6-CountingAFile.c
// gcc functions.o 6-CountingAFile.o -o main.exe