# Makefile para el Juego Educativo de Plataformas
# Compilador y flags

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
LIBS = -lSDL2 -lSDL2main

# Directorios
SRC_DIR = src
BUILD_DIR = build
TARGET = juego_educativo

# Archivos fuente
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Regla principal
all: $(BUILD_DIR) $(TARGET)

# Crear directorio de build
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Compilación exitosa! Ejecutable: $(TARGET)"

# Compilar archivos objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos compilados
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)
	@echo "Archivos limpiados"

# Ejecutar el juego
run: $(TARGET)
	./$(TARGET)

# Instalar dependencias (Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install libsdl2-dev libsdl2-2.0-0

# Verificar instalación de SDL2
check-sdl:
	@echo "Verificando instalación de SDL2..."
	@pkg-config --exists sdl2 && echo "SDL2 encontrado" || echo "SDL2 NO encontrado - ejecuta 'make install-deps'"

# Reglas que no son archivos
.PHONY: all clean run install-deps check-sdl

# Información de ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make          - Compilar el juego"
	@echo "  make run      - Compilar y ejecutar el juego"
	@echo "  make clean    - Limpiar archivos compilados"
	@echo "  make install-deps - Instalar dependencias SDL2"
	@echo "  make check-sdl    - Verificar instalación de SDL2"
	@echo "  make help     - Mostrar esta ayuda"
