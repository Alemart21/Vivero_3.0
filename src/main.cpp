#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>

// Variables Utilizadas para la lectura desde firebase
int temperaturaCargada, humedadCargada, luzCargada, humedadSueloCargada;
// Variables utilizada para guardar info de sensores
int temperatura, humedad, luz, humedadSuelo;

// Reemplaza con tu SSID y Password
const char* ssid = "WAB 2.4";
const char* password = "ESCRIBILADOSVECES";

// Credenciales de Firebase
#define FIREBASE_HOST "https://invernadero-3-0-default-rtdb.firebaseio.com/"  // Reemplaza con tu URL de Firebase
#define FIREBASE_AUTH "gPtE4XXcsC6OT92hdQ9pw69Vdd00TKqyuY8PPaVd"   // Reemplaza con tu token

// Declaraciones de void
void leerYGuardarValor(String rutaFirebase, int &variableDestino);
void cargarValorAFirebase(String rutaFirebase, int valor);

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
  temperatura=35;
  humedad=100;
  luz=49250;
  humedadSuelo=100;

  leerYGuardarValor("/Sensores/valoresCargados/temperaturaCargada", temperaturaCargada);
  leerYGuardarValor("/Sensores/valoresCargados/humedadCargada", humedadCargada);
  leerYGuardarValor("/Sensores/valoresCargados/luzCargada", luzCargada);
  leerYGuardarValor("/Sensores/valoresCargados/humedadSueloCargada", humedadSueloCargada);
  cargarValorAFirebase("/Sensores/temperaturaActual", temperatura);
  cargarValorAFirebase("/Sensores/humedadActual", humedad);
  cargarValorAFirebase("/Sensores/luxActual", luz);
  cargarValorAFirebase("/Sensores/humedadSueloActual", humedadSuelo);

  delay(5000); // Lee el valor cada 10 segundos
}

// Funcion para leer y guardar valores en esp32
void leerYGuardarValor(String rutaFirebase, int &variableDestino) {
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
        Serial.print("Número leído: ");
        Serial.println(variableDestino);
      } else {
        Serial.println("No se encontraron números en el valor leído.");
      }
    } else {
      Serial.println("Error al leer valor de Firebase");
      Serial.println(firebaseData.errorReason());  // Imprime el error si no se pudo leer desde Firebase
    }
  }
  delay(100);
}

// Función para cargar valores a Firebase
void cargarValorAFirebase(String rutaFirebase, int valor) {
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