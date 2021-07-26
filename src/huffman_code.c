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

#define BYTE_SIZE 8

//Returns ceil(num/den)
int ceil_divide(size_t num, size_t den)
{
    if (!num % den)
        return num / den;
    return num / den + 1;
}

//Returns number of characters in encoding (not including null termination)
/*int encode_string(char string[], size_t string_len, char out_buf[], size_t out_buf_len)
{
    int written_len = 0;

    int i, j, k = 0;
    for (i = 0; i < string_len; ++i)
    {
        //Check if there is room to write
        if (ceil_divide(written_len + char_encode_len, BYTE_SIZE) > out_buf_len) {
            return -1;
        }

        //Get
        for(j = 0; j < char_encode_len; ++j)
        {
            int bit_pos = 7 - (written_len + j) % BYTE_SIZE;

            out_buf[k] += (ALPHABET[(int)string[i]][j] - 48) << bit_pos;

            if(bit_pos == 0) {
                ++k;
            }
        }

        written_len += char_encode_len;
    }

    //Check if there is room to write
    if (ceil_divide(written_len + 1, 8) > out_buf_len) {
        return -1;
    }

    out_buf[written_len] = 0; //Null terminate

    return written_len; //Return number of bits written
}*/


int encode_string(char string[], size_t string_len, int out_buf[], size_t out_buf_len) {
    register int written_len = 0;
    register int num_1s = 0;
    register int bit_pos = 0;
    register int k=0;
    
    printf("String: %s\n",string);

    size_t i;
    for(i=0; i<string_len; ++i) {
        num_1s = LETTER_ORDER[(int)string[i]];

        printf("num_1s: %d\n", num_1s);

        //Check if there is room to write
        if (ceil_divide(written_len + num_1s+1, BYTE_SIZE) > out_buf_len) {
            return -1;
        }

        int j;
        for(j=0; j<num_1s; j++) {
            bit_pos = 7 - (written_len + j) % BYTE_SIZE;

            out_buf[k] += (1 << bit_pos);

            printf("out_buf[%d]=%d (1<<%d)=%d\n", k, out_buf[k], bit_pos, 1<<bit_pos);

            if(bit_pos == 0) {
                ++k;
            }
        }

        bit_pos = 7 - (written_len + j) % BYTE_SIZE;

        out_buf[k] += (0 << bit_pos);

        if(bit_pos == 0) {
            ++k;
        }

        written_len += num_1s+1;
    }

    //Check if there is room to write
    if (ceil_divide(written_len + num_1s+1, BYTE_SIZE) > out_buf_len) {
        return -1;
    }

    return written_len;
}

//Decode a string encoded in binary
int decode_string(int encoded_string[], size_t num_encoded_bits, char out_buf[], size_t out_buf_len) {
    size_t k=0;

    size_t num_1s = 0;
    char byte;
    

    int i;
    for (i = 0; i < num_encoded_bits; i+=8) {
        byte = encoded_string[i/8];

        if(!(byte&0x80)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else {
            ++num_1s;
        }

        if(!(byte&0x40)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        if(!(byte&0x20)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        if(!(byte&0x10)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        if(!(byte&0x8)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else {
            ++num_1s;
        }

        if(!(byte&0x4)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        if(!(byte&0x2)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        if(!(byte&0x1)) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            printf("num_1s: %d, value: %c\n", num_1s, ALPHABET[num_1s]);
            num_1s = 0;
        }else{
            ++num_1s;
        }

        //printf("Num 1s: %d\n", num_1s);
    }

    byte = encoded_string[(num_encoded_bits-1)/8];

    
    for(int i=num_encoded_bits%BYTE_SIZE; i>=0; ++i) {
        if(!(byte&0x(1<<i))) {
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s = 0;
        }else {
            ++num_1s;
        }
    }

    out_buf[k] = 0;

    return k;
}

int main()
{
    char test_word[] = "hello world";
    int buf[1000];
    char out_buf[1000];

    int written_len = encode_string(test_word, strlen(test_word), buf, 1000);

    if (written_len < 0) {
        printf("Not enough room in buffer");
        return -1;
    }

    //printf("Encoding of %s:\n", test_word);

    int i;
    for (i = 0; i < ceil_divide(written_len, BYTE_SIZE); ++i) {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(buf[i]));
    }
    printf("\n");

    for (i = 0; i < ceil_divide(written_len, BYTE_SIZE); ++i) {
        printf("%x ", buf[i]);
    }
    printf("\n");

    int strlen = decode_string(buf, written_len, out_buf, 1000);

    printf("\nDecoded value\n");

    printf("%s\n", out_buf);

    return 0;
}
