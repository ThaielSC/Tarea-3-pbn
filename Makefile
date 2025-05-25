CXX = g++
CXXFLAGS = -Wall -Wextra -Wundef -Werror -Wuninitialized -Winit-self -std=c++17
LDFLAGS = # Puedes añadir aquí flags para el enlazador, ej: -lsfml-graphics
LDLIBS =  # Puedes añadir aquí bibliotecas a enlazar, ej: -lm

TARGET = tarea3
SRCDIR = src
BUILDDIR = build

# Lista de directorios donde buscar archivos fuente .cpp
SOURCEDIRS = $(SRCDIR) $(SRCDIR)/classes $(SRCDIR)/utils

# Encuentra todos los archivos .cpp en los directorios especificados
SOURCES = $(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.cpp))

# Alternativa recursiva (más flexible si añades nuevos subdirectorios bajo src):
# SOURCES = $(shell find $(SRCDIR) -name '*.cpp' -type f)

OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Establece el objetivo por defecto
.DEFAULT_GOAL := all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Enlazando $@"
	$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compilando $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@echo "Ejecutando $(TARGET)..."
	./$(TARGET)

clean:
	@echo "Limpiando..."
	rm -rf $(BUILDDIR) $(TARGET)

# Añade 'run' a la lista de objetivos PHONY
.PHONY: all clean run
