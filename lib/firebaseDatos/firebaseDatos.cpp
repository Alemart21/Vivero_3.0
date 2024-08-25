#include "firebaseDatos.h"

firebaseDatos::firebaseDatos(const char* host, const char* auth) 
    : _FIREBASE_HOST(host), _FIREBASE_AUTH(auth) {
}

void firebaseDatos::begin() {
    Firebase.begin(_FIREBASE_HOST, _FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
}

void firebaseDatos::leerValor(String rutaFirebase, int &variableDestino) {
    if (Firebase.ready()) {
        if (Firebase.getString(firebaseData, rutaFirebase)) {
            String valor = firebaseData.stringData();     // Carga en valor lo que lee desde Firebase
            String numero = "";
            
            // Extraer solo los números del string
            for (int i = 0; i < valor.length(); i++) {
                if (isDigit(valor[i])) {                    // Verifica si el carácter es un dígito
                    numero += valor[i];
                }
            }

            if (numero.length() > 0) {                    // Verifica si se encontraron números
                variableDestino = numero.toInt();           // Convertir a número entero y guardar en la variable pasada por referencia
            } else {
                Serial.println("No se encontraron números en el valor leído.");
            }
        } else {
            Serial.println("Error al leer valor de Firebase");
            Serial.println(firebaseData.errorReason());  // Imprime el error si no se pudo leer desde Firebase
        }
    }
}

void firebaseDatos::cargarValorInt(String rutaFirebase, int valor) {
    if (Firebase.ready()) {
        if (Firebase.setInt(firebaseData, rutaFirebase, valor)) {
            Serial.print("Valor ");
            Serial.print(valor);
            Serial.print(" guardado en ");
            Serial.println(rutaFirebase);
        } else {
            Serial.print("Error al guardar valor en ");
            Serial.println(rutaFirebase);
            Serial.println(firebaseData.errorReason());
        }
    }
}

void firebaseDatos::cargarValorFloat(String rutaFirebase, float valor) {
    if (Firebase.ready()) {
        if (Firebase.setFloat(firebaseData, rutaFirebase, valor)) {
            Serial.print("Valor ");
            Serial.print(valor);
            Serial.print(" guardado en ");
            Serial.println(rutaFirebase);
        } else {
            Serial.print("Error al guardar valor en ");
            Serial.println(rutaFirebase);
            Serial.println(firebaseData.errorReason());
        }
    }
}
