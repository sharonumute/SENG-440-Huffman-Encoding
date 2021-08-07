#include "../include/huffman_code.h"


/**
 * Function: ceil_divide
 * 
 * Description: Returns the ceiling of num/den
 * 
 * Param: (unsgined long int) num: The numerator
 * 
 * Param: (unsigned long int) den: The denominator
 * 
 * Returns: ceil(num/den)
 * 
 */
int ceil_divide(int num, int den)
{
    register int floor = num/den;
    return floor + (num%den==0);
    //return !(num%den) ? floor : floor+1;
}

/**
 * Function: encode_string
 * 
 * Description: Encodes string and writes encoded value to buffer
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
unsigned int encode_string(
    char string[], 
    register int string_len, 
    char out_buf[], 
    register int out_buf_len) 
{
    //Alphabet ordered by probability of occurence of each value
    const char ENCODE_TABLE[ALPHABET_SIZE] = {
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

    register int bits_written = 0;
    register int num_1s = 0;
    register int bit_pos = 0;
    register int byte=0; 
    register int j; //Loop counter
    register int i; //Loop counter


    for(i=0; i<string_len; ++i) {
        //Get integer representing the number of 1s in the code
        num_1s = ENCODE_TABLE[(int)string[i]];

        //Check if there is room to write
        if(ceil_divide(bits_written + num_1s + 1, BYTE_SIZE) >= out_buf_len) {
            return 0;
        }

        
        //Write ones in each bit
        for(j=0; j<num_1s; j++) {
            bit_pos = 7 - (bits_written + j)%BYTE_SIZE;

            out_buf[byte] += (1 << bit_pos);

            if(bit_pos == 0) {
                ++byte;
                out_buf[byte] = 0;
            }
        }

        bit_pos = 7 - (bits_written + j) % BYTE_SIZE;

        if(bit_pos == 0) {
            ++byte;
            out_buf[byte] = 0;
        }

        bits_written += num_1s;
        ++bits_written; //0
    }

    return bits_written;
}

/**
 * Function: decode_string
 * 
 * Description: Encodes string and writes encoded value to buffer
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
int decode_string(
    char encoded_string[], 
    register int num_encoded_bits, 
    char out_buf[], 
    register int out_buf_len) 
{

    // Alphabet 
    // from most probable to least
    const char DECODE_TABLE[ALPHABET_SIZE] = {
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

    register int out_buf_index = 0; //Loop iterator
    register int num_1s = 0;
    register int byte ;
    register int i;

    //printf("Num encoded bits: %i\n", num_encoded_bits);
    //printf("mod(encoded_bit, byte size)=%i", num_encoded_bits%BYTE_SIZE);

    register int num_full_bytes_encoded = num_encoded_bits/BYTE_SIZE;


    for (i = 0; i < num_full_bytes_encoded; ++i) {
        byte = (unsigned int)encoded_string[i];

        if(byte&0x80) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }

            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x40) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }

            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
           num_1s ^= num_1s;
        }

        if(byte&0x20) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x10) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x8) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x4) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x2) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }

        if(byte&0x1) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) {
                return -1;
            }
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }
    }
    
    if(num_encoded_bits%BYTE_SIZE == 0) {
        return out_buf_index;
    }

    byte = encoded_string[num_full_bytes_encoded];
    
    for(i = 7; i > 7-(num_encoded_bits%BYTE_SIZE); --i) {
        
        if(byte&(1<<i)) {
            ++num_1s;
        } else {
            
            if(out_buf_index == out_buf_len) {
                return -1;
            }

            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }
    }

    return out_buf_index;
}