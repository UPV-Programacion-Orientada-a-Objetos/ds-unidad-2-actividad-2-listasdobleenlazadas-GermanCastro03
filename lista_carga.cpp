// ============================================================================
// ListaDeCarga.cpp - Implementación de Lista Doblemente Enlazada
// ============================================================================

#include "ListaDeCarga.h"
#include <iostream>

// Constructor del nodo
ListaDeCarga::NodoCarga::NodoCarga(char c) 
    : dato(c), siguiente(nullptr), previo(nullptr) {}

// Constructor de ListaDeCarga
ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr) {}

// Destructor
ListaDeCarga::~ListaDeCarga() {
    NodoCarga* actual = cabeza;
    while(actual) {
        NodoCarga* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

// Insertar al final
void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if(!cabeza) {
        // Primera inserción
        cabeza = cola = nuevo;
    } else {
        // Insertar al final
        cola->siguiente = nuevo;
        nuevo->previo = cola;
        cola = nuevo;
    }
}

// Imprimir mensaje completo
void ListaDeCarga::imprimirMensaje() {
    std::cout << "\n---\nMENSAJE OCULTO ENSAMBLADO:\n";
    
    NodoCarga* actual = cabeza;
    while(actual) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    
    std::cout << "\n---\n";
}

// Imprimir estado parcial (debug)
void ListaDeCarga::imprimirParcial() {
    NodoCarga* actual = cabeza;
    while(actual) {
        std::cout << "[" << actual->dato << "]";
        actual = actual->siguiente;
    }
}
