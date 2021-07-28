#include "../include/huffman_code.h"

int main() {
    printf("Hello world\n");

    char test_word[] = "abcdefghijklmnopqrstuvxyz .,a?5233445?23012sdf1>";
    int buf[1000];
    char out_buf[1000];

    int bits_written = encode_string(test_word, strlen(test_word)+1, buf, 1000);

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

    register int i;
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

    FILE* fptr = fopen("./test/sample_values.txt", "r");

    if(fptr == NULL) {
        fprintf(stderr, "Couldn't open file\n");
        return -1;
    }

    char char_buf[100];

    fgets(char_buf, 100, fptr);

    int num_chars = atoi(char_buf);

    char fbuf[num_chars+100];

    printf("Size of file: %d\n", num_chars );

    char c;
    i=-1;
    while((c = fgetc(fptr)) != EOF) {
        fbuf[++i] = c;
    }

    fclose(fptr);

    int encoded_buf[num_chars];


    bits_written = encode_string(fbuf, num_chars, encoded_buf, num_chars);
    
    for(int i=0; i<num_chars; ++i) {
        //printf("%d ", fbuf[i]);
    }
    for (i = 0; i < ceil_divide(bits_written, BYTE_SIZE); ++i) {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(encoded_buf[i]));
    }
    printf("\n");


    printf("Bytes written: %d\n", (bits_written/8)+1);

    return 0;
}
