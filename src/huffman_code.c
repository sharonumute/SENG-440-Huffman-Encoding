#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/huffman_encode.h"

//For printing to binary
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    (byte & 0x80 ? '1' : '0'),     \
        (byte & 0x40 ? '1' : '0'), \
        (byte & 0x20 ? '1' : '0'), \
        (byte & 0x10 ? '1' : '0'), \
        (byte & 0x08 ? '1' : '0'), \
        (byte & 0x04 ? '1' : '0'), \
        (byte & 0x02 ? '1' : '0'), \
        (byte & 0x01 ? '1' : '0')

//Returns ceil(num/den)
int ceil_divide(int num, int den)
{
    if (!num % den)
        return num / den;
    return num / den + 1;
}

//Returns number of characters in encoding (not including null termination)
int encode_string(char string[], int string_len, char out_buf[], int out_buf_len)
{
    int written_len = 0;

    int i, j, k = 0;
    for (i = 0; i < string_len; ++i)
    {
        //Get the size to encode new character (in bits)
        int huff_len = (int)string[i] + 1;

        //Check if there is room to write
        if (ceil_divide(written_len + huff_len, 8) > out_buf_len)
            return -1;

        //Get
        for (j = 0; j < huff_len; ++j)
        {
            int bit_pos = 7 - (written_len + j) % 8;

            out_buf[k] += (HUFFMAN_CODES[(int)string[i]][j] - 48) << bit_pos;
            printf("val: %d\n", HUFFMAN_CODES[(int)string[i]][j] - 48);

            if (bit_pos == 0)
                ++k;
        }

        written_len += huff_len;
    }

    //Check if there is room to write
    if (ceil_divide(written_len + 1, 8) > out_buf_len)
        return -1;

    out_buf[written_len] = 0; //Null terminate

    return ceil_divide(written_len, 8);
}

//Decode a string encoded in binary
int decode_string(char encoded_string[], int encoded_string_len, char out_buf[], int out_buf_len)
{
    int i;
    for (i = 0; i < encoded_string_len;)
        ;
}

int main()
{
    char test_word[] = "hello world";
    char buf[1000] = {""};

    int written_len = encode_string(test_word, sizeof(test_word), buf, 1000);

    if (written_len < 0)
    {
        printf("Not enough room in buffer");
        return -1;
    }

    printf("Encoding of %s:\n", test_word);

    int i;
    for (i = 0; i < written_len; ++i)
    {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(buf[i]));
    }

    return 0;
}
