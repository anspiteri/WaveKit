#ifndef TRACK_UTILS_H
#define TRACK_UTILS_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

/* 
 * Track Data Structure.
 *
 * sample_n : number of samples stored in data array, one sample = two bytes.
 * allocation_s : size of allocated to data array in int16_t chunks.
 * data : ptr to sample array located on heap. 
*/
 struct track {
    size_t sample_n;
    size_t allocation_s;
    int16_t* data;
};

/*
 * Initialise a new track object
 * 
 * Returns a pointer to a struct track object on the heap.
 * On failure, prints error and returns NULL. 
*/
struct track* tr_init();

// Destroy a track object and free all allocated memory
void tr_destroy(struct track* obj);

// Return the length of the segment
size_t tr_length(struct track* seg);

// Read len elements from position pos into dest
void tr_read(struct track* t, int16_t* dest, size_t pos, size_t len);

// Write len elements from src into position pos
void tr_write(struct track* t, int16_t* src, size_t pos, size_t len);

// Delete a range of elements from the track
bool tr_delete_range(struct track* t, size_t pos, size_t len);

#endif
