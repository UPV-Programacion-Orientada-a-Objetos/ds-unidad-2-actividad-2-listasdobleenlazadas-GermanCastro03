// ============================================================================
// TramaBase.h - Clase Base Abstracta para Tramas PRT-7
// ============================================================================

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * 
 * Define la interfaz común que deben implementar todas las tramas
 * (TramaLoad y TramaMap). El uso de polimorfismo permite procesar
 * cualquier tipo de trama a través de un puntero a la clase base.
 */
class TramaBase {
public:
    /**
     * @brief Procesa la trama aplicando su lógica específica
     * @param carga Puntero a la lista donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo para transformaciones César
     * 
     * Método virtual puro que obliga a las clases derivadas a implementar
     * su propia lógica de procesamiento.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
    
    /**
     * @brief Destructor virtual para limpieza polimórfica correcta
     * 
     * CRÍTICO: Debe ser virtual para evitar memory leaks cuando se hace
     * delete sobre un puntero TramaBase* que apunta a objetos derivados.
     */
    virtual ~TramaBase() {}
};

#endif // TRAMA_BASE_H
