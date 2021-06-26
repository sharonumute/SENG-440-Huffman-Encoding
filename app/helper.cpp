#include <algorithm>
#include <functional>
#include <iostream>
#include <string_view>
#include <vector>

#include "../include/huffman_encode.h"

int main(int argc, char * argv []) {
    std::array<char, ALPHABET_SIZE> alpha; 

	for(int i=0; i<ALPHABET_SIZE; ++i) {
		alpha[i] = ALPHABET[i]; 
	}

    std::make_heap(alpha.begin(), alpha.end(), std::greater<>{});

    for(int i=0; i<ALPHABET_SIZE; ++i) {
        std::cout << (int)alpha[i] << std::endl;
    }

    return 0;
}
