#ifndef WAVEKIT_LOGGING_H
#define WAVEKIT_LOGGING_H

#include <stdarg.h>

typedef enum {
	WAVEKIT_LOG_DEBUG,
	WAVEKIT_LOG_INFO,
	WAVEKIT_LOG_WARN,
	WAVEKIT_LOG_ERROR
} wavekit_log_level_t;

// platform defined callback function
typedef void (*wavekit_log_callback_t)(
	wavekit_log_level_t, const char* file, int line, const char* fmt, va_list args
);

// logging configuration
void wavekit_log_callback_set(wavekit_log_callback_t callback);
void wavekit_log_level_set(wavekit_log_level_t level);

#endif // !WAVEKIT_LOGGING_H
