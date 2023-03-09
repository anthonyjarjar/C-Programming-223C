#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void asciiTable();

int main(int argc, char *argv[]){

    asciiTable();

    return 0;
}

void asciiTable(){
  FILE *output;
  output = fopen("output.txt", "w+");
  if (output == NULL) {
    printf("Failed to open output file.\n");
    exit(-1);
  }
  
  for (int idx = 0; idx < 8; idx++)
    fprintf(output, " Char Hex    Dec  |");
  
  fprintf(output, "\n");

  for (int jdx = 0; jdx < 8; jdx++)
    fprintf(output, "------------------+");
  
  
  for (int chx = 0; chx < 256; chx++) {
    if((chx % 8) == 0)
        fprintf(output, "\n");
    
   
      if (chx < 33 || chx > 126)
          fprintf(output, " -    0x%02X   %03d  |", chx, chx);

      else if (chx > 33 || chx < 126)
          fprintf(output, " %c    0x%02X   %03d  |", chx, chx, chx);
      }
  }
