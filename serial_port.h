// ============================================================================
// SerialPort.h - Comunicación Serial Multiplataforma
// ============================================================================

#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <termios.h>
#endif

/**
 * @class SerialPort
 * @brief Clase para comunicación serial multiplataforma (Windows/Linux)
 * 
 * Encapsula las diferencias entre las APIs de comunicación serial de
 * Windows (Win32) y Linux (POSIX termios), proporcionando una interfaz
 * unificada para leer datos desde el Arduino.
 */
class SerialPort {
private:
#ifdef _WIN32
    HANDLE puerto;      ///< Handle del puerto COM en Windows
#else
    int puerto;         ///< File descriptor del puerto en Linux
#endif
    bool conectado;     ///< Estado de la conexión
    
public:
    /**
     * @brief Constructor - Abre y configura el puerto serial
     * @param nombrePuerto Nombre del puerto (ej: "COM3" o "/dev/ttyUSB0")
     * 
     * Configura el puerto con los siguientes parámetros:
     * - Baud Rate: 9600
     * - Data Bits: 8
     * - Stop Bits: 1
     * - Parity: None
     * - Timeouts apropiados para lectura no bloqueante
     */
    SerialPort(const char* nombrePuerto);
    
    /**
     * @brief Destructor - Cierra el puerto serial
     * 
     * Libera los recursos del sistema operativo asociados al puerto.
     */
    ~SerialPort();
    
    /**
     * @brief Lee una línea completa desde el puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param maxLen Tamaño máximo del buffer
     * @return true si se leyó una línea completa, false en caso contrario
     * 
     * Lee caracteres hasta encontrar '\n' o '\r', o hasta llenar el buffer.
     * Filtra caracteres de control y retorna solo líneas válidas.
     */
    bool leerLinea(char* buffer, int maxLen);
    
    /**
     * @brief Verifica si la conexión está activa
     * @return true si el puerto está conectado y listo, false en caso contrario
     */
    bool estaConectado() const;
};

#endif // SERIAL_PORT_H
