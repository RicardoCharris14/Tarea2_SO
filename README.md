
# Tarea 2 SO 2024-2: Simulador Productor-Consumidor y Simulador de Memoria Virtual con paginación.

El proyecto consta de 2 partes. La primera es el simulador de productor-consumidor, que se puede encontrar en el directorio 'simulation'. La segunda consiste del simulador de memoria virtual, el cual se encuentra en el directorio 'direccionamiento virtual'.

## Integrantes
- Ricardo Charris Jimenez
- Juan Umaña
- Vicente Ramírez
- Benjamín Villarroel 
## Instalación y ejecución.
Ambos simuladores fueron desarrollados en Linux, por lo que se necesita este entorno con los compiladores actualizados para poder ejecutarlos correctamente.
### **Clonar repositorio:**
   ```bash
   git clone https://github.com/RicardoCharris14/Tarea2_SO.git
   ```
### **Compilar y ejecutar Parte 1 (Simulador productor-consumidor)**:
  ```
  g++ -std=c++11 -Wall -pthread -Iinclude src/main.cpp src/consumer_producter.cpp src/monitor.cpp src/queue.cpp -o simulador
  ```
  ```
 ./simulador -p <productores> -c <consumidores> -s <tamaño de la cola> -t <tiempo de espera>
  ```
### **Compilar y ejecutar Parte 2 (Simulador de memoria virtual)**
Acceder a la carpeta 'direccionamiento virtual' y ejecutar los siguientes comandos en la terminal:
```
g++ main.cpp tabla_pagina.cpp marco_pagina.cpp pagina_virtual.cpp -o main
```
```
./main -m <n_marcos> -a <algoritmo> -f <file.txt>
```
# Descripción Parte 1:
Esta parte del proyecto es un simulador de una cola circular concurrente. Implementa:
- Gestión concurrente de productores y consumidores.
- Redimensionamiento automático de la cola.
- Archivo log único por ejecución.
- Logs detallados de operaciones y cambios de tamaño.

# Descripción Parte 2:
Esta parte del proyecto consiste de un simulador de memoria virtual utilizando paginación, y algoritmos de reemplazo para el manejo de fallos de página. 
- Implementación de algoritmos de reemplazo Optimo, Fifo, LRU y LRU Reloj.
- Simulación de tablas de página utilizando estructura de datos tabla hash y manejo de colisiones con chaining.
- Lectura de archivo txt con entradas para inserción de páginas.

Notar que el archivo .txt debe tener un formato como el siguiente (Ejemplo del enunciado):
```
0 1 3 4 1 2 5 1 2 3 4
```
