#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Reemplaza con tu SSID y Password
const char* ssid = "WAB 2.4";
const char* password = "ESCRIBILADOSVECES";

// Credenciales de Firebase
#define FIREBASE_HOST "https://invernadero-3-0-default-rtdb.firebaseio.com/"  // Reemplaza con tu URL de Firebase
#define FIREBASE_AUTH "gPtE4XXcsC6OT92hdQ9pw69Vdd00TKqyuY8PPaVd"   // Reemplaza con tu token

// Instancia de Firebase
FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conexión a la red Wi-Fi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

    // Conectar a Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Prueba de escritura de datos en Firebase
  if (Firebase.setInt(firebaseData, "/prueba/Numero", 3446351496)) {
    Firebase.setString(firebaseData, "/prueba/Nombre", "Alejandro");
    Serial.println("Datos escritos correctamente!");
  } else {
    Serial.println("Error en la escritura de datos:");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  //hola
  // Aquí puedes agregar tu código principal
}
