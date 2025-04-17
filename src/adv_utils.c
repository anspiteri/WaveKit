#include "adv_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STARTING_RESULT_S 128 

// Returns a string containing <start>,<end> ad pairs in target
char* util_identify(struct track* target, struct track* ad) {
    char* result = (char*)malloc(STARTING_RESULT_S );
    size_t buffer_s = STARTING_RESULT_S;
    size_t result_len = 0;
    
    if (result == NULL) {
	    return NULL;
    } else {
	    result[0] = '\0';
    }

    // compute auto-correlation of ad at 0.
    double auto_corr = 0;
    for (int i = 0; i < ad->sample_n; i++) {
	    auto_corr += ad->data[i] * ad->data[i];
    }
    
    if (auto_corr == 0) {
	    free((void*)result);
	    return NULL;
    }

    // compute cross-correlation
    for (int i = 0; i <= (target->sample_n - ad->sample_n); ) {
	    double cross_corr = 0;
	    
        for (int j = 0; j < ad->sample_n; j++) {
	        cross_corr += target->data[i+j] * ad->data[j];
	    }
	
	    // Match found: manage result memory.
	    if ((cross_corr / auto_corr) >= 0.95) {
	        char ad_stamps[32];
	        int stamps_len;

	        if (result_len == 0) {
		        stamps_len = snprintf(ad_stamps, sizeof(ad_stamps), 
                        "%d,%d", i, i+ad->sample_n-1);
	        } else {
		        stamps_len = snprintf(ad_stamps, sizeof(ad_stamps), 
                        "\n%d,%d", i, i+ad->sample_n-1);
	        }
	    
	        if (result_len + stamps_len + 1 > buffer_s) {
		        buffer_s = (result_len + stamps_len + 1) * 2;
		        
                if (buffer_s > SIZE_MAX / 2) {
		            free((void*)result);
		            return NULL;
		        }

		        char* r_ptr = (char*)realloc(result, buffer_s);
		
		        if (r_ptr == NULL) {
		            free((void*)result);
		            return NULL;
                }
                
                result = r_ptr;
            }

            memcpy(result + result_len, ad_stamps, stamps_len);
            result_len += stamps_len;
            result[result_len] = '\0';

            i += ad->sample_n;
        } else {
            i++;
        }
    } 
    return result;
}

// Insert a portion of src_track into dest_track at position destpos
void tr_insert(struct track* src_track,
            struct track* dest_track,
            size_t destpos, size_t srcpos, size_t len) {
    
    // Dynamic resize if required: is position to write to outside of array 
    // bounds OR is the length of the write larger than the memory available 
    // at write position.
    if (destpos >= dest_track->allocation_s || 
            (dest_track->allocation_s - destpos) < len) {
            
        size_t n_size = dest_track->allocation_s;
        
        do {
            n_size *= 2;
        } while (n_size < (destpos + len));

        int16_t* new_data 
            = (int16_t*)realloc(dest_track->data, n_size * sizeof(int16_t));
        
        if (new_data == NULL) {
            return;
        } else {
            size_t old_size = dest_track->allocation_s;
            memset(
                new_data + old_size, 
                0, (n_size - old_size) * sizeof(int16_t)
            );
        }
        dest_track->data = new_data;
        dest_track->allocation_s = n_size;
    }

    // write to track data & recalculate n_samples
    memcpy(
        dest_track->data + destpos, 
        src_track->data + srcpos, 
        len * sizeof(int16_t)
    );
    size_t end_pos = destpos + len;
    
    // if we just inserted data past previous end position then update it
    if (end_pos > dest_track->sample_n) {
            dest_track->sample_n = end_pos;
    }

    return;
}
