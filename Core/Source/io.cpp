#include "io.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

#define DATA_OFFSET 40
#define CHUNK_SIZE(x) (x) + 36
#define SUB_CHUNK_1_SIZE 16
#define SUB_CHUNK_2_SIZE(x) (x) * 2
#define AUDIO_FMT 1
#define NUM_CHANNELS 1
#define SAMPLE_RATE 8000
#define BITS_PER_SAMPLE 16

void w_load(const char* fname, int16_t* dest) {
    int32_t data_s = -1;
    
    errno = 0;
    FILE* fp = fopen(fname, "r");

    if (fp == NULL) {
	    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
	    return;
    }

    errno = 0;
    if (fseek(fp, DATA_OFFSET, SEEK_SET) != 0) {
	    fprintf(stderr, "Error traversing file: %s\n", strerror(errno));
	    fclose(fp);
	    return; 
    }
    
    errno = 0;
    if (fread(&data_s, sizeof(int32_t), 1, fp) != 1) {	
	    fprintf(stderr, "Error reading file: error or EOF.\n"); 
	    fclose(fp);
	    return;	
    }
    
    if (data_s == -1) {
	    fprintf(stderr, "Error, data_s never initialised.\n");
	    return;
    }
    
    fread(dest, sizeof(int16_t), data_s, fp);
    
    fclose(fp);
    return;
}

void print_write_error() {
    fprintf(stderr, "Writing failed, aborting.\n");
    return;
}

// Create/write a WAV file from buffer
void w_save(const char* fname, int16_t* src, size_t len) {
    const char* chunk_id = "RIFF";
    const uint32_t chunk_s = CHUNK_SIZE(len);
    const char* format = "WAVE";
    const char* sub_chunk_1_id = "fmt ";
    const uint32_t sub_chunk_1_s = SUB_CHUNK_1_SIZE;
    const uint16_t audio_f = AUDIO_FMT;
    const uint16_t num_channels = NUM_CHANNELS;
    const uint32_t sample_rate = SAMPLE_RATE;
    const uint32_t byte_rate = SAMPLE_RATE * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    const uint16_t block_align = NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    const uint16_t bits_per_sample = BITS_PER_SAMPLE;
    const char* sub_chunk_2_id = "data";
    const uint32_t sub_chunk_2_s = SUB_CHUNK_2_SIZE(len); 

    FILE* fp = fopen(fname, "w");
    if (fp == NULL) {
	    fprintf(stderr, "Error opening file: %s\n", strerror(errno));
	    print_write_error();
	    return;
    }
    
    // CHUNK ID
    if (fwrite(chunk_id, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // CHUNK SIZE
    if (fwrite(&chunk_s, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // FORMAT
    if (fwrite(format, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // SUB CHUNK 1 ID
    if (fwrite(sub_chunk_1_id, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // SUB CHUNK 1 SIZE
    if (fwrite(&sub_chunk_1_s, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // AUDIO FORMAT
    if (fwrite(&audio_f, sizeof(char), 2, fp) != 2) {
	    print_write_error();
	    return;
    }
    // NUM CHANNELS
    if (fwrite(&num_channels, sizeof(char), 2, fp) != 2) {
	    print_write_error();
	    return;
    }
    // SAMPLE RATE
    if (fwrite(&sample_rate, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // BYTE RATE
    if (fwrite(&byte_rate, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // BLOCK ALIGN
    if (fwrite(&block_align, sizeof(char), 2, fp) != 2) {
	    print_write_error();
	    return;
    }
    // BITS PER SAMPLE
    if (fwrite(&bits_per_sample, sizeof(char), 2, fp) != 2) {
	    print_write_error();
	    return;
    }
    // SUB CHUNK 2 ID
    if (fwrite(sub_chunk_2_id, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // SUB CHUNK 2 SIZE
    if (fwrite(&sub_chunk_2_s, sizeof(char), 4, fp) != 4) {
	    print_write_error();
	    return;
    }
    // DATA
    if (fwrite(src, sizeof(uint16_t), len, fp) != len) {
	    print_write_error();
	    return;
    }

    if (fclose(fp) != 0) {
	    fprintf(
            stderr, "Write error: %s, may not have saved properly.\n", 
            strerror(errno)
        );
    }

    return;
}
