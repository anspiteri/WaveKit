#ifndef ADV_UTILS_H
#define ADV_UTILS_H

#include "track_utils.h"

#include <stddef.h>

// Returns a string containing <start>,<end> ad pairs in target
char* util_identify(struct track* target, struct track* ad);

// Insert a portion of src_track into dest_track at position destpos
void tr_insert(struct track* src_track,
            struct track* dest_track,
            size_t destpos, size_t srcpos, size_t len);

#endif
