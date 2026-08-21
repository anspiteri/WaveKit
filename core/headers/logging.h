#ifndef WAVEKIT_LOGGING_H
#define WAVEKIT_LOGGING_H

#include <stdarg.h>

// Macros to be used internally
#define WAVEKIT_LOG_DEBUG(fmt, ...) wavekit_internal_log(WAVEKIT_LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define WAVEKIT_LOG_INFO(fmt, ...) wavekit_internal_log(WAVEKIT_LOG_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define WAVEKIT_LOG_WARN(fmt, ...) wavekit_internal_log(WAVEKIT_LOG_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define WAVEKIT_LOG_ERROR(fmt, ...) wavekit_internal_log(WAVEKIT_LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

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

// internal logging function
void wavekit_internal_log(
	wavekit_log_level_t level, const char *file, int line, const char *fmt, ...
);
#endif // !WAVEKIT_LOGGING_H
