#include "../include/huffman_code.h"

int main() {
    printf("Hello world\n");

    char test_word[] = "abcdefghijklmnopqrstuvxyz .,a?5233445?23012sdf1>";
    char buf[1000];
    char out_buf[1000];
    register int i;

    int bits_written;
    
    bits_written = encode_string(test_word, strlen(test_word)+1, buf, 1000);

    if (bits_written < 0) {
        printf("Not enough room in buffer");
        return -1;
    }

    int str_len = decode_string(buf, bits_written, out_buf, 1000);

    printf("\nDecoded value\n");

    printf("\"%s\"\n", out_buf);

    char test_word1[] = "asdkjfh123879Q$#T@$%HTW$%Y<KL>ETUYJTDFG!@#$Q%$%^#%^UHND!~!#$~54 g";

    bits_written = encode_string(test_word1, strlen(test_word1)+1, buf, 1000);

    if (bits_written < 0) {
        printf("Not enough room in buffer");
        return -1;
    }

    for (i = 0; i < ceil_divide(bits_written, BYTE_SIZE); ++i) {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(buf[i]));
    }
    printf("\n");

    for (i = 0; i < ceil_divide(bits_written, BYTE_SIZE); ++i) {
        printf("%x ", buf[i]);
    }
    printf("\n");

    decode_string(buf, bits_written, out_buf, 1000);
    
    printf("\nDecoded value 1\n");
    printf("\"%s\"\n", out_buf);

    /*FILE* fptr = fopen("./test/sample_values.txt", "r");

    if(fptr == NULL) {
        fprintf(stderr, "Couldn't open file\n");
        return -1;
    }

    char char_buf[100];

    fgets(char_buf, 100, fptr);

    int num_chars = atoi(char_buf);

    char fbuf[num_chars];
    char decode_buf[num_chars];

    printf("Size of file: %d\n", num_chars );

    char c;
    i=-1;
    while((c = fgetc(fptr)) != EOF) {
        fbuf[++i] = c;
    }

    fclose(fptr);

    printf("Wrote %i values\n", i+1);
    printf("Num_chars: %i\n", num_chars);

    char encoded_buf[i];

    bits_written = encode_string(fbuf, num_chars, encoded_buf, num_chars);
    
    printf("\nEncoded value\n");*/
    
    //printf("\"%s\"\n", fbuf);

    /* for(i=0; i<num_chars; ++i) {
        printf("%d ", fbuf[i]);
    }

    for (i = 0; i < ceil_divide(bits_written, BYTE_SIZE); ++i) {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(encoded_buf[i]));
    }
    printf("\n");*/

    /*printf("Bytes written: %d\n", ceil_divide(bits_written, BYTE_SIZE));

    if(decode_string(encoded_buf, bits_written, decode_buf, num_chars)<0){
        fprintf(stderr, "Decode did not work\n");
        return -1;
    }

    printf("\nDecoded value:\n");
    //printf("\"%s\"\n", decode_buf);

    unsigned int num_mismatches = 0;
    for(i=0; i < num_chars; ++i) {
        if(fbuf[i] != decode_buf[i]) {
            ++num_mismatches;
            printf("Mismatch at char %i of %i chars\n",i+1,num_chars);
        };
    }

    printf("Num mismatches: %i\n", num_mismatches);*/

    return 0;
}
