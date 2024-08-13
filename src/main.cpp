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
  if (Firebase.setString(firebaseData, "/prueba", "Hello_Word")) {
    Serial.println("Datos escritos correctamente!");
  } else {
    Serial.println("Error en la escritura de datos:");
    Serial.println(firebaseData.errorReason());
  }
}

void loop() {
  if (Firebase.ready()) { //leo desdde firebase
    if (Firebase.getString(firebaseData, "/Sensores/valoresCargados/temperaturaCargada")) {
      String valor = firebaseData.stringData();     //cargo en valor lo que leo desde firebase
      String numero = "";
      
      // Extraer solo los números del string
      for (int i = 0; i < valor.length(); i++) {    //tengo q ver q hace este for
        if (isDigit(valor[i])) {                    //ver que es isDigit
          numero += valor[i];
        }
      }

      if (numero.length() > 0) {                 // ver que hace este if
        int temperaturaCargada = numero.toInt(); // Convertir a número entero
        Serial.print("Número leído: ");
        Serial.println(temperaturaCargada);
      } else {
        Serial.println("No se encontraron números en el valor leído.");
      }
    } else {
      Serial.println("Error al leer valor de Firebase");
      Serial.println(firebaseData.errorReason());  //imprime el error de xq no leyo firebase
    }
  }
  delay(10000); // Lee el valor cada 10 segundos
}
