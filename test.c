#include <stdio.h>

volatile int a, b;

int main( void) {
  a = 1;
  b = 2;
  printf( "a + b = %i\n", a+b);
}

