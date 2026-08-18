#ifndef TOOLS_H
#define TOOLS_H

#include "track_utils.h"

#include <stddef.h>

/**
 * Finds any instances of a specified track occuring in another track.
 * 
 * @param target Track @struct to be searched
 * @param ad Track @struct search for in target
 * 
 * @return A string containing <start>, <end> ad pairs in target
 */
char* tool_identify(struct track* target, struct track* ad);

#endif