// ============================================================================
// SerialPort.cpp - Implementación de Comunicación Serial
// ============================================================================

#include "SerialPort.h"
#include <iostream>

// Constructor
SerialPort::SerialPort(const char* nombrePuerto) : conectado(false) {
#ifdef _WIN32
    // ===== WINDOWS: API Win32 =====
    puerto = CreateFileA(nombrePuerto,
                        GENERIC_READ | GENERIC_WRITE,
                        0, nullptr, OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL, nullptr);
    
    if(puerto == INVALID_HANDLE_VALUE) {
        std::cerr << "Error al abrir puerto " << nombrePuerto << std::endl;
        return;
    }
    
    // Configurar parámetros del puerto
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    
    if(!GetCommState(puerto, &dcb)) {
        CloseHandle(puerto);
        return;
    }
    
    dcb.BaudRate = CBR_9600;      // 9600 baudios
    dcb.ByteSize = 8;              // 8 bits de datos
    dcb.StopBits = ONESTOPBIT;     // 1 bit de parada
    dcb.Parity = NOPARITY;         // Sin paridad
    
    if(!SetCommState(puerto, &dcb)) {
        CloseHandle(puerto);
        return;
    }
    
    // Configurar timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    
    SetCommTimeouts(puerto, &timeouts);
    
#else
    // ===== LINUX: API POSIX =====
    puerto = open(nombrePuerto, O_RDWR | O_NOCTTY | O_SYNC);
    
    if(puerto < 0) {
        std::cerr << "Error al abrir puerto " << nombrePuerto << std::endl;
        return;
    }
    
    // Configurar parámetros del puerto
    struct termios tty;
    if(tcgetattr(puerto, &tty) != 0) {
        close(puerto);
        return;
    }
    
    // Configurar velocidad (9600 baudios)
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    
    // Configurar modo de datos: 8N1
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8 bits
    tty.c_iflag &= ~IGNBRK;                      // Sin ignorar break
    tty.c_lflag = 0;                              // Sin modo canónico
    tty.c_oflag = 0;                              // Sin procesamiento de salida
    tty.c_cc[VMIN] = 0;                          // Lectura no bloqueante
    tty.c_cc[VTIME] = 5;                         // Timeout 0.5 segundos
    
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);     // Sin control de flujo
    tty.c_cflag |= (CLOCAL | CREAD);             // Ignorar modem, habilitar lectura
    tty.c_cflag &= ~(PARENB | PARODD);           // Sin paridad
    tty.c_cflag &= ~CSTOPB;                      // 1 bit de parada
    
    tcsetattr(puerto, TCSANOW, &tty);
#endif
    
    conectado = true;
    std::cout << "Conexión establecida. Esperando tramas...\n" << std::endl;
}

// Destructor
SerialPort::~SerialPort() {
    if(conectado) {
#ifdef _WIN32
        CloseHandle(puerto);
#else
        close(puerto);
#endif
    }
}

// Leer línea desde el puerto
bool SerialPort::leerLinea(char* buffer, int maxLen) {
    if(!conectado) return false;
    
    int pos = 0;
    
#ifdef _WIN32
    // ===== WINDOWS =====
    DWORD leidos;
    char c;
    
    while(pos < maxLen - 1) {
        if(!ReadFile(puerto, &c, 1, &leidos, nullptr) || leidos == 0) {
            if(pos > 0) break;  // Tenemos datos parciales
            return false;        // No hay datos
        }
        
        // Filtrar caracteres de nueva línea
        if(c == '\n' || c == '\r') {
            if(pos > 0) break;  // Fin de línea
            continue;            // Ignorar si está vacío
        }
        
        buffer[pos++] = c;
    }
    
#else
    // ===== LINUX =====
    char c;
    
    while(pos < maxLen - 1) {
        int n = read(puerto, &c, 1);
        
        if(n <= 0) {
            if(pos > 0) break;  // Tenemos datos parciales
            return false;        // No hay datos
        }
        
        // Filtrar caracteres de nueva línea
        if(c == '\n' || c == '\r') {
            if(pos > 0) break;  // Fin de línea
            continue;            // Ignorar si está vacío
        }
        
        buffer[pos++] = c;
    }
#endif
    
    buffer[pos] = '\0';
    return pos > 0;
}

// Verificar estado de conexión
bool SerialPort::estaConectado() const {
    return conectado;
}
