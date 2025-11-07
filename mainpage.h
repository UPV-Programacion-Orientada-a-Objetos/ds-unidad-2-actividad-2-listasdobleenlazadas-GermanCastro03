// ============================================================================
// mainpage.h - Página Principal de Documentación (Doxygen)
// ============================================================================

#ifndef MAINPAGE_H
#define MAINPAGE_H

/**
 * @mainpage Decodificador PRT-7 - Sistema de Decodificación Industrial
 * 
 * @section intro_sec Introducción
 * 
 * Sistema completo de decodificación del protocolo industrial PRT-7.
 * El protocolo transmite instrucciones para ensamblar mensajes ocultos
 * usando dos tipos de tramas:
 * - **Tramas LOAD (L)**: Cargan fragmentos de datos
 * - **Tramas MAP (M)**: Modifican el estado del rotor de cifrado
 * 
 * @section arch_sec Arquitectura
 * 
 * El sistema implementa:
 * - **POO Avanzada**: Herencia y polimorfismo con TramaBase
 * - **Estructuras de Datos Manuales**:
 *   - Lista Circular Doblemente Enlazada (RotorDeMapeo)
 *   - Lista Doblemente Enlazada (ListaDeCarga)
 * - **Comunicación Serial**: Lectura en tiempo real desde Arduino
 * 
 * @section protocol_sec Protocolo PRT-7
 * 
 * Formato de tramas:
 * ```
 * L,X  -> Carga el carácter X (será decodificado)
 * M,N  -> Rota el rotor N posiciones
 * ```
 * 
 * Ejemplo de secuencia:
 * ```
 * L,H    -> H (sin rotación)
 * L,O    -> O (sin rotación)
 * M,2    -> Rotar +2
 * L,A    -> C (A rotado +2)
 * M,-2   -> Rotar -2 (volver)
 * L,D    -> D (sin rotación)
 * ```
 * 
 * @section usage_sec Uso del Sistema
 * 
 * 1. Compilar con CMake:
 *    ```bash
 *    mkdir build && cd build
 *    cmake ..
 *    make
 *    ```
 * 
 * 2. Conectar Arduino y cargar el transmitter
 * 
 * 3. Ejecutar decodificador:
 *    ```bash
 *    ./decodificador_prt7 /dev/ttyUSB0  # Linux
 *    decodificador_prt7.exe COM3        # Windows
 *    ```
 * 
 * @section classes_sec Clases Principales
 * 
 * - TramaBase: Clase base abstracta para polimorfismo
 * - TramaLoad: Implementa carga de fragmentos
 * - TramaMap: Implementa rotación del rotor
 * - RotorDeMapeo: Lista circular para cifrado César
 * - ListaDeCarga: Lista doble para almacenar resultado
 * - SerialPort: Comunicación multiplataforma
 * 
 * @section author_sec Autor
 * 
 * Proyecto educativo - Estructuras de Datos Avanzadas
 * 
 * @section license_sec Licencia
 * 
 * Material educativo de uso libre para fines académicos.
 */

#endif // MAINPAGE_H
