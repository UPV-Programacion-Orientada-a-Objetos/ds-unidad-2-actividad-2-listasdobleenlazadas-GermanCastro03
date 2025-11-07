// ============================================================================
// ListaDeCarga.h - Lista Doblemente Enlazada para Almacenar Datos Decodificados
// ============================================================================

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada que almacena los caracteres decodificados
 * 
 * Estructura de datos lineal que mantiene el orden de llegada de los
 * fragmentos de datos procesados. Permite recorrido hacia adelante y atrás.
 */
class ListaDeCarga {
private:
    /**
     * @struct NodoCarga
     * @brief Nodo de la lista doble que almacena un carácter decodificado
     */
    struct NodoCarga {
        char dato;              ///< Carácter almacenado (decodificado)
        NodoCarga* siguiente;   ///< Puntero al siguiente nodo
        NodoCarga* previo;      ///< Puntero al nodo anterior
        
        /**
         * @brief Constructor del nodo
         * @param c Carácter a almacenar
         */
        NodoCarga(char c);
    };
    
    NodoCarga* cabeza;  ///< Puntero al primer nodo de la lista
    NodoCarga* cola;    ///< Puntero al último nodo de la lista

public:
    /**
     * @brief Constructor - Inicializa la lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor - Libera toda la memoria de los nodos
     * 
     * Recorre la lista desde la cabeza eliminando cada nodo
     * secuencialmente para evitar memory leaks.
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     * 
     * Mantiene el orden de llegada de los datos (FIFO para inserción).
     * Actualiza los punteros cabeza/cola según sea necesario.
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo ensamblado
     * 
     * Recorre la lista desde la cabeza e imprime todos los caracteres
     * en secuencia, revelando el mensaje oculto decodificado.
     */
    void imprimirMensaje();
    
    /**
     * @brief Imprime el estado parcial del mensaje (debug)
     * 
     * Muestra los caracteres acumulados hasta el momento en formato
     * [X][Y][Z] para visualizar el progreso de la decodificación.
     */
    void imprimirParcial();
};

#endif // LISTA_DE_CARGA_H
