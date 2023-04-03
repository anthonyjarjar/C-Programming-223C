#include <stdlib.h>
#include "/Users/anthonyjarjour/Desktop/C-Programming-223C/Assignment7/src/functions.h"

int main(int argc, char *argv[]) {
    bool encode = false;
    bool decode = false;
    bool justify = false; 
    bool wrap = false;
    char *filename = "";
    char *stringToMorseResult;
    char *morseToStringResult;

    commandOperators(&encode, &decode, &justify, &wrap, &filename, argc, argv);

    if(encode && decode){
        fprintf(stderr, "Error: You can only use -e OR -d (code %d)\n", 1);
        return 1;
    }

    legendMaker();

    int errorCode = 0;

    char *buffer = 0;
    long length;
    FILE *inputFile;

    inputFile = fopen(filename, "rb");
    

    if (!errorCheck(inputFile, filename)) {
        exit(1);
    }

    if(inputFile){
        fseek (inputFile, 0, SEEK_END);
        length = ftell(inputFile);
        fseek (inputFile, 0, SEEK_SET);
        buffer = calloc(length + 1, sizeof(char));
        if (buffer){
            fread (buffer, 1, length, inputFile);
            buffer[length] = '\0';
        }
        fclose (inputFile);
    }

    if (!buffer){
        fprintf(stderr, "Error: Something went wrong when interpreting the string (code %d)\n", 1);
        return 1;
    }

    if(encode){
        stringToMorseResult = stringToMorse(buffer, &errorCode);
        
    }
    if(decode){
        morseToStringResult = morseToString(buffer, &errorCode);
        printf("%s\n", morseToStringResult);
    }

    if(errorCode != 0){
        fprintf(stderr, "Error code: %d\n", errorCode);
    }

    free(buffer);

    return 0;
}
