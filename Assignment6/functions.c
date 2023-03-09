#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "functions.h"

int newLineCount(char *input)
{
    int count = 0;
    int index = 0;

    while (input[index] != NULL)
    {
        if (input[index] == '\n')
        {
            count++;
            index++;
        }
        else
        {
            index++;
        }
    }

    return count;
}

int byteCount(char *input)
{
    int count = 0;
    int index = 0;

    while (input[index] != NULL)
    {
        count++;
        index++;
    }

    return count;
}

int maxLineLen(char *input)
{
    int index = 0;
    int currMax = 0;
    int tempLen = 0;

    while (input[index] != NULL)
    {
        if (input[index] == '\n')
        {
            if (tempLen > currMax)
            {
                currMax = tempLen;
                tempLen = 0;
                index++;
            }
            else
            {
                tempLen = 0;
                index++;
            }
        }

        if (input[index] == 13)
            index++;

        if (input[index] != '\n' && input[index] != 13)
        {
            tempLen++;
            index++;
        }
    }

    if (currMax == 0 || currMax < tempLen)
    {
        currMax = tempLen;
    }

    return currMax;
}

int wordCount(char *input)
{
    int count = 0;
    int index = 0;

    while (input[index] != NULL)
    {
        if (((input[index - 1] < 33) && ((input[index] >= 33) && (input[index] <= 126))) && (input[index + 1] != EOF))
        {
            count++;
        }
        index++;
    }

    return count;
}

void frequency(char *input)
{
    int freq[94] = {0};

    for (int idx = 0; input[idx] != '\0'; idx++)
        freq[input[idx] - '!'] += 1;

    for (int idx = 0; idx < 94; idx++)
    {
        if (freq[idx] != 0)
        {
            char char_ = ('!') + (idx);
            printf("%c %d\n", char_, freq[idx]);
        }
    }
}

int includes(char **arr, char *target)
{
    int length = 5;
    for (int idx = 0; idx < length; idx++)
    {
        if (strncmp(arr[idx], target, strlen(target)) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void getFileData(char *fileName, char *flags[])
{
    char *buffer = 0;
    long length;
    FILE *input = fopen(fileName, "rb");
    int index = 0;
    char ch;
    char *lowL = "-l";
    char *upL = "-L";
    char *lowW = "-w";
    char *lowC = "-c";

    if (input)
    {
        fseek(input, 0, SEEK_END);
        length = ftell(input);
        fseek(input, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
            fread(buffer, 1, length, input);

        fclose(input);
    }

    if (buffer)
    {
        if (includes(flags, lowL))
            printf("%d ", newLineCount(buffer));
        if (includes(flags, lowW))
            printf("%d ", wordCount(buffer));
        if (includes(flags, lowC))
            printf("%d ", byteCount(buffer));
        if (includes(flags, upL))
            printf("%d ", maxLineLen(buffer));

        // -l -w -c -L -f

        bool none = (!includes(flags, lowL)) && (!includes(flags, lowW)) && (!includes(flags, lowC)) && (!includes(flags, upL));

        if (none == true)
            printf("%d %d %d ", newLineCount(buffer), wordCount(buffer), byteCount(buffer));
    }

    fclose(input);
}
