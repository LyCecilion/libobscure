CC      ?= cc
CFLAGS  ?= -O2 -Wall -Wextra

BUILD_DIR := build
SRC       := src/libobscure.c
TARGET    := $(BUILD_DIR)/libobscure.so

all: $(TARGET)

$(TARGET): $(SRC) | $(BUILD_DIR)
	$(CC) -shared -fPIC $(CFLAGS) -o $@ $<

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
