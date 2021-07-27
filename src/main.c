#include "../include/huffman_code.h"

int main() {
    
    char test_word[] = "abcdefghijklmnopqrstuvxyz .,a?5233445?23012sdf1>";
    int buf[5000];
    int buf1[5000];
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
    bits_written = encode_string(test_word1, strlen(test_word1)+1, buf, 5000);

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

    char out_buf1[1000];
    decode_string(buf, bits_written, out_buf, 1000);
    printf("\nDecoded value 1\n");
    printf("\"%s\"\n", out_buf);

    /*FILE* fptr = fopen("../test/sample_values.txt", "r");

    if(fptr == NULL) {
        return -1;
    }

    char char_buf[100];

    fgets(char_buf, 100, fptr);

    int num_chars = atoi(char_buf);

    char fbuf[num_chars];

    printf("Size if file: %d", num_chars );

    char c;
    i=-1;
    while((c = fgetc(fptr)) != EOF) {
        fbuf[++i] = c;
    }

    fclose(fptr);*/

    return 0;
}
