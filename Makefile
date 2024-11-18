# Variables
CC = g++                  # Compilador
CFLAGS = -Wall -pthread   # Opciones de compilación
SRC = src/prueba.cpp      # Archivo fuente
OBJ = $(SRC:.cpp=.o)      # Archivos objeto
EXEC = simulador          # Nombre del ejecutable
BUILD_DIR = build         # Carpeta para guardar el ejecutable

# Reglas
all: $(BUILD_DIR)/$(EXEC)

# Crear el ejecutable en la carpeta BUILD_DIR
$(BUILD_DIR)/$(EXEC): $(OBJ)
	mkdir -p $(BUILD_DIR)             # Crear carpeta si no existe
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compilar archivos .cpp a .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJ)
	rm -rf $(BUILD_DIR)
