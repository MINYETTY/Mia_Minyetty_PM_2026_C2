CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC_DIR = src
BUILD_DIR = build
BIN = mosler_risk

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR) $(BIN)

.PHONY: all run clean
