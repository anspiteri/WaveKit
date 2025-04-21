#include "track_utils.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define INIT_TR_SEC 2
#define SAMPLE_RATE 8000
#define N_CHANNELS 1

// Initialize a new track object
struct track* tr_init() {
    struct track* t = (struct track*)malloc(sizeof(struct track));

    if (t == NULL) {
	    fprintf(stderr, "Error: unable to allocate memory for track struct.\n");
	    return NULL;
    }	
    
    t->sample_n = 0;
    t->allocation_s = INIT_TR_SEC * SAMPLE_RATE * N_CHANNELS;
    t->data = (int16_t*)calloc(t->allocation_s, sizeof(int16_t));

    if (t->data == NULL) {
	    fprintf(stderr, "Error: unable to allocate memory for track sample array.\n");
	    return NULL;
    }

    return t;
}    

// Destroy a track object and free all allocated memory
void tr_destroy(struct track* obj) {
    free((void*)obj->data);
    obj->data = NULL;
    
    free((void*)obj);
    obj = NULL;
    
    return;
}

// Return the length of the segment
size_t tr_length(struct track* seg) {
    return seg->sample_n;
}

// Read len elements from position pos into dest
void tr_read(struct track* t, int16_t* dest, size_t pos, size_t len) {
    if ((pos >= t->sample_n) || (len > (t->sample_n - pos))) {
	    fprintf(stderr, "read failed: reading greater than specified position.");
	    return;
    }

    memcpy(dest, t->data + pos, len * sizeof(int16_t)); 
    return;
}

// Write len elements from src into position pos
void tr_write(struct track* t, int16_t* src, size_t pos, size_t len) {
    // dynamic resize if required: expands by factor of 2 until > pos+len.
    if (pos >= t->allocation_s || (t->allocation_s - pos) < len) {	
	    size_t n_size = t->allocation_s;
	    do {
	        n_size *= 2;
	    } while (n_size < (pos + len));

	    int16_t* new_data = (int16_t*)realloc(t->data, n_size * sizeof(int16_t));
	    if (new_data == NULL) {
	        fprintf(stderr, "Write error, could not resize track: %s\n", strerror(errno));
	        return;
        } else {
            memset(new_data + t->allocation_s, 0, 
                    (n_size - t->allocation_s) * sizeof(int16_t));
        }

        t->data = new_data;
        t->allocation_s = n_size;
    }

    // write to track data & recalculate n_samples
    memcpy(t->data + pos, src, len * sizeof(int16_t));
    size_t end_pos = pos + len;
    if (end_pos > t->sample_n) {
	    t->sample_n = end_pos;
    }
    
    return;
}

// Delete a range of elements from the track
bool tr_delete_range(struct track* t, size_t pos, size_t len) {
    if ((pos > t->sample_n) || ((pos + len) > t->sample_n)) {
	    return false;
    }
    
    size_t data_tail = t->sample_n - (pos + len);
    memmove(t->data + pos, t->data + pos + len, data_tail * sizeof(int16_t));

    t->sample_n = t->sample_n - len;

    if (t->sample_n < (t->allocation_s / 2)) {
        int16_t* new_data = (int16_t*)realloc(
                    t->data, (t->allocation_s / 2) * sizeof(int16_t)
                );
        if (new_data != NULL) {
            t->data = new_data;
            t->allocation_s /= 2;
        }
    }
    return true;
}
