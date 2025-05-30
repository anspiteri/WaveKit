#ifndef TRACK_UTILS_H
#define TRACK_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Data structure used for storing groups of audio data in tracks.
 * 
 * @field sample_n Number of samples stored in data array, one sample = two bytes
 * @field allocation_s Size of allocated memory to data array in int16_t chunks
 * @field data Pointer to sample array located on heap
 */
 struct track {
    size_t sample_n;
    size_t allocation_s;
    int16_t* data;
};

/**
 * Initialises a new track @struct
 * 
 * @return A pointer to a track @struct on the heap,
 *         on failure, prints error and returns NULL
 */
struct track* tr_init();

/**
 * Destroys a track @struct and frees all allocated memory.
 * 
 * @param obj The track struct to destroy
 */
void tr_destroy(struct track* obj);

/**
 * Returns the length of the specified track segment.
 * 
 * @param seg The specified track @struct whose length to query
 * 
 * @return The number of samples in the track @struct
 */
size_t tr_length(struct track* seg);

/**
 * Reads specified samples from specified position into specified buffer.
 * 
 * @param t Track to read from
 * @param dest Buffer to read track contents into
 * @param pos Positon in t to read from
 * @param len Specified number of samples to read
 */
void tr_read(struct track* t, int16_t* dest, size_t pos, size_t len);

/**
 * Writes specified number of samples from specified buffer into specified track.
 * 
 * @param t Track @struct to write into
 * @param src Specified buffer to read from
 * @param pos Position in t to write to
 * @param len Specified number of samples to write at pos, NOTE: len must be
 *            less than or equal size of src buffer! 
 */
void tr_write(struct track* t, int16_t* src, size_t pos, size_t len);

/**
 * Deletes a range of samples from a specified track @struct
 * 
 * @param t Track @struct to delete from
 * @param pos Position in t to delete from
 * @param len Specified number of samples to delete at pos
 */
bool tr_delete_range(struct track* t, size_t pos, size_t len);

/**
 * Inserts a portion of audio from specified track to another specified track,
 * where both tracks are track @struct.
 * 
 * @param src_track Specified track to read from
 * @param dest_track Specified track to insert to
 * @param destpos Position in dest_track to insert at
 * @param srcpos Position in src_track to read from
 * @param len Specified number of samples to read from src_track and insert,
 *            NOTE: len must be not exceed the length of src_track from srcpos
 */
void tr_insert(
    struct track* src_track,
    struct track* dest_track,
    size_t destpos, size_t srcpos, size_t len
);

#endif