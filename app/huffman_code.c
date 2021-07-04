#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/huffman_encode.h"

//Returns number of characters in encoding (not including null termination)
int encode_string(char string[], int string_len, char out_buf[], int out_buf_len) {
    int written_len = 0;

    int i,j;
    for(i=0; i<string_len;++i) {        
        //Get the size to encode new word
        int huff_len = (int)string[i];

        //Check if there is room to write
        if(written_len + huff_len > out_buf_len) return -1;

        //Get
        for(j=0; j<huff_len; ++j) {
            out_buf[j+written_len] = HUFFMAN_CODES[(int)string[i]][j];
        } 

        written_len += huff_len;
    }

    if(written_len+1 > out_buf_len) return -1;

    out_buf[written_len] = 0; //Null terminate

    return written_len;
}

int decode_string(char encoded_string[], int encoded_string_len, char out_buf[], int out_buf_len) {
    int written_len = 0;

    int i,j;
    for(i=0; i<word_len;++i) {
        written_len += huff_len;
    }

    if(written_len+1 > out_buf_len) return -1;

    out_buf[written_len] = 0; //Null terminate

    return written_len;
}

int main() {

    char test_word[] = "hello world";
    char buf[1000000] = {};
    
    int written_len = encode_word(test_word, sizeof(test_word), buf, 1000000);

    if(written_len<0) {
        printf("Not enough room in buffer");
        return -1;
    }

    printf("Encoding of %s:\n\"%s\"\n", test_word, buf);

    return 0;
}
