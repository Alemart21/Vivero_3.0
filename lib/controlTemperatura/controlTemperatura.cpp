#include <Arduino.h>
#include "controlTemperatura.h"

controlTemperatura::controlTemperatura(float temperaturaActual, int temperaturaSeteada, bool estadoForzador, bool estadoCalefaccion)
{
    _temperaturaActual=temperaturaActual;
    _temperaturaSeteada=temperaturaSeteada;
    _estadoForzador=estadoForzador;
    _estadoCalefaccion=estadoCalefaccion;

    
}

