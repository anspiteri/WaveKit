# Makefile for Wavekit Library

CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter
TARGET = wavekit.a

SRC_DIR = core/src
BUILD_DIR = build
HEADER_DIR = core/headers

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

show:
	@ echo "Listed source: $(SRC_FILES)"
	@ echo "Corresponding objects: $(OBJ_FILES)"
	@ echo "Config: $(CC) $(CFLAGS)"
	@ echo "Target: $(TARGET)"

.PHONY: all clean show

clean:
	rm -f $(OBJ_FILES) $(TARGET)
