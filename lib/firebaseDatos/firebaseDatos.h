#ifndef FIREBASEMANAGER_H
#define FIREBASEMANAGER_H

#include <FirebaseESP32.h>

// Clase FirebaseManager
class firebaseDatos {
public:
    firebaseDatos(const char* host, const char* auth);
    void begin();
    void leerValor(String rutaFirebase, int &variableDestino);
    void cargarValorInt(String rutaFirebase, int valor);
    void cargarValorFloat(String rutaFirebase, float valor);

private:
    FirebaseData firebaseData;
    const char* _FIREBASE_HOST;
    const char* _FIREBASE_AUTH;
};

#endif // FIREBASEMANAGER_H
