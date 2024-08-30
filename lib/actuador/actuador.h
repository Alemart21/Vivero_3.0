#ifndef ACTUADOR_H
#define ACTUADOR_H

#include <Arduino.h>

class Actuador {
public:
    Actuador(int _pin, String _nombre);

    void encender();
    void apagar();
    void controlar(bool _estado);

private:
    int _pin;
    String _nombre;

};

#endif
