CC = gcc
CFLAGS = -Wall

CURR_DIR = $(shell pwd)
TEST_DIR = test_dir

.PHONY: all
all: remove fake_unlink.so

fake_unlink.so: fake_unlink.c
	$(CC) $(CFLAGS) -shared -fPIC $^ -ldl -o $@

.PHONY: remove
remove: remove.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: test-fake
test-fake:export LD_PRELOAD=$(CURR_DIR)/fake_unlink.so
test-fake:
	mkdir -p $(TEST_DIR)

	touch $(TEST_DIR)/fileFIX
	./remove $(TEST_DIR)/fileFIX || true
	test -f $(TEST_DIR)/fileFIX

	touch $(TEST_DIR)/file
	./remove $(TEST_DIR)/file

	rm -rf $(TEST_DIR)


.PHONY: test-origin
test-origin:
	mkdir -p $(TEST_DIR)

	touch $(TEST_DIR)/fileFIX
	./remove $(TEST_DIR)/fileFIX

	touch $(TEST_DIR)/file
	./remove $(TEST_DIR)/file

	rm -rf $(TEST_DIR)

.PHONY: tests-run
tests-run: test-fake test-origin
	echo "Tests passed!"

.PHONY: clean
clean:
	rm remove fake_unlink.so || true
	rm -rf $(TEST_DIR) || true