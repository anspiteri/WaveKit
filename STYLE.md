# WaveKit Style Guide
## 1. Functions & Variables (snake_case)

* Public Core: Prefix public functions and variables with wavekit_ to avoid global namespace naming collisions.
	* Example: wavekit_variable_name
* Private Core: Use plain snake_case without a prefix for internal, file-specific names.
* Noun-First Rule: Structure function names as Noun-First, Verb-Second so related actions group together in your IDE's autocomplete.
	* Example: wavekit_wav_load(), wavekit_wav_save()

## 2. Isolation & Scope Management

* Static Functions: Always mark internal-only functions as static to hide them from other files.

## 3. Types, Pointers & Macros

* Constants & Macros: Write all constants and preprocessor macros in ALL_CAPS with underscores.
	* Example: WAVEKIT_MAX_BUFFER
* Custom Types: Suffix custom typedef structures or enums with _t.
	* Example: wavekit_log_level_t
* Pointers: Add a p_ prefix to pointer variable names to clearly visually flag memory indirection.
	* Example: wavekit_wav_t *p_file;

