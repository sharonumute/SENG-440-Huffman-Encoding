#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

#define ALPHABET_SIZE 128
#define MAX_HUFFCODE_LEN 127

#define BYTE_SIZE 8
#define FOUR_BYTES_SIZE 32

#define FOUR_BYTES_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define FOUR_BYTES_TO_BINARY(byte) \
        (byte & 0x80000000 ? '1' : '0'), \
        (byte & 0x40000000 ? '1' : '0'), \
        (byte & 0x20000000 ? '1' : '0'), \
        (byte & 0x10000000 ? '1' : '0'), \
        (byte & 0x08000000 ? '1' : '0'), \
        (byte & 0x04000000 ? '1' : '0'), \
        (byte & 0x02000000 ? '1' : '0'), \
        (byte & 0x01000000 ? '1' : '0'), \
        (byte & 0x00800000 ? '1' : '0'), \
        (byte & 0x00400000 ? '1' : '0'), \
        (byte & 0x00200000 ? '1' : '0'), \
        (byte & 0x00100000 ? '1' : '0'), \
        (byte & 0x00080000 ? '1' : '0'), \
        (byte & 0x00040000 ? '1' : '0'), \
        (byte & 0x00020000 ? '1' : '0'), \
        (byte & 0x00010000 ? '1' : '0'), \
        (byte & 0x00008000 ? '1' : '0'), \
        (byte & 0x00004000 ? '1' : '0'), \
        (byte & 0x00002000 ? '1' : '0'), \
        (byte & 0x00001000 ? '1' : '0'), \
        (byte & 0x00000800 ? '1' : '0'), \
        (byte & 0x00000400 ? '1' : '0'), \
        (byte & 0x00000200 ? '1' : '0'), \
        (byte & 0x00000100 ? '1' : '0'), \
        (byte & 0x00000080 ? '1' : '0'), \
        (byte & 0x00000040 ? '1' : '0'), \
        (byte & 0x00000020 ? '1' : '0'), \
        (byte & 0x00000010 ? '1' : '0'), \
        (byte & 0x00000008 ? '1' : '0'), \
        (byte & 0x00000004 ? '1' : '0'), \
        (byte & 0x00000002 ? '1' : '0'), \
        (byte & 0x00000001 ? '1' : '0')

/**
 * Function: ceil_divide
 * 
 * Description: Returns the ceiling of num/den. Used to calculate 
 * the number of data elements int the encoding.
 * 
 * Param: (unsgined long int) num: The numerator
 * 
 * Param: (unsigned long int) den: The denominator
 * 
 * Returns: ceil(num/den)
 * 
 */
inline uint32_t ceil_divide(uint32_t num,uint32_t den) {
    return (num+den-1)/den;
}

uint32_t encode_string(
    char string[], 
    register uint32_t string_len, 
    uint32_t out_buf[], 
    register uint32_t out_buf_len);

uint32_t decode_string(
    uint32_t encoded_string[], 
    register uint32_t num_encoded_bits, 
    char out_buf[], 
    register uint32_t out_buf_len);

#endif
