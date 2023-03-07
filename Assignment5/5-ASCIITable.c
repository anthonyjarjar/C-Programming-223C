#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFileData(char *stringArr, char *fileName);
void asciiTable();
void computeTable(char *stringArr);

int main(int argc, char *argv[]) {
  char *fileCharacters[1000];

  getFileData(*fileCharacters, argv[1]);

  computeTable(*fileCharacters);

  return 0;
}

void computeTable(char *stringArr){
  int freq[256] = {0};

  printf(" Char   | HexDec | Dec  | Count \n");
  printf("--------+--------+------+------\n");

  for (int idx = 0; stringArr[idx] != '\0'; idx++)
        freq[stringArr[idx]-'\n'] += 1;
  
    for (int idx = 0; idx < 256; idx++)
    {
        if (freq[idx] != 0)
        {
            char char_ = '\n' + idx;

            if (char_ == 10)
              printf("\\n      |  0x%02X  | %03d  | %d \n", char_, char_, freq[idx]);

            if ((char_ == 9) || (char_ == 32))
              printf("SPACE   |  0x%02X  | %03d  | %d \n", char_, char_, freq[idx]);

            if (char_ != 10 && char_ != 32 && char_ != 9)
              printf("%c       |  0x%02X  | %03d  | %d \n", char_, char_, char_, freq[idx]);
        }
    }

    printf("\n");
}

void asciiTable(){
  for (char chx = 0; chx <= 126; chx++) {
      
      if (chx < 32 && chx != 10)
        printf("   |  0x%02X  | %03d \n", chx, chx);

      if (chx == 10)
        printf("\\n |  0x%02X  | %03d \n", chx, chx);

      if (chx > 32 && chx != 32)
        printf("%c  |  0x%02X  | %03d \n", chx, chx, chx);

    }
}

void getFileData(char *stringArr, char *fileName) {
  FILE *ptr;
  char ch;
  int index = 0;
  ptr = fopen(fileName, "r");

  if (NULL == ptr) {
    printf("Failed to open file.\n");
    exit(-1);
  }

  while (!feof(ptr)) {
    ch = fgetc(ptr);

    if (ch < 0 || ch > 127)
      break;

    stringArr[index] = ch;

    index++;
  }
  
  fclose(ptr);
}