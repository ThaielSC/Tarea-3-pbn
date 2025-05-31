CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self

SRCDIR = src
BUILDDIR = build
TARGET_NAME = tarea3
TARGET = $(BUILDDIR)/bin/$(TARGET_NAME)

# Lista de directorios donde buscar archivos fuente .cpp
SOURCEDIRS = $(SRCDIR) $(SRCDIR)/classes $(SRCDIR)/utils

# Encuentra todos los archivos .cpp en los directorios especificados
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cpp))

# Alternativa recursiva (más flexible si añades nuevos subdirectorios bajo src):
# SOURCES = $(shell find $(SRCDIR) -name '*.cpp' -type f)

# Define el directorio de objetos
OBJDIR = $(BUILDDIR)/objs

# Crea los nombres de los archivos objeto en el directorio OBJDIR
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)

# Archivo de tests
TEST_SRC = ./tests/tests.cpp
TEST_EXE = $(BUILDDIR)/bin/tests

test: $(TEST_EXE)
	@echo "==> Ejecutando tests..."
	@./$(TEST_EXE)

$(TEST_EXE): $(TEST_SRC) ./src/classes/player.cpp
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $^ -o $@

# Crea el ejecutable a partir de los objects
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	@echo "==> Enlazando: $@"
	@$(CXX) $(LDFLAGS) $^ -o $@ 

# Regla para compilar los archivos fuente a archivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "==> Compilando $< -> $@"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@clear
	@echo "==> Ejecutando $(TARGET_NAME)..."
	@./$(TARGET)

clean:
	@echo "==> Limpiando..."
	@rm -rf $(BUILDDIR)

example:
	@chmod +x ./example/juego
	@cd ./example && ./juego

.PHONY: all clean run example
