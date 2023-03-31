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

void legendMaker();
char *stringToMorse(char* inputBuf, int* errorCode);
char* morseToString( char* inputBuf, int* errorCode);

int main(int argc, char *argv[]) {
    legendMaker();

    int errorCode = 0;

    char * buffer = 0;
    long length;
    FILE *inputFile = fopen("test.txt", "rb");

    if (!inputFile){
        fprintf(stderr, "Error: Something went wrong when opening the input file (code %d)\n", 1);
        return 1;
    }

    if(inputFile){
        fseek (inputFile, 0, SEEK_END);
        length = ftell(inputFile);
        fseek (inputFile, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer){
            fread (buffer, 1, length, inputFile);
        }
        fclose (inputFile);
    }

    if (!buffer){
        fprintf(stderr, "Error: Something went wrong when opening the input file (code %d)\n", 1);
        return 1;
    }

    stringToMorse(buffer, &errorCode);

    if(errorCode != 0){
        fprintf(stderr, "Error code: %d\n", errorCode);
    }

    return 0;
}

void legendMaker(){
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
}

char *stringToMorse( char* inputBuf, int* errorCode){
    char space = ' ';
    char newline = '\n';
    int charToTranslate = 0;

    do
    {
        char cdx = toupper(inputBuf[charToTranslate]);
        char *character = &cdx;
 
        if (inputBuf[charToTranslate] == '\0'){
            break;
        }

        bool found = false;

        for(int idx = 0; idx < 49; idx++){            
            if(character[0] == LEGEND[idx].asciiChar[0]){
                printf("%s ", LEGEND[idx].morsecode);
                found = true;
                break;
            }

            if(character[0] == space){
                printf(" ");
                found = true;
                break;
            }

            if(character[0] == newline){
                printf("  ");
                found = true;
                break;
            }
        }

        if(!found){
            *errorCode = 2;
            return 0;
        }

        charToTranslate++;

    }  while(1);

    printf("\n");
    return 0;
}

char* morseToString(char* inputBuf, int* errorCode) {
    int idx = 0;
    while (inputBuf[idx] != '\0') {
        bool found = false;

        if (inputBuf[idx] == ' ') {
            if (idx + 1 < strlen(inputBuf) && inputBuf[idx + 1] == ' ') {
                if (idx + 2 < strlen(inputBuf) && inputBuf[idx + 2] == ' ') {
                    if (idx + 3 < strlen(inputBuf) && inputBuf[idx + 3] == ' ') {
                        printf("\n\n");
                        found = true;
                        idx += 4;
                    } else {
                        printf("\n");
                        found = true;
                        idx += 3;
                    }
                } else {
                    printf(" ");
                    found = true;
                    idx += 2;
                }
            } else {
                idx++;
            }
        } else {
            char morseCode[7] = {'\0'};
            int jdx = 0;
            while (inputBuf[idx] != ' ' && inputBuf[idx] != '\0') {
                morseCode[jdx++] = inputBuf[idx++];
            }
            for (int kdx = 0; kdx < 49; kdx++) {
                if (strcmp(morseCode, LEGEND[kdx].morsecode) == 0) {
                    printf("%c", LEGEND[kdx].asciiChar[0]);
                    found = true;
                    break;
                }
            }
        }

        if(!found){
            *errorCode = 2;
            return 0;
        }
    }
    printf("\n");
    return 0;
}

