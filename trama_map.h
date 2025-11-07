// ============================================================================
// TramaMap.h - Trama de Mapeo (Tipo M)
// ============================================================================

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"

/**
 * @class TramaMap
 * @brief Trama que representa una instrucción de rotación del rotor
 * 
 * Formato del protocolo: M,N
 * Donde N es un entero (positivo o negativo) que indica cuántas
 * posiciones debe rotar el rotor de mapeo.
 * 
 * Ejemplo: "M,2"  -> Rota el rotor +2 posiciones (A→C, B→D, etc.)
 * Ejemplo: "M,-3" -> Rota el rotor -3 posiciones (A→X, B→Y, etc.)
 */
class TramaMap : public TramaBase {
private:
    int rotacion;  ///< Cantidad de posiciones a rotar (+ o -)

public:
    /**
     * @brief Constructor - Crea una trama de mapeo
     * @param n Cantidad de rotaciones a aplicar
     */
    TramaMap(int n);
    
    /**
     * @brief Procesa la trama: rota el rotor de mapeo
     * @param carga Lista de carga (no se modifica en esta operación)
     * @param rotor Rotor que será rotado
     * 
     * Lógica de procesamiento:
     * 1. Aplica la rotación: rotor->rotar(rotacion)
     * 2. Muestra información de debug en consola
     * 
     * Nota: Esta trama NO inserta datos, solo modifica el estado
     * del rotor para afectar futuras tramas TramaLoad.
     */
    void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H
