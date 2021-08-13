#include "../include/huffman_code.h"


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
uint32_t encode_string(
    char string[], 
    register uint32_t string_len, 
    uint32_t out_buf[], 
    register uint32_t out_buf_len) 
{
    //Num 1s for each alphabet character 
    //(represented by the index)
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

    register uint32_t bits_written = 0;
    register int32_t num_1s = 0;
    register uint32_t bit_pos = 0;
    register uint32_t out_buf_index=0; 
    register int j  ; //Loop counter
    register uint32_t i;

    out_buf[0] = 0;

    for(i=0; i < string_len; ++i) {
        //Get integer representing the number of 1s in the code
        num_1s = *(ENCODE_TABLE+string[i]);

        //Check if there is room to write
        if((bits_written + num_1s + 1)/FOUR_BYTES_SIZE >= out_buf_len) {
            return 0;
        }

        //Write ones in each bit
        for(j=0; j < num_1s; j++) {
            bit_pos = 31 - (bits_written + j)%FOUR_BYTES_SIZE;

            out_buf[out_buf_index] += (1 << bit_pos);

            if(!bit_pos) { //bit_pos == 0
                ++out_buf_index;
                out_buf[out_buf_index] = 0;
            }
        }

        if((bits_written + j) % FOUR_BYTES_SIZE == 31) {
            ++out_buf_index;
            out_buf[out_buf_index] = 0;
        }

        bits_written += num_1s;
        ++bits_written; //For the zero bit at the end
    }
    return bits_written;
}

/**
 * Function: decode_string
 * 
 * Description: Descodes string and writes encoded value to buffer
 * 
 * Param: [in] (uint32_t []) encoded_string: String to encode not neccessarily 
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
uint32_t decode_string(
    uint32_t encoded_string[], 
    register uint32_t num_encoded_bits, 
    char out_buf[], 
    register uint32_t out_buf_len) 
{

    // Alphabet ordered from most probable to least
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


    register uint32_t out_buf_index = 0; //Index for writing values to output buffer
    register uint32_t num_1s = 0; //Record the number of 1s for a sequence
    register uint32_t four_bytes = 0; //Value to load into register from encoded sequence
    register int i=0, j=0; //Loop iterators
    register int num_ints_encoded = num_encoded_bits/FOUR_BYTES_SIZE; //Number of full 32 bit integers in encoding
    register int bit_value = 0; //Value of a particular bit from encoding
    register int bit_value1 = 0; //Second version for loop unrolling

    //Loop for each full 32 bit value in the encoded array
    for(i=0; i < num_ints_encoded; ++i) {
        four_bytes = encoded_string[i];

        //For speed, only want to check once per iteration if buffer might become full
        //In this iteration (in the worst case)
        //If it might, the iterations are continued below, but a per bit check is performed
        if(out_buf_index == out_buf_len+FOUR_BYTES_SIZE) {
            break;
        }

        //Iterate from 31 = 0x15 (Num bits-1)
        //-1 has high bit at 0x20 (loop condition like j!=-1)
        //Code contains as few branches as possible
        for(j=0x1F; !(j&0x20); j-=2) {
            bit_value = (four_bytes>>j)&01;
            bit_value1 = (four_bytes>>(j-1))&01;
   
            //If bit is one, increment num_1s
            num_1s += bit_value;

            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            
            //Sets to zero if bit is 0, otherwise keep the same 
            num_1s *= bit_value;

            //If bit is 0, this is the end of the character,so
            //Increment the outut buffer index
            out_buf_index += !bit_value;

            //Repeat for loop unrolling
            num_1s += bit_value1;
            
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];

            num_1s *= bit_value1;
            
            out_buf_index += !bit_value1;
        }
    }

    //Continue where left off, but check if output buffer full on each 
    //new bit
    for(; i < num_ints_encoded; ++i) {
        four_bytes = encoded_string[i];

        //Iterate to 31 = 0x1F
        //-1 has high bit at 0x20 (so loop until j==-1)
        for(j=0x1F; !(j&0x20); j-=2) {

            bit_value = (four_bytes>>j)&01;
            bit_value1 = (four_bytes>>(j-1))&01;

            num_1s += bit_value;

            if(!bit_value) {
                //Buffer full
                if(out_buf_index == out_buf_len) {
                    return 0;
                }
                out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            }
            num_1s *= bit_value; //Sets to zero if bit is 0, otherwise keep the same    
            out_buf_index += !bit_value;

            num_1s += bit_value1;

            if(!bit_value1) {
                if(out_buf_index == out_buf_len) { //Too long
                    return 0;
                }
                out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            }
            num_1s *= bit_value1;
            out_buf_index += !bit_value1;
        }
    }

    //If encoding fits evenly into bytes then return here
    if(num_encoded_bits%FOUR_BYTES_SIZE == 0) {;
        return out_buf_index;
    }


    //Last int contains only a certain number of encoded bits,
    //So need to determine where the end of the encoding is
    four_bytes = encoded_string[num_ints_encoded];

    int end_bit_cond = 31-(int)(num_encoded_bits%FOUR_BYTES_SIZE);

    for(i = 31; i > end_bit_cond; --i) {
        if(four_bytes&(1<<i)) {
            ++num_1s;
        } else {
            if(out_buf_index == out_buf_len) { //Too long
                return 0;
            }
            out_buf[out_buf_index] = DECODE_TABLE[num_1s];
            ++out_buf_index;
            num_1s ^= num_1s;
        }
    }

    //Return the number of deconded values
    return out_buf_index;
}
