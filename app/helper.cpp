
#include <stdio.h>

int main() {
    int i;

    long double p = 0.5;


    printf("const long double ALPHABET = {");
    for(i=0; i<127; ++i) {
        if(!(i%10)) printf("\n");
        printf("%03d,", i);
        //printf("\t%1.100LfL,\n", p);
        //p *= 0.5;
    }
    //printf("\t%1.100LfL\n", p);
    printf("03%d", i);
    printf("};");

}
