#include <stdio.h>
#include "../include/huffman_encode.h"

int main(int argc, char * argv []) {

    //Generate alphabet
    int i,j;
    printf("{\n\"0\",\n");
    for(i=1; i<127; ++i) {
        printf("\"1");
        for(j=0; j<i; ++j) {
            printf("0");
        }
        printf("\",\n");
    }

    return 0;
}
