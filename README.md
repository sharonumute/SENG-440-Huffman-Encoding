# SENG 440 Project files

Huffman Code implementation:

Seng 440 Final Project Code

Authors: Samuel Barrett, Shron Mute


Compiling:

Use Makefiile to run code. Makefile contains two variables "ARM", "EXE_DIR", and "ASSEMBLER_CODE", which can be set on the command line when running the make file

If the arm variable is set to true, the code uses the arm-linux-gcc compiler, with options for compiling it to run on our ARM embedded system. If it is not (i.e. it is set to false, or undefined), then the Makefile compiles using regulat gcc.

The ASSEMBLER_CODE variable similarily specifies weather to generate assembler code using the -S flag, or weather to generate executables

The variable "EXE_DIR" specifies the the directory to put executables, assembler code, static libraries, and object files.

The Makefile creates a static library lib_huffman_code, which can be linked using -l_huffman_code

It also creates an exectuable ./main, which tests various input files located in the test directory.
