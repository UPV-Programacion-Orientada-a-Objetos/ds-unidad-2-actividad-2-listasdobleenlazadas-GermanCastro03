// ============================================================================
// TramaLoad.cpp - Implementación de Trama de Carga
// ============================================================================

#include "TramaLoad.h"
#include <iostream>

// Constructor
TramaLoad::TramaLoad(char c) : caracter(c) {}

// Procesar trama de carga
void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Obtener el carácter decodificado usando el rotor actual
    char decodificado = rotor->getMapeo(caracter);
    
    // Insertar en la lista de carga
    carga->insertarAlFinal(decodificado);
    
    // Mostrar información de debug
    std::cout << "Trama [L," << caracter << "] -> Fragmento '" 
              << caracter << "' decodificado como '" << decodificado 
              << "'. Mensaje: ";
    carga->imprimirParcial();
    std::cout << std::endl;
}
