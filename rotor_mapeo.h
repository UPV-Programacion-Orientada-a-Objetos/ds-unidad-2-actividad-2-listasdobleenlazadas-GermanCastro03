// ============================================================================
// RotorDeMapeo.h - Lista Circular Doblemente Enlazada
// ============================================================================

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que implementa un cifrado César dinámico
 * 
 * Estructura de datos circular que contiene el alfabeto A-Z y permite
 * rotación bidireccional. Funciona como un "disco de cifrado" donde
 * la posición de la cabeza determina el mapeo actual de caracteres.
 */
class RotorDeMapeo {
private:
    /**
     * @struct NodoRotor
     * @brief Nodo de la lista circular que almacena un carácter
     */
    struct NodoRotor {
        char dato;              ///< Carácter almacenado (A-Z)
        NodoRotor* siguiente;   ///< Puntero al siguiente nodo (circular)
        NodoRotor* previo;      ///< Puntero al nodo anterior (circular)
        
        /**
         * @brief Constructor del nodo
         * @param c Carácter a almacenar
         */
        NodoRotor(char c);
    };
    
    NodoRotor* cabeza;  ///< Puntero a la posición "cero" actual del rotor
    int tamanio;        ///< Cantidad de elementos en el rotor (26 para A-Z)
    
    /**
     * @brief Inserta un carácter al final de la lista circular
     * @param c Carácter a insertar
     * 
     * Método privado usado durante la inicialización para construir
     * el alfabeto completo.
     */
    void insertarAlFinal(char c);

public:
    /**
     * @brief Constructor - Inicializa el rotor con el alfabeto A-Z
     * 
     * Crea una lista circular con los 26 caracteres del alfabeto
     * en orden, con la cabeza apuntando a 'A'.
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor - Libera toda la memoria de los nodos
     * 
     * Rompe el círculo y elimina todos los nodos secuencialmente
     * para evitar memory leaks.
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Rota el rotor N posiciones (positivas o negativas)
     * @param n Cantidad de posiciones a rotar
     *          - Positivo: rotación hacia adelante (A→B→C...)
     *          - Negativo: rotación hacia atrás (A→Z→Y...)
     * 
     * No mueve datos, solo cambia el puntero cabeza de forma eficiente.
     * El módulo garantiza que valores grandes de n funcionen correctamente.
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el carácter mapeado según la rotación actual
     * @param in Carácter de entrada a mapear
     * @return Carácter transformado según la posición actual del rotor
     * 
     * Implementa la lógica de cifrado César:
     * - Encuentra la posición del carácter de entrada
     * - Aplica el desplazamiento relativo a la cabeza actual
     * - Retorna el carácter resultante
     * 
     * Caracteres especiales (espacios, no-alfabéticos) se retornan sin cambios.
     */
    char getMapeo(char in);
    
    /**
     * @brief Imprime el estado actual del rotor (debug)
     * 
     * Muestra todos los caracteres en orden circular y señala
     * la posición actual de la cabeza.
     */
    void imprimir();
};

#endif // ROTOR_DE_MAPEO_H
