CXX = gcc
OPTIONS = -Wall -g
EXE_DIR = tmp


all: $(EXE_DIR)/main

create_tmp_dir:
	mkdir -p $(EXE_DIR)

$(EXE_DIR)/huffman_code.o: app/huffman_code.c create_tmp_dir
	$(CXX) -c app/huffman_code.c -o $(EXE_DIR)/huffman_code.o

$(EXE_DIR)/lib_huffman_code.a: $(EXE_DIR)/huffman_code.o create_tmp_dir
	ar rcs $(EXE_DIR)/lib_huffman_code.a $(EXE_DIR)/huffman_code.o

$(EXE_DIR)/main.o: create_tmp_dir
	$(CXX) -c src/main.c -o $(EXE_DIR)/main.o

$(EXE_DIR)/main: $(EXE_DIR)/main.o $(EXE_DIR)/lib_huffman_code.a create_tmp_dir
	$(CXX) -o $(EXE_DIR)/main $(EXE_DIR)/main.o -L./$(EXE_DIR) -l_huffman_code $(OPTIONS)

clean:
	rm -f $(EXE_DIR)/*.a $(EXE_DIR)/*.o $(EXE_DIR)/main
	
