#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/huffman_encode.h"

char** encode_letter(int target){
    char ** encoded= malloc(130 * sizeof(char*));
    for (size_t i = 0; i < target; i++)
    {
        strcat(encoded, "1");
    }
    strcat(encoded, "0");
	return encoded;
}

char** decode_sentence(char * target){
    char * t;
    char ** decoded= malloc(128 * sizeof(char*));

    int count = 0;
    for (t = target; *t != '\0'; t++) {
        if (*t == '1'){
            count++;
        }else if (*t == '0'){
            char buffer[3];
            sprintf(buffer, "%d", count);
            strcat(decoded, buffer);
            count = 0;
        }
    }

    return decoded;
}

int main() {

    int i=0;
    long double sum_of_p = 0.0;
    for(i =0; i<ALPHABET_SIZE; i++) {
        sum_of_p += PROBABILITIES[i];
        printf("p[%03d]=%1.100Lf\n", i, PROBABILITIES[i]);
    }

    printf("sum: %1.100Lf\n", sum_of_p);

    printf("%s\n", encode_letter(127));
    printf("%s\n", decode_sentence("0101100"));
    return 0;
}