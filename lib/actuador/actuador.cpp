#include "Actuador.h"

Actuador::Actuador(int _pin, String _nombre) : _pin(_pin), _nombre(_nombre) {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);  // Inicializar el actuador en estado apagado
}

void Actuador::controlar(bool _estado) {
    if (_estado) {
        encender();
    } else {
        apagar();
    }
}

void Actuador::encender() {
    digitalWrite(_pin, HIGH);
    Serial.println(_nombre + " encendido");
}

void Actuador::apagar() {
    digitalWrite(_pin, LOW);
    Serial.println(_nombre + " apagado");
}
