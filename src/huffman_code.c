#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ALPHABET_SIZE 128
#define MAX_HUFFCODE_LEN 127


// Alphabet (encoded in ASCII)
//Array corresponding to numbers of 1s in encoding 
const char ALPHABET[ALPHABET_SIZE] = {
    23, 113, 96, 73, 1, 82, 54, 93, 37, 116, 88, 
    39, 6, 55, 46, 7, 19, 49, 66, 64, 104, 45, 21, 
    120, 20, 61, 76, 106, 102, 81, 34, 62, 14, 99, 
    22, 84, 71, 77, 58, 17, 124, 126, 27, 117, 41, 
    97, 12, 4, 32, 38, 13, 25, 83, 101, 9, 28, 85, 
    24, 95, 57, 18, 3, 92, 48, 50, 86, 79, 91, 103, 
    108, 123, 80, 125, 5, 90, 70, 94, 89, 87, 44, 
    2, 33, 69, 26, 127, 111, 75, 118, 8, 36, 121, 
    105, 107, 78, 15, 11, 74, 10, 43, 51, 122, 100, 
    72, 63, 98, 68, 119, 16, 65, 60, 52, 42, 53, 
    35, 0, 115, 67, 59, 30, 47, 114, 29, 40, 112, 
    31, 109, 56, 110
};


const char LETTER_ORDER[ALPHABET_SIZE] = {
    114, 4, 80, 61, 47, 73, 12, 15, 88, 54, 97, 
    95, 46, 50, 32, 94, 107, 39, 60, 16, 24, 22, 
    34, 0, 57, 51, 83, 42, 55, 121, 118, 124, 48, 
    81, 30, 113, 89, 8, 49, 11, 122, 44, 111, 98, 
    79, 21, 14, 119, 63, 17, 64, 99, 110, 112, 6, 
    13, 126, 59, 38, 117, 109, 25, 31, 103, 19, 
    108, 18, 116, 105, 82, 75, 36, 102, 3, 96, 
    86, 26, 37, 93, 66, 71, 29, 5, 52, 35, 56, 65, 
    78, 10, 77, 74, 67, 62, 7, 76, 58, 2, 45, 104, 
    33, 101, 53, 28, 68, 20, 91, 27, 92, 69, 125, 
    127, 85, 123, 1, 120, 115, 9, 43, 87, 106, 23, 
    90, 100, 70, 40, 72, 41, 84
};

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


/**
 * Function: De
 * 
 */
int ceil_divide(unsigned long long int num, size_t den)
{
    if (!num % den)
        return num / den;
    return num / den + 1;
}

/**
 * Function: Encodes string and writes encoded value to buffer
 * 
 * Param: [in] (char []) string: String to encode not neccessarily 
 * null terminated as '\0' is a valid part of the alphabet
 * 
 * Param: [in] (register unsigned int) string_len: The length of the string to encode (including null terminators)
 * 
 * Param: [out] (char []) out_buf: Buffer to put encoded values in
 * 
 * Param: [out] (register unsigned int out_buf_len): Size of output buffer
 * 
 * Returns: (unsigned long long int) The number of bits written or -1 if there was an error
 */
unsigned long long int encode_string(char string[], register unsigned int string_len, int out_buf[], register unsigned int out_buf_len) {
    register int written_len = 0;
    register int num_1s = 0;
    register int bit_pos = 0;
    register int k=0;
    
    printf("String: %s\n",string);

    size_t i;
    for(i=0; i<string_len; ++i) {
        num_1s = LETTER_ORDER[(int)string[i]];

        //Check if there is room to write
        if (ceil_divide(written_len + num_1s+1, BYTE_SIZE) > out_buf_len) {
            return 0;
        }

        int j;
        for(j=0; j<num_1s; j++) {
            bit_pos = 7 - (written_len + j) % BYTE_SIZE;

            out_buf[k] += (1 << bit_pos);

            //printf("out_buf[%d]=%d (1<<%d)=%d\n", k, out_buf[k], bit_pos, 1<<bit_pos);

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
        return 0;
    }

    return written_len;
}

/**
 * Function: Encodes string and writes encoded value to buffer
 * 
 * Param: [in] (char []) string: String to encode not neccessarily 
 * null terminated as '\0' is a valid part of the alphabet
 * 
 * Param: [in] (register unsigned int) string_len: The length of the string to encode
 * 
 * Param: [out] (char []) out_buf: Buffer to put encoded values in
 * 
 * Param: [out] (register unsigned int out_buf_len): Size of output buffer
 * 
 * Returns: (long long int) The number of bits written or -1 if there was an error
 */
long long int decode_string(int encoded_string[], register unsigned long long int num_encoded_bits, 
    char out_buf[], register unsigned int out_buf_len) {
    register unsigned int k = 0;
    register unsigned int num_1s = 0;
    register unsigned int byte;
    register unsigned int i;

    register int num_full_bytes_encoded = num_encoded_bits/BYTE_SIZE;

    for (i = 0; i < num_full_bytes_encoded; ++i) {
        byte = (unsigned int)encoded_string[i];

        if(byte&0x80) {
            ++num_1s;
        }else {
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x40) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x20) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x10) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x8) {
            ++num_1s;
        }else {
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x4) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x2) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }

        if(byte&0x1) {
            ++num_1s;
        }else{
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }
    }

    byte = encoded_string[num_encoded_bits/BYTE_SIZE];

    
    for(i=num_encoded_bits%BYTE_SIZE; i; --i) {
        if(byte&(1<<i)) {
            ++num_1s;
        }else {
            if(k == out_buf_len-1) return -1;
            out_buf[k] = ALPHABET[num_1s];
            ++k;
            num_1s ^= num_1s;
        }
    }

    return k;
}

int main()
{
    char test_word[] = "abcdefghijklmnopqrstuvxyz .,a?1233445?23012sdf\'>";
    int buf[1000];
    char out_buf[1000];

    int written_len = encode_string(test_word, strlen(test_word)+1, buf, 1000);

    if (written_len < 0) {
        printf("Not enough room in buffer");
        return -1;
    }

    register int i;
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
