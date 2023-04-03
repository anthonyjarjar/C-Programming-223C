#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "/Users/anthonyjarjour/Desktop/C-Programming-223C/Assignment7/src/functions.h"

struct codeTranslator{
    char asciiChar[2];
    char morsecode[7];
};

struct codeTranslator LEGEND[49]; 

bool errorCheck(FILE *inputFile, char *filename){
    if (!inputFile) {
        printf("Error opening file %s\n", filename);
        perror("Error");
        return false;
    }
    return true;
}


void legendMaker(){
    char *filename = "src/txtfiles/morsecode.txt";
    FILE *morseCodeFile;

    morseCodeFile = fopen(filename, "rb");
    
    if (!errorCheck(morseCodeFile, filename)) {
        exit(1);
    }

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

int endsWithTXT(const char* str){
    int len = strlen(str);
    const char* suffix = ".txt";
    int suffix_len = strlen(suffix);

    if (len < suffix_len) {
        return 0;
    }

    const char* end = str + len - suffix_len;
    return (strcmp(end, suffix) == 0);
}

void commandOperators(bool *encode, bool *decode, bool *justify, bool *wrap, char **filename, int argc, char *argv[]){
    for(int idx = 0; idx < argc; idx++){
        if (strcmp(argv[idx], "-e") == 0){
            *encode = true;
        }
        if (strcmp(argv[idx], "-d") == 0){
            *decode = true;
        }
        if (endsWithTXT(argv[idx])){
            *filename = argv[idx];
        }
    }
}

char *stringToMorse( char* inputBuf, int* errorCode){
    char space = ' ';
    char newline = '\n';
    int charToTranslate = 0;
    char *result = malloc(50 * sizeof(char));

    *errorCode = 0;

    do
    {
        char cdx = inputBuf[charToTranslate];
        cdx = toupper(cdx);
        char *character = &cdx;
 
        if (inputBuf[charToTranslate] == '\0'){
            break;
        }

        bool found = false;

        for(int idx = 0; idx < 49; idx++){     
            if(character[0] == LEGEND[idx].asciiChar[0] && LEGEND[idx].asciiChar[0] != 0){
                if(LEGEND[idx].morsecode[0] != 0)    
                    result = realloc(result, (strlen(result) + strlen(LEGEND[idx].morsecode) + 1) * sizeof(char));
                    strcat(result, LEGEND[idx].morsecode);
                    result = realloc(result, (strlen(result) + strlen(" ") + 1) * sizeof(char));
                    strcat(result, " ");
                    found = true;
                    break;
            }

            if(character[0] == space){
                result = realloc(result, (strlen(result) + strlen(" ") + 1) * sizeof(char));
                strcat(result, " ");
                found = true;
                break;
            }

            if(character[0] == newline){
                result = realloc(result, (strlen(result) + strlen("  ") + 1) * sizeof(char));
                strcat(result, "  ");
                found = true;
                break;
            }

            if(inputBuf[charToTranslate] == newline && character[0] == newline){
                result = realloc(result, (strlen(result) + strlen("   ") + 1) * sizeof(char));
                strcat(result, "   ");
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

    return result;
}

char* morseToString(char* inputBuf, int* errorCode) {
    *errorCode = 0;
    int idx = 0;
    char *result = malloc(50 * sizeof(char));

    while (inputBuf[idx] != '\0') {
        bool found = false;

        if (inputBuf[idx] == ' ') {
            found = true;
            if (idx + 1 < (int)strlen(inputBuf) && inputBuf[idx + 1] == ' ') {
                if (idx + 2 < (int)strlen(inputBuf) && inputBuf[idx + 2] == ' ') {
                    if (idx + 3 < (int)strlen(inputBuf) && inputBuf[idx + 3] == ' ') {
                        found = true;
                        result = realloc(result, (strlen(result) + strlen("\n\n") + 1) * sizeof(char));
                        strcat(result, "\n\n ");
                        idx += 4;
                        continue;
                    } else {
                        found = true;
                        result = realloc(result, (strlen(result) + strlen("\n") + 1) * sizeof(char));
                        strcat(result, "\n ");
                        idx += 3;
                        continue;
                    }
                } else {
                    result = realloc(result, (strlen(result) + strlen(" ") + 1) * sizeof(char));
                    strcat(result, " ");
                    found = true;
                    idx += 2;
                    continue;
                }
            } else {
                idx++;
                continue;
            }
        } else {
            char morseCode[7] = {'\0'};
            int jdx = 0;
            while (inputBuf[idx] != ' ' && inputBuf[idx] != '\0') {
                morseCode[jdx++] = inputBuf[idx++];
            }
            for (int kdx = 0; kdx < 49; kdx++) {
                if (strcmp(morseCode, LEGEND[kdx].morsecode) == 0) {
                    result = realloc(result, (strlen(result) + strlen(&LEGEND[kdx].asciiChar[0]) + 1) * sizeof(char));
                    strcat(result, &LEGEND[kdx].asciiChar[0]);
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

    return result;
}
