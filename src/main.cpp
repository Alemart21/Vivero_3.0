#include <Arduino.h>
#include <WiFi.h>
#include "sensorDHT11.h"
#include "firebaseDatos.h"
#include "actuador.h"
// Variables Utilizadas para la lectura desde firebase
int temperaturaCargada, humedadCargada, luzCargada, humedadSueloCargada;
// Variables utilizada para guardar info de sensores
int analogValueLuz = 0, analogValueHumedadSuelo = 0, humedadSuelo = 0, luz = 0;
float temperatura = 0, humedad = 0; 
// Definicion de pines
sensorDHT sensorDHT(4); // Entrada DHT11 pin 4
#define pinLuz 35
#define pinHumedadSuelo 34 
Actuador calefactor(12, "Calefactor");
Actuador ventilacion(13, "Ventilación");
Actuador luzActuador(14, "Luz");
Actuador riego(15, "Riego");
Actuador humidificador(2, "Humidificador");

// WIFI SSID y Password
const char* ssid = "WAB 2.4"; //Alumnos2.4GHz
const char* password = "NOLAESCRIBAS"; //alumnosfcyt
// Credenciales de Firebase
#define FIREBASE_HOST "https://invernadero-3-0-default-rtdb.firebaseio.com/"  // URL Firebase
#define FIREBASE_AUTH "gPtE4XXcsC6OT92hdQ9pw69Vdd00TKqyuY8PPaVd"   // Token Firebase
// Instancia de FirebaseManager
firebaseDatos firebaseDatos(FIREBASE_HOST, FIREBASE_AUTH);

void setup() {
  Serial.begin(115200);
  analogReadResolution(10); // Resolucion de 10bits al ADC
  // Conexión a la red Wi-Fi
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  sensorDHT.iniciar();  // Inicializa el sensorDHT11
  firebaseDatos.begin(); // Inicializa firebase

  Serial.println("Dirección IP: ");
  Serial.print(WiFi.localIP());
  }

void loop() {
  sensorDHT.leerValores();
  analogValueLuz = analogRead(pinLuz);
  luz = map(analogValueLuz, 0, 1024, 0, 50000); // Escalo de 0 a 50k
  analogValueHumedadSuelo = analogRead(pinHumedadSuelo);
  humedadSuelo = map(analogValueHumedadSuelo, 915, 385, 0, 100); // Escalo el valor de 0 a 100
  if (humedadSuelo<0){humedadSuelo=0;}
  if (humedadSuelo>100){humedadSuelo=100;}
  temperatura = sensorDHT.getTemperatura();
  temperatura = round(temperatura); // Redondeo el valor de temperatura
  humedad = sensorDHT.getHumedad();

  firebaseDatos.leerValor("/Sensores/valoresCargados/temperaturaCargada", temperaturaCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/humedadCargada", humedadCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/luzCargada", luzCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/humedadSueloCargada", humedadSueloCargada);
    // Control de temperatura
  calefactor.controlar((temperaturaCargada - 2) > temperatura);
  ventilacion.controlar((temperaturaCargada + 2) < temperatura);
    // Control de humedad
  humidificador.controlar((humedadCargada + 2) < humedad);
    // Control de humedad del suelo
  riego.controlar((humedadSueloCargada + 2) < humedadSuelo);
    // Control de luz
  luzActuador.controlar((luzCargada + 2) > luz);
  firebaseDatos.cargarValorFloat("/Sensores/temperaturaActual", temperatura);
  firebaseDatos.cargarValorFloat("/Sensores/humedadActual", humedad);
  firebaseDatos.cargarValorInt("/Sensores/luxActual", luz);
  firebaseDatos.cargarValorInt("/Sensores/humedadSueloActual", humedadSuelo);
}