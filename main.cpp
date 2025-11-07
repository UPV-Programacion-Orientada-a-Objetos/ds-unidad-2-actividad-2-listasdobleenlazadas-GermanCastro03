// ============================================================================
// main.cpp - Programa Principal del Decodificador PRT-7
// ============================================================================

#include <iostream>
#include <cstring>
#include <cstdlib>

#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "SerialPort.h"

/**
 * @brief Parsea una línea de texto y crea la trama correspondiente
 * @param linea Línea leída del puerto serial (ej: "L,A" o "M,5")
 * @return Puntero a TramaBase (TramaLoad o TramaMap), o nullptr si hay error
 * 
 * Formato esperado:
 * - "L,X" -> TramaLoad con carácter X
 * - "M,N" -> TramaMap con rotación N
 */
TramaBase* parsearTrama(char* linea) {
    if(!linea || linea[0] == '\0') return nullptr;
    
    char tipo = linea[0];
    
    // Validar formato básico
    if(tipo != 'L' && tipo != 'M') return nullptr;
    if(linea[1] != ',') return nullptr;
    
    if(tipo == 'L') {
        // Trama de carga: L,X
        char caracter = linea[2];
        return new TramaLoad(caracter);
    } else {
        // Trama de mapeo: M,N
        int rotacion = atoi(&linea[2]);
        return new TramaMap(rotacion);
    }
}

/**
 * @brief Función principal del decodificador
 * @param argc Cantidad de argumentos
 * @param argv Array de argumentos (argv[1] = nombre del puerto)
 * @return 0 si éxito, 1 si error
 */
int main(int argc, char* argv[]) {
    // Banner de inicio
    std::cout << "========================================" << std::endl;
    std::cout << "  DECODIFICADOR PRT-7" << std::endl;
    std::cout << "  Sistema de Decodificación Industrial" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    // Determinar puerto serial
    const char* nombrePuerto;
    
    if(argc > 1) {
        // Puerto especificado por línea de comandos
        nombrePuerto = argv[1];
    } else {
        // Puerto por defecto según plataforma
#ifdef _WIN32
        nombrePuerto = "\\\\.\\COM3";
#else
        nombrePuerto = "/dev/ttyUSB0";
#endif
        std::cout << "Usando puerto por defecto: " << nombrePuerto << std::endl;
        std::cout << "Usa: " << argv[0] << " <puerto> para especificar otro puerto\n" << std::endl;
    }
    
    std::cout << "Conectando a puerto: " << nombrePuerto << "..." << std::endl;
    
    // Inicializar estructuras de datos
    ListaDeCarga miListaDeCarga;
    RotorDeMapeo miRotorDeMapeo;
    
    // Conectar al puerto serial
    SerialPort serial(nombrePuerto);
    
    if(!serial.estaConectado()) {
        std::cerr << "\n[ERROR] No se pudo conectar al puerto." << std::endl;
        std::cerr << "Verifica que:" << std::endl;
        std::cerr << "  - El Arduino esté conectado" << std::endl;
        std::cerr << "  - El puerto sea correcto" << std::endl;
#ifndef _WIN32
        std::cerr << "  - Tengas permisos (chmod 666 " << nombrePuerto << ")" << std::endl;
#endif
        return 1;
    }
    
    // Bucle principal de procesamiento
    char buffer[256];
    int tramasProcesadas = 0;
    int intentosSinDatos = 0;
    const int MAX_INTENTOS_SIN_DATOS = 50;  // ~5 segundos sin datos
    
    std::cout << "\n[INFO] Esperando tramas del Arduino..." << std::endl;
    std::cout << "[INFO] Presiona RESET en el Arduino si no transmite\n" << std::endl;
    
    while(true) {
        if(serial.leerLinea(buffer, sizeof(buffer))) {
            // Se recibió una línea
            intentosSinDatos = 0;
            
            // Parsear y procesar
            TramaBase* trama = parsearTrama(buffer);
            
            if(trama) {
                // Trama válida - procesar
                trama->procesar(&miListaDeCarga, &miRotorDeMapeo);
                delete trama;
                tramasProcesadas++;
            } else {
                // Trama mal formada
                std::cout << "[WARN] Trama mal formada: [" << buffer << "]" << std::endl;
            }
        } else {
            // No hay datos disponibles
            intentosSinDatos++;
            
            // Si hemos procesado tramas y no llegan más datos, terminar
            if(tramasProcesadas > 0 && intentosSinDatos >= MAX_INTENTOS_SIN_DATOS) {
                std::cout << "\n[INFO] No se reciben más datos. Finalizando..." << std::endl;
                break;
            }
            
            // Pequeña pausa para no saturar el CPU
#ifdef _WIN32
            Sleep(100);  // 100ms
#else
            usleep(100000);  // 100ms
#endif
        }
    }
    
    // Verificar si se procesó algo
    if(tramasProcesadas == 0) {
        std::cout << "\n[WARN] No se recibieron tramas del Arduino." << std::endl;
        std::cout << "Verifica que el Arduino esté transmitiendo." << std::endl;
        return 1;
    }
    
    // Mostrar mensaje final
    std::cout << "\nFlujo de datos terminado." << std::endl;
    std::cout << "Total de tramas procesadas: " << tramasProcesadas << std::endl;
    
    miListaDeCarga.imprimirMensaje();
    
    std::cout << "\nLiberando memoria... Sistema apagado." << std::endl;
    
    return 0;
}
