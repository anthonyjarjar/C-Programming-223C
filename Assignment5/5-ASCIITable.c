#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(char *fileName);

int main(int argc, char *argv[]) {

  readFile(argv[1]);

  return 0;
}

void readFile(char *fileName) {
  FILE *ptr;
  char ch;
  ptr = fopen(fileName, "r");

  if (NULL == ptr) {
    printf("Failed to open file.\n");
    exit(-1);
  }

  while (!feof(ptr)) {
    ch = fgetc(ptr);

    if (ch == -1)
      break;

    printf("%c |  0x%X  | %d \n", ch, ch, ch);
  }

  printf("\n");
  fclose(ptr);
}