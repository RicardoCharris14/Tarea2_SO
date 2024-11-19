# Variables
CC = g++                 # Compilador
CFLAGS = -Wall -pthread -Iinclude  # Opciones de compilación, incluye directorio de encabezados
SRC_DIR = src            # Directorio de archivos fuente
BUILD_DIR = build         # Carpeta para los archivos objeto
EXEC = simulador          # Nombre del ejecutable

# Archivos fuente y objeto
SRC = $(wildcard $(SRC_DIR)/*.cpp)  # Encuentra automáticamente todos los .cpp en src/
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC))

# Regla principal
all: $(BUILD_DIR) $(EXEC)
# Crear el ejecutable
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

# Compilar cada archivo fuente a objeto
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Crear la carpeta build si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Limpieza de archivos generados
clean:
	rm -rf $(BUILD_DIR) $(EXEC) logs/*.log
