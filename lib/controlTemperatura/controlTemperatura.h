#ifndef controlTemperatura_h
#define controlTemperatura_h

#include <Arduino.h>

class controlTemperatura
{
    public:
        controlTemperatura(float temperaturaActual, int temperaturaSeteada, bool estadoForzador, bool estadoCalefaccion);

    private:
        float _temperaturaActual;
        int _temperaturaSeteada;
        bool _estadoForzador, _estadoCalefaccion;
};


#endif