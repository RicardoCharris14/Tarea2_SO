# Simulador de Cola Circular

Una simulación de una cola circular dinámica con soporte para múltiples productores y consumidores. El programa incluye logging para registrar el progreso y cambios en el tamaño de la cola.

## Descripción
Este proyecto es un simulador de una cola circular concurrente diseñado para sistemas Linux. Implementa:
- Gestión concurrente de productores y consumidores.
- Redimensionamiento automático de la cola.
- Archivo log único por ejecución.

## Características
- Redimensionamiento dinámico de la cola.
- Logs detallados de operaciones y cambios de tamaño.
- Compatible con sistemas Linux.
- Gestión de concurrencia usando `pthread`.
## Integrantes
- Juan Umaña
- Ricardo Charris Jimenez
## Requisitos
- Linux.
- `g++` con soporte para C++11 o superior.
- Biblioteca `pthread`.

## Instalación
1. Clona el repositorio:
   ```bash
   git clone https://github.com/RicardoCharris14/Tarea2_SO.git
## Instrucciones de compilación
1.- Compilar el programa:
```
  g++ -std=c++11 -Wall -pthread -Iinclude src/main.cpp src/consumer_producter.cpp src/monitor.cpp src/queue.cpp -o simulador
```
2.- Ejecutar el programa desde la terminal con el comando:
```
 ./simulador -p <productores> -c <consumidores> -s <tamaño de la cola> -t <tiempo de espera>
 ```
