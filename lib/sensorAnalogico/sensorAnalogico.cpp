#include "sensorAnalogico.h"

// Constructor
SensorAnalogico::SensorAnalogico(int pin, int minLeido, int maxLeido, int minMapeado, int maxMapeado){
    _pin = pin;
    _minLeido = minLeido;
    _maxLeido = maxLeido;
    _minMapeado = minMapeado;
    _maxMapeado = maxMapeado;
  }
// Metodo para leer el valor analógico y mapearlo
void SensorAnalogico::leer() {
  _valorLeido = analogRead(_pin);
  _valorMapeado = map(_valorLeido, _minLeido, _maxLeido, _minMapeado, _maxMapeado);
  if (_valorMapeado < _minMapeado) _valorMapeado = _minMapeado;
  if (_valorMapeado > _maxMapeado) _valorMapeado = _maxMapeado;
}

// Método para obtener el valor leído
int SensorAnalogico::getValorLeido() {
  return _valorLeido;
}

// Método para obtener el valor mapeado
int SensorAnalogico::getValorMapeado() {
  return _valorMapeado;
}
