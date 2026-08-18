#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stddef.h>

struct wav_header {
    char chunk_id[5];
    uint32_t chunk_size;
    char format[5];
    char sub_chunk_1_id[5];
    uint32_t sub_chunk_1_size;
    char audio_format[2];
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    char sub_chunk_2_id[5];
    uint32_t sub_chunk_2_size;
};

/**
 * Loads a WAV file into a buffer.
 * 
 * @param fname Path of .wav file to load
 * @param dest buffer to load file contents to
 */
void w_load(const char* fname, int16_t* dest);

/**
 * Creates a WAV file from buffer
 * 
 * @param fname Path of .wav file to write to
 * @param src Buffer to copy file contents from
 * @param len Number of samples to copy from buffer
 */
void w_save(const char* fname, int16_t* src, size_t len);

#endif