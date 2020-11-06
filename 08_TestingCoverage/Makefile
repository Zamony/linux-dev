CC = gcc
CFLAGS = -Wall
LDFLAGS = -shared -fPIC
PROFILE_CFLAGS = $(CFLAGS) --coverage -g -O0
PROFILE_LDFLAGS = $(LDFLAGS) -lgcov

SRC_DIR = src
TESTS_DIR = test
BUILD_DIR = build
LIB = $(BUILD_DIR)/libbuf.so
TEST_BIN = $(BUILD_DIR)/test

TEST_FLAGS = `pkg-config --cflags check`
CHECK_LIBS = `pkg-config --libs check`
TEST_LIBS  = $(CHECK_LIBS) -L$(BUILD_DIR) -lbuf

all: $(LIB) $(TEST_BIN)

.ts.c:
	checkmk $< > $@

$(LIB): $(SRC_DIR)/buf.c $(SRC_DIR)/buf.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $(LIB)

$(TEST_BIN): $(TESTS_DIR)/test.c $(LIB)
	$(CC) $(TEST_FLAGS) -I$(SRC_DIR) $< -o $@ $(TEST_LIBS)

profile: $(SRC_DIR)/buf.c $(SRC_DIR)/buf.h $(TEST_BIN)
	$(CC) $(PROFILE_CFLAGS) $(PROFILE_LDFLAGS) $< -o $(LIB)
	LD_LIBRARY_PATH=$(BUILD_DIR) ./$(TEST_BIN)

check: $(TEST_BIN)
	LD_LIBRARY_PATH=$(BUILD_DIR) ./$(TEST_BIN)

clean:
	rm build/*  || true
	rm test/*.c || true
	rm *.gcno   || true
	rm *.gcda   || true
	rm *.gcov   || true

.SUFFIXES:
.SUFFIXES: .ts .c
.PHONY: all clean check profile