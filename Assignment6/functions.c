#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        if (((input[index - 1] < 33) && (input[index] >= 33) && (input[index] <= 126)) || (input[index + 1] == -1))
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

void getFileData()
{
    char *buffer = 0;
    long length;
    FILE *input = fopen("test.txt", "rb");
    int index = 0;
    char ch;

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
        printf("\nNew Line Count: %d\n", newLineCount(buffer));
        printf("\nByte Count: %d\n", byteCount(buffer));
        printf("\nMaxLineLen: %d\n", maxLineLen(buffer));
        printf("\nWord Count: %d\n", wordCount(buffer));
        printf("\nFrequency: \n");
        frequency(buffer);
    }

    fclose(input);
}