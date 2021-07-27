all: main

main: libs
	gcc -lm -o tmp/main src/main.c -L./tmp -l_huffcode

tmp/huffman_code.o: app/huffman_code.c
	gcc -O -c app/huffman_code.c

tmp/lib_huffcode.a: tmp/huffman_code.o
	ar rcs tmp/lib_huffcode.a tmp/huffman_code.o

libs: tmp/lib_huffcode.a

clean:
	rm -f tmp/*