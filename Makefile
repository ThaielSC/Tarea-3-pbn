# Nombre del ejecutable
TARGET = juego

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++17 -Wall -Wextra

# Busca todos los archivos .cpp del directorio actual
SRCS = $(wildcard *.cpp)

# Reemplaza .cpp por .o para obtener los objetos
OBJS = $(SRCS:.cpp=.o)

# Regla principal
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Ejecutar el programa
run: all
	./$(TARGET)

# Limpieza
clean:
	rm -f $(TARGET) *.o