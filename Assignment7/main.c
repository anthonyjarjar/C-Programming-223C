#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct codeTranslator{
    char asciiChar[2];
    char morsecode[7];
};

struct codeTranslator LEGEND[49]; 

char* string_to_morse(char* input_buf, int* error_code);

int main(int argc, char *argv[]) {
    FILE *morseCodeFile;
    morseCodeFile = fopen("morsecode.txt", "r");
    char line[256];
    char delim[] = " ";
    int idx = 0; 

    while (fgets(line, sizeof(line), morseCodeFile)) {
        char *ptr = strtok(line, delim);
        int cdx = 0;

        while (ptr != NULL) {
            ptr[strcspn(ptr, "\n")] = 0;

            if(cdx == 0){
                strcpy(LEGEND[idx].asciiChar, ptr);
            }

            if(cdx == 1){
                strcpy(LEGEND[idx].morsecode, ptr);
            }

            ptr = strtok(NULL, delim);
            cdx++;
        }

        idx++;
    }

    fclose(morseCodeFile);

    FILE *test;
    test = fopen("test.txt", "r");
    char space = ' ';
    char newline = '\n';
    
    do
    {
        char c = toupper(fgetc(test));
        char *character = &c;
 
        if (feof(test))
            break;
         
        for(int idx = 0; idx < 49; idx++){            
            if(character[0] == LEGEND[idx].asciiChar[0]){
                printf("%s ", LEGEND[idx].morsecode);
                break;
            }

            if(character[0] == space){
                printf(" ");
                break;
            }

            if(character[0] == newline){
                printf("  ");
                break;
            }
        }
    }  while(1);

    printf("\n");

    return 0;
}

char* string_to_morse( char* input_buf, int* error_code){
    return 0;
};
