#include "logging.h"
#include <stdio.h>

// Global callback configuration
static wavekit_log_callback_t g_log_callback = NULL;
static wavekit_log_level_t g_log_level = WAVEKIT_LOG_INFO;

// Callback configuration setters
void wavekit_log_callback_set(wavekit_log_callback_t callback) {
	g_log_callback = callback;
}

void wavekit_log_level_set(wavekit_log_level_t level) {
	g_log_level = level;
}

// Wrapper function over provided callback configuration
void wavekit_internal_log(
	wavekit_log_level_t level, const char *file, int line, const char *fmt, ...
) {
	if (level < g_log_level) return;

	if (g_log_callback) {
		va_list args;
		va_start(args, fmt);
		g_log_callback(level, file, line, fmt, args);
		va_end(args);
	}
}
