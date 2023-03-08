#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char fileCharacters[1000];

void getFileData(char *stringArr, char *fileName);
void computeTable(char *stringArr, char *fileName);

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("\nPLEAE USE '--help' FOR HELP\n\n");
    return 1;
  }

  if (argc == 2 && !strcmp(argv[argc - 1], "--help")) {
    printf("\nIn order to use this app you must use the following format");
    printf("\n./main <input_file> <output_file>");
    printf("\n");
    printf("\nThe input file must contain a string for the app to read");
    printf("\nThe output file must be blank for the app to write too\n\n");
    return 1;
  }

  getFileData(fileCharacters, argv[1]);
  computeTable(fileCharacters, argv[2]);

  return 0;
}

void computeTable(char *stringArr, char *fileName) {
  int freq[256] = {0};

  for (int idx = 0; stringArr[idx] != '\0'; idx++)
    freq[stringArr[idx] - '\n'] += 1;

  FILE *output;
  output = fopen("output.txt", "w+");
  if (output == NULL) {
    printf("Failed to open output file.\n");
    exit(-1);
  }

  fputs(" Char   | HexDec | Dec  | Count \n", output);
  fputs("--------+--------+------+------\n", output);

  for (int idx = 0; idx < 256; idx++) {
    if (freq[idx] != 0) {
      char char_ = ('\n') + (idx);

      if (char_ == 10)
        fprintf(output, "\\n      |  0x%02X  | %03d  | %d \n", char_, char_,
                freq[idx]);

      if ((char_ == 9) || (char_ == 32))
        fprintf(output, "SPACE   |  0x%02X  | %03d  | %d \n", char_, char_,
                freq[idx]);

      if (char_ != 10 && char_ != 32 && char_ != 9)
        fprintf(output, "%c       |  0x%02X  | %03d  | %d \n", char_, char_,
                char_, freq[idx]);
    }
  }
  fclose(output);
}

void getFileData(char *stringArr, char *fileName) {
  FILE *input;
  char ch;
  int index = 0;
  input = fopen(fileName, "r");

  if (input == NULL) {
    printf("Failed to open input file.\n");
    exit(-1);
  }

  while (!feof(input)) {
    ch = fgetc(input);

    if (ch < 0 || ch > 127)
      break;

    stringArr[index] = ch;

    index++;
  }

  fclose(input);
}