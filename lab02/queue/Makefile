# Compilador e Flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g -I$(SRC_DIR) -I$(UNITY_DIR)

# Diretórios
SRC_DIR   = src
TEST_DIR  = tests
UNITY_DIR = Unity
BIN_DIR   = bin

# Arquivos-fonte
QUEUE_SRC = $(SRC_DIR)/queue.c
APP_SRC   = $(SRC_DIR)/testafila.c $(QUEUE_SRC)
UNITY_SRC = $(UNITY_DIR)/unity.c
TEST_SRC  = $(TEST_DIR)/test_queue.c $(QUEUE_SRC) $(UNITY_SRC)

# Executáveis
APP_BIN   = $(BIN_DIR)/testafila
TEST_BIN  = $(BIN_DIR)/test_queue

.PHONY: all test run clean

# Regra padrão: compila os testes e a aplicação
all: $(APP_BIN) $(TEST_BIN)

# Garante a existência do diretório bin
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compila o programa principal (testafila)
$(APP_BIN): $(APP_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(APP_SRC) -o $@

# Compila o executável de testes unitários com o Unity
$(TEST_BIN): $(TEST_SRC) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $@

# Compila e roda os testes unitários (TDD)
test: $(TEST_BIN)
	@echo "--- Executando testes unitários ---"
	@./$(TEST_BIN)

# Compila e roda o programa principal
run: $(APP_BIN)
	@echo "--- Executando testafila ---"
	@./$(APP_BIN)

# Limpeza dos binários gerados
clean:
	@rm -rf $(BIN_DIR)
	@echo "Arquivos de compilação limpos."
