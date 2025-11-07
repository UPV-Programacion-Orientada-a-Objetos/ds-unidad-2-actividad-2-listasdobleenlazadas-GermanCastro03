// ============================================================================
// TramaMap.cpp - Implementación de Trama de Mapeo
// ============================================================================

#include "TramaMap.h"
#include <iostream>

// Constructor
TramaMap::TramaMap(int n) : rotacion(n) {}

// Procesar trama de mapeo
void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    // Rotar el rotor
    rotor->rotar(rotacion);
    
    // Mostrar información de debug
    std::cout << "Trama [M," << rotacion << "] -> ROTANDO ROTOR " 
              << (rotacion >= 0 ? "+" : "") << rotacion << std::endl;
}
