/**
 * Seng 440 Huffman Code project
 * Authors: Samuel Barrett, Sharon Mute
 */
#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ALPHABET_SIZE 128
#define MAX_HUFFCODE_LEN 127

#define BYTE_SIZE 8
#define FOUR_BYTES_SIZE 32

//Used for printing 32 bit integer in binary using printf
#define FOUR_BYTES_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define FOUR_BYTES_TO_BINARY(four_bytes) \
        (four_bytes & 0x80000000 ? '1' : '0'), \
        (four_bytes & 0x40000000 ? '1' : '0'), \
        (four_bytes & 0x20000000 ? '1' : '0'), \
        (four_bytes & 0x10000000 ? '1' : '0'), \
        (four_bytes & 0x08000000 ? '1' : '0'), \
        (four_bytes & 0x04000000 ? '1' : '0'), \
        (four_bytes & 0x02000000 ? '1' : '0'), \
        (four_bytes & 0x01000000 ? '1' : '0'), \
        (four_bytes & 0x00800000 ? '1' : '0'), \
        (four_bytes & 0x00400000 ? '1' : '0'), \
        (four_bytes & 0x00200000 ? '1' : '0'), \
        (four_bytes & 0x00100000 ? '1' : '0'), \
        (four_bytes & 0x00080000 ? '1' : '0'), \
        (four_bytes & 0x00040000 ? '1' : '0'), \
        (four_bytes & 0x00020000 ? '1' : '0'), \
        (four_bytes & 0x00010000 ? '1' : '0'), \
        (four_bytes & 0x00008000 ? '1' : '0'), \
        (four_bytes & 0x00004000 ? '1' : '0'), \
        (four_bytes & 0x00002000 ? '1' : '0'), \
        (four_bytes & 0x00001000 ? '1' : '0'), \
        (four_bytes & 0x00000800 ? '1' : '0'), \
        (four_bytes & 0x00000400 ? '1' : '0'), \
        (four_bytes & 0x00000200 ? '1' : '0'), \
        (four_bytes & 0x00000100 ? '1' : '0'), \
        (four_bytes & 0x00000080 ? '1' : '0'), \
        (four_bytes & 0x00000040 ? '1' : '0'), \
        (four_bytes & 0x00000020 ? '1' : '0'), \
        (four_bytes & 0x00000010 ? '1' : '0'), \
        (four_bytes & 0x00000008 ? '1' : '0'), \
        (four_bytes & 0x00000004 ? '1' : '0'), \
        (four_bytes & 0x00000002 ? '1' : '0'), \
        (four_bytes & 0x00000001 ? '1' : '0')


/**
 * Declarations for functions used in huffman_code.c
 * See huffman_code.c file for function descriptions
 */

uint32_t ceil_divide(uint32_t num,uint32_t den);

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

uint32_t naive_decode_string(
    uint32_t encoded_string[], 
    register uint32_t num_encoded_bits, 
    char out_buf[], 
    register uint32_t out_buf_len);

#endif
