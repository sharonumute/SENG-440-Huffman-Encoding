#include "../include/huffman_code.h"
#include <sys/time.h>

/**
 * Description: Opens file specified by fpath, and preforms encoding operation 
 * and decoding operation. Records time taken to perform decoding, and outputs statistics
 * to the screen.
 *
 * Parameter: (char *) fpath: Path to test file to open
 * 
 * Parameter: (int) naive_bool: flag to determine weather naive decode function should be called
 *                            or if optimized decode function should be called
 *
 * Parameter: (int) io_ratio: Relative size of ouput buffer compared to input buffer size 
            (determines amount of space to allocate on the heap, depending on what kind of test is being done)
 *
 */
int run_test_file(char * fpath, int naive_bool, int io_ratio) {
    char char_buf[100], c;
    FILE *fptr;
    uint32_t num_chars, i, num_mismatches = 0;
    uint32_t bits_written;
    int c_int;

    fptr = fopen(fpath, "r");

    if(fptr == NULL) {
        fprintf(stderr, "Couldn't open file\n");
        return -1;
    }

    //Read the number of characters to encode from the file
    fgets(char_buf, 100, fptr);


    //Convert to int
    num_chars = atoi(char_buf);
    if(num_chars == 0) {
        printf("Please add number of characters on first line of file\n");
        return -2;
    }

    printf("Doing %s test using %s file of size %u\n", 
        naive_bool ? "naive":"optimized", fpath, num_chars);


    uint32_t * encoded_buf = malloc(num_chars*sizeof(uint32_t)*io_ratio);
    char fbuf[num_chars];
    char decode_buf[num_chars];    

    i=0;
    while((c_int = (int)fgetc(fptr)) != EOF) {
        c = (char)c_int;
        fbuf[i++] = c;
    }

    fclose(fptr);

    //Encode the string
    bits_written = encode_string(fbuf, num_chars, encoded_buf, num_chars*io_ratio);
    
    if(bits_written == 0) {
        printf("Not a big enough buffer\n");
        return -1;
    }
    
    struct timeval t0, t1;
    if(!naive_bool) {
            gettimeofday(&t0, NULL);
            for(i=0; i<1000; ++i) {
                decode_string(encoded_buf, bits_written, decode_buf, num_chars);
            }
            gettimeofday(&t1, NULL);
    } else {
            gettimeofday(&t0, NULL);
            for(i=0; i<1000; ++i) {
                naive_decode_string(encoded_buf, bits_written, decode_buf, num_chars);
            }
            gettimeofday(&t1, NULL);
    }

    printf("Did %u calls in %.2g seconds\n", i, t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));

    if(!naive_bool) {
        num_chars = decode_string(encoded_buf, bits_written, decode_buf, num_chars);
    } else{ 
        num_chars = naive_decode_string(encoded_buf, bits_written, decode_buf, num_chars);
    }

    if(num_chars == 0){
        fprintf(stderr, "Decode did not work\n");
        return -1;
    }


    for(i=0; i < num_chars; ++i) {
        if(fbuf[i] != decode_buf[i]) {
            ++num_mismatches;
            printf("Mismatch at char %i of %i chars\n",i+1,num_chars);
            printf("Should be, "FOUR_BYTES_TO_BINARY_PATTERN" but is "FOUR_BYTES_TO_BINARY_PATTERN"\n", 
                FOUR_BYTES_TO_BINARY(fbuf[i]), FOUR_BYTES_TO_BINARY(decode_buf[i]));
            printf("Should be, %i but is %i\n", fbuf[i], decode_buf[i]);
        };
    }

    //printf("%s\n", decode_buf);

    free(encoded_buf);

    printf("Encoding used %u bytes. Original string was %u bytes long\n", bits_written/8+((bits_written%32)?1:0)*4, num_chars);

    printf("Num mismatches: %i\n", num_mismatches);

    return num_mismatches;
}

int main() {
    const int NAIVE_DECODE = 1;
    const int OPTIMIZED_DECODE = 0;

    //run_test_file("./test/sample_values.txt", NAIVE_DECODE);
    //run_test_file("./test/sample_values2.txt", NAIVE_DECODE);
    run_test_file("./test/average_sample.txt", NAIVE_DECODE, 1);
    run_test_file("./test/best_sample.txt", NAIVE_DECODE, 1);
    //run_test_file("./test/worst_sample.txt", NAIVE_DECODE, 16);
    //run_test_file("./test/sample_values3.txt", 1);

    //run_test_file("./test/sample_values.txt", OPTIMIZED_DECODE);
    run_test_file("./test/average_sample.txt", OPTIMIZED_DECODE, 1);
    run_test_file("./test/best_sample.txt", OPTIMIZED_DECODE, 1);
    //run_test_file("./test/worst_sample.txt", OPTIMIZED_DECODE, 16);
    //run_test_file("./test/sample_values3.txt", 0);
    return 0;
}
