// ============================================================================
// TramaLoad.h - Trama de Carga (Tipo L)
// ============================================================================

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaLoad
 * @brief Trama que representa una carga de datos (fragmento de mensaje)
 * 
 * Formato del protocolo: L,X
 * Donde X es un carácter que debe ser decodificado usando el rotor actual
 * y luego almacenado en la lista de carga.
 * 
 * Ejemplo: "L,A" -> Carga el carácter 'A' y lo decodifica según rotación actual
 */
class TramaLoad : public TramaBase {
private:
    char caracter;  ///< Carácter a decodificar y cargar

public:
    /**
     * @brief Constructor - Crea una trama de carga
     * @param c Carácter a almacenar en la trama
     */
    TramaLoad(char c);
    
    /**
     * @brief Procesa la trama: decodifica y almacena el carácter
     * @param carga Lista donde se insertará el carácter decodificado
     * @param rotor Rotor que aplicará la transformación César
     * 
     * Lógica de procesamiento:
     * 1. Consulta al rotor el carácter mapeado: decodificado = rotor->getMapeo(caracter)
     * 2. Inserta el resultado en la lista: carga->insertarAlFinal(decodificado)
     * 3. Muestra información de debug en consola
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H
