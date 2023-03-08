#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFileData();
void computeTable(char *stringArr);

int main(int argc, char *argv[]) {

  getFileData();

  return 0;
}

void computeTable(char *stringArr) {
  int freq[26] = {0};

  for (int idx = 0; stringArr[idx] != '\0'; idx++)
    freq[stringArr[idx] - 'a'] += 1;

  FILE *output;
  output = fopen("output.txt", "w+");
  if (output == NULL) {
    printf("Failed to open output file.\n");
    exit(-1);
  }

  fputs(" Char   | HexDec | Dec  | Count \n", output);
  fputs("--------+--------+------+------\n", output);

  for (int idx = 0; idx < 26; idx++) {
    if (freq[idx] != 0) {
      char char_ = ('a') + (idx);

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

void getFileData() {
  char *buffer = 0;
  long length;
  FILE *input = fopen("words_alpha.txt", "rb");
  int index = 0;
  char ch;

  if (input) {
    fseek(input, 0, SEEK_END);
    length = ftell(input);
    fseek(input, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer)
      fread(buffer, 1, length, input);

    fclose(input);
  }

  int freq[26] = {0};

  if (buffer) {
    computeTable(buffer);
  }

  fclose(input);
}