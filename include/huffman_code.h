#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ALPHABET_SIZE 128
#define MAX_HUFFCODE_LEN 127


//For printing to binary
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
        (byte & 0x80 ? '1' : '0'), \
        (byte & 0x40 ? '1' : '0'), \
        (byte & 0x20 ? '1' : '0'), \
        (byte & 0x10 ? '1' : '0'), \
        (byte & 0x08 ? '1' : '0'), \
        (byte & 0x04 ? '1' : '0'), \
        (byte & 0x02 ? '1' : '0'), \
        (byte & 0x01 ? '1' : '0')

#define BYTE_SIZE 8

int ceil_divide(int,int);

unsigned int encode_string(
    char string[], 
    register int string_len, 
    char out_buf[], 
    register int out_buf_len);

int decode_string(
    char encoded_string[], 
    register int num_encoded_bits, 
    char out_buf[], 
    register int out_buf_len);

#endif
