#include <stdio.h>
#include <stdlib.h>

#include "../include/huffman_encode.h"



int main() {

    int i=0;
    long double sum_of_p = 0.0;
    for(i =0; i<ALPHABET_SIZE; i++) {
        sum_of_p += PROBABILITIES[i];
        printf("p[%03d]=%1.100Lf\n", i, PROBABILITIES[i]);
    }

    printf("sum: %1.100Lf\n", sum_of_p);

    
    return 0;
}
