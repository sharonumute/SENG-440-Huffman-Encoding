#include <stdio.h>
#include "../include/huffman_encode.h"

int main(int argc, char *argv[])
{
    // Generate alphabet
    int i, j;

    // First Alphabet in the format "0"
    printf("{\n\"0\",\n");

    // The remaining 127 alphabets in the format "1111...0"
    for (i = 1; i < 127; ++i)
    {
        printf("\"");
        for (j = 0; j < i; ++j)
        {
            printf("1");
        }
        printf("0");
        printf("\",\n");
    }

    return 0;
}
