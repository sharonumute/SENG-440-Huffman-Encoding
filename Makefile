#These variables can be set via the command line
ARM = true
ASSEMBLER_CODE = false 
EXE_DIR = tmp

ifeq ($(ARM), true)
CXX = arm-linux-gcc
OPTIONS = -O3 -Werror -Wall -Wextra #-mfloat-abi=softfp
else
OPTIONS = -Ofast -Werror -Wall -Wextra #-fsanitize=address
CXX = gcc
endif



ifeq ($(ASSEMBLER_CODE), true)
all: $(EXE_DIR)/main.s $(EXE_DIR)/huffman_code.s 
else
all: $(EXE_DIR)/main
endif

create_tmp_dir:
	mkdir -p $(EXE_DIR)

$(EXE_DIR)/huffman_code.o: app/huffman_code.c create_tmp_dir
	$(CXX) -c app/huffman_code.c -o $(EXE_DIR)/huffman_code.o $(OPTIONS)

$(EXE_DIR)/huffman_code.s: app/huffman_code.c create_tmp_dir
	$(CXX) -c app/huffman_code.c -S -o $(EXE_DIR)/huffman_code.s $(OPTIONS)

$(EXE_DIR)/lib_huffman_code.a: $(EXE_DIR)/huffman_code.o create_tmp_dir
	ar rcs $(EXE_DIR)/lib_huffman_code.a $(EXE_DIR)/huffman_code.o

$(EXE_DIR)/main.o: create_tmp_dir
	$(CXX) -c src/main.c -o $(EXE_DIR)/main.o $(OPTIONS)

$(EXE_DIR)/main.s: create_tmp_dir $(EXE_DIR)/lib_huffman_code.a
	$(CXX) -c src/main.c -S -o $(EXE_DIR)/main.s $(OPTIONS)

$(EXE_DIR)/main: $(EXE_DIR)/main.o $(EXE_DIR)/lib_huffman_code.a create_tmp_dir
	$(CXX) -o $(EXE_DIR)/main $(EXE_DIR)/main.o -L$(EXE_DIR) -l_huffman_code $(OPTIONS)

clean:
	rm -f $(EXE_DIR)/*.a $(EXE_DIR)/*.o $(EXE_DIR)/main
	
