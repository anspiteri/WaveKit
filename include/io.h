#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stddef.h>

struct wav_header {
    char chunk_id[5]; //big
    uint32_t chunk_size; //little
    char format[5]; //big
    char sub_chunk_1_id[5]; //big
    uint32_t sub_chunk_1_size; //little
    char audio_format[2]; //little
    uint16_t num_channels; //little
    uint32_t sample_rate; //little
    uint32_t byte_rate; //little
    uint16_t block_align; //little
    uint16_t bits_per_sample; //little
    char sub_chunk_2_id[5]; //big
    uint32_t sub_chunk_2_size; //little
};

/*
 * w_load
 *
 *  desc: 
 *      Loads a WAV file into a buffer
 *  params:
 *      fname - path of .wav file to load
 *      dest - buffer to load file contents to
*/
void w_load(const char* fname, int16_t* dest);

/*
 * w_save
 *
 *  desc: 
 *      Creates a WAV file from buffer
 *  params:
 *      fname - path of .wav file to write to
 *      src - buffer to copy file contents from
 *      len - number of samples to copy from buffer
*/
void w_save(const char* fname, int16_t* src, size_t len);

#endif
