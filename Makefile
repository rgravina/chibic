C_COMPILER=cc
CFLAGS=-std=c11 -Wall -Wextra
BIN_DIR=./bin
TARGET = chibic
TARGET_TEST = chibic_test
SRC_FILES=\
	src/lexer.c\
	src/parser.c\
	src/node.c\
	src/code.c
SRC_FILES_TEST=\
	test/tap.c \
	test/test_lexer.c \
	test/test_parser.c \
	test/test_code.c \
	test/test_all.c \
	$(SRC_FILES)
INC_DIRS=-Isrc

all: test
chibic: clean _chibic
test: clean _test

_chibic:
	@$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SRC_FILES) src/main.c -o $(BIN_DIR)/$(TARGET)
	@$(BIN_DIR)/$(TARGET)
	@as $(BIN_DIR)/out.s -o $(BIN_DIR)/out.o
	@ld -e _main -o $(BIN_DIR)/out $(BIN_DIR)/out.o
	@$(BIN_DIR)/out;echo $$?

_test:
	@$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SRC_FILES_TEST) -o $(BIN_DIR)/$(TARGET_TEST)
	@$(BIN_DIR)/$(TARGET_TEST)

clean:
	@rm -f $(BIN_DIR)/*.o $(BIN_DIR)/*.s $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(TARGET_TEST) bin/out
