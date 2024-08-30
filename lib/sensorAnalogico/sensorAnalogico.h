#ifndef sensorAnalogico_H
#define sensorAnalogico_H

#include <Arduino.h>

class sensorAnalogico {
  public:
    // Constructor
    sensorAnalogico(int pin, int minLeido, int maxLeido, int minMapeado, int maxMapeado);

    // Metodos
    void leer();
    int getValorLeido();
    int getValorMapeado();

  private:
    int _pin;
    int _valorLeido;
    int _valorMapeado;
    int _minLeido;
    int _maxLeido;
    int _minMapeado;
    int _maxMapeado;
};

#endif
