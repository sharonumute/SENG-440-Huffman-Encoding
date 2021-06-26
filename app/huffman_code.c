#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/huffman_encode.h"


int encode_char(char c, char out_buf[], size_t out_buf_len){
    size_t huffcode_len = strlen(HUFFMAN_CODES[(int)c]);

    printf("strlen: %lu\n", huffcode_len);

    //Check that buffer size is large enough
    //to store huffman code plus string terminater char
    if(out_buf_len < huffcode_len+2) {
        return -1;
    }

    for(size_t i=0; i<=huffcode_len; ++i) 
        out_buf[i] = HUFFMAN_CODES[(int)c][i]; 
    out_buf[huffcode_len+1] = 0;

    return huffcode_len;
}

char decode_char (char in_char_code[], size_t in_code_len) {
    if(in_char_code[in_code_len-1] == '1') {
        return (char)(in_code_len + 1);
    }
    return (char)(in_code_len-1);
}

int encode_word(char word[], char out_buf[], size_t out_buf_len) {
    size_t written_len = 0;

    int wordlen = sizeof(word);

    for(int i=0; i<wordlen;++i) {
        int ret_len = encode_char(word[i], out_buf+written_len, out_buf_len-written_len); 
        
        if(ret_len == -1) {
            return -1;    
        }
        
        written_len += ret_len;

        if(written_len > out_buf_len-1) {
            return -1;
        }
    }

    out_buf[written_len] = 0;

    return written_len;
}

int main() {

    char test_code[] = "hello world";
    char buf[200];
    int out_len;
    
    out_len = encode_char(2, buf, 200);
    printf("%d|buf: %s\n",out_len, buf); 
    printf("was here\n");

    out_len = encode_char(127, buf, 200);
    printf("%d|buf: %s\n",out_len, buf); 

    out_len = encode_char(test_code[2], buf, 200);
    printf("%d|buf: %s\n",out_len, buf); 

    return 0;
}
