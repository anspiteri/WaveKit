#ifndef TOOLS_H
#define TOOLS_H

#include "track_utils.h"

#include <stddef.h>

// Returns a string containing <start>,<end> ad pairs in target
char* tool_identify(struct track* target, struct track* ad);

#endif