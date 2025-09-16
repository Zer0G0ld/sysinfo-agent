# ---------------- Caminhos ----------------
INCLUDE_DIR = include
SRC_DIR     = src
BUILD_DIR   = build
BIN_DIR     = bin

# ---------------- Compilador e flags ----------------
CC      = gcc
CFLAGS  = -I$(INCLUDE_DIR) -Wall -O2
LDFLAGS = 

# ---------------- Módulo e teste ----------------
MODULE = cpu
TEST   = test_cpu

SRC_MODULE = $(SRC_DIR)/$(MODULE).c
SRC_TEST   = $(SRC_DIR)/$(TEST).c

OBJ_MODULE = $(BUILD_DIR)/$(MODULE).o
OBJ_TEST   = $(BUILD_DIR)/$(TEST).o

EXE = $(BIN_DIR)/$(TEST).exe

# ---------------- Alvo padrão ----------------
all: build

# Compila o executável
build: $(EXE)

# Executa o teste
test: build
	@echo "Running $(TEST)..."
	$(EXE)

# ---------------- Objetos ----------------
$(OBJ_MODULE): $(SRC_MODULE)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_TEST): $(SRC_TEST)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------- Executável ----------------
$(EXE): $(OBJ_MODULE) $(OBJ_TEST)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJ_MODULE) $(OBJ_TEST) -o $(EXE) $(LDFLAGS)

# ---------------- Limpar ----------------
clean:
	@echo "Cleaning build and bin directories..."
	-rm -rf $(BUILD_DIR)/* $(BIN_DIR)/*
