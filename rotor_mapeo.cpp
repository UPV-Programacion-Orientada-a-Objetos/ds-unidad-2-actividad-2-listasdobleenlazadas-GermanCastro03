// ============================================================================
// RotorDeMapeo.cpp - Implementación de Lista Circular
// ============================================================================

#include "RotorDeMapeo.h"
#include <iostream>

// Constructor del nodo
RotorDeMapeo::NodoRotor::NodoRotor(char c) 
    : dato(c), siguiente(nullptr), previo(nullptr) {}

// Constructor de RotorDeMapeo
RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
    // Inicializar con el alfabeto A-Z
    for(char c = 'A'; c <= 'Z'; c++) {
        insertarAlFinal(c);
    }
}

// Destructor
RotorDeMapeo::~RotorDeMapeo() {
    if(!cabeza) return;
    
    NodoRotor* actual = cabeza;
    NodoRotor* temp;
    
    // Romper el círculo para poder eliminar secuencialmente
    cabeza->previo->siguiente = nullptr;
    
    // Eliminar todos los nodos
    while(actual) {
        temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

// Insertar al final (usado en construcción)
void RotorDeMapeo::insertarAlFinal(char c) {
    NodoRotor* nuevo = new NodoRotor(c);
    
    if(!cabeza) {
        // Primer nodo - apunta a sí mismo
        cabeza = nuevo;
        cabeza->siguiente = cabeza;
        cabeza->previo = cabeza;
    } else {
        // Insertar al final del círculo
        NodoRotor* ultimo = cabeza->previo;
        
        ultimo->siguiente = nuevo;
        nuevo->previo = ultimo;
        nuevo->siguiente = cabeza;
        cabeza->previo = nuevo;
    }
    tamanio++;
}

// Rotar el rotor N posiciones
void RotorDeMapeo::rotar(int n) {
    if(!cabeza || tamanio == 0) return;
    
    // Normalizar rotación (manejar valores mayores al tamaño)
    n = n % tamanio;
    if(n < 0) n += tamanio;  // Convertir negativos a equivalente positivo
    
    // Rotar moviendo la cabeza (eficiente O(n))
    for(int i = 0; i < n; i++) {
        cabeza = cabeza->siguiente;
    }
}

// Obtener mapeo César según rotación actual
char RotorDeMapeo::getMapeo(char in) {
    if(!cabeza) return in;
    
    // Manejar caracteres especiales sin mapeo
    if(in == ' ' || in < 'A' || in > 'Z') {
        return in;
    }
    
    // Encontrar posición del carácter de entrada en el rotor
    NodoRotor* actual = cabeza;
    int posicionEntrada = -1;
    int indice = 0;
    
    do {
        if(actual->dato == in) {
            posicionEntrada = indice;
            break;
        }
        actual = actual->siguiente;
        indice++;
    } while(actual != cabeza);
    
    if(posicionEntrada == -1) return in; // No encontrado
    
    // El mapeo: avanzar desde cabeza la misma cantidad de posiciones
    // Ejemplo: Si 'C' está en posición 2 desde cabeza, retornar
    //          el carácter que está en posición 2 desde cabeza
    actual = cabeza;
    for(int i = 0; i < posicionEntrada; i++) {
        actual = actual->siguiente;
    }
    
    return actual->dato;
}

// Imprimir estado del rotor (debug)
void RotorDeMapeo::imprimir() {
    if(!cabeza) {
        std::cout << "Rotor vacío" << std::endl;
        return;
    }
    
    NodoRotor* actual = cabeza;
    std::cout << "Rotor: [";
    do {
        std::cout << actual->dato;
        actual = actual->siguiente;
        if(actual != cabeza) std::cout << " ";
    } while(actual != cabeza);
    std::cout << "] (Cabeza en '" << cabeza->dato << "')" << std::endl;
}
