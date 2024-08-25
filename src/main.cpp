#include <Arduino.h>
#include <WiFi.h>
#include "sensorDHT11.h"
#include "firebaseDatos.h"
// Variables Utilizadas para la lectura desde firebase
int temperaturaCargada, humedadCargada, luzCargada, humedadSueloCargada;
// Variables utilizada para guardar info de sensores
int analogValue = 0, humedadSuelo = 0, luz = 0;
float temperatura = 0, humedad = 0; 
// Definicion de pines
sensorDHT sensorDHT(4); // Entrada DHT11 pin 4
#define pinLuz 34  // Entrada luz pin 34
#define salidaCalefactor 12
#define salidaVentilacion 13
#define salidaLuz 14
#define salidaRiego 15
#define salidaHumidificador 2
// WIFI SSID y Password
const char* ssid = "WAB 2.4";
const char* password = "ESCRIBILADOSVECES";
// Credenciales de Firebase
#define FIREBASE_HOST "https://invernadero-3-0-default-rtdb.firebaseio.com/"  // URL Firebase
#define FIREBASE_AUTH "gPtE4XXcsC6OT92hdQ9pw69Vdd00TKqyuY8PPaVd"   // Token Firebase
// Instancia de FirebaseManager
firebaseDatos firebaseDatos(FIREBASE_HOST, FIREBASE_AUTH);

void setup() {
  Serial.begin(115200);
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
  Serial.println(WiFi.localIP());

  pinMode(salidaCalefactor, OUTPUT);
  pinMode(salidaLuz, OUTPUT);
  pinMode(salidaRiego, OUTPUT);
  pinMode(salidaVentilacion, OUTPUT);
  pinMode(salidaHumidificador, OUTPUT);
  
  digitalWrite(salidaCalefactor, LOW);
  digitalWrite(salidaLuz, LOW);
  digitalWrite(salidaRiego, LOW);
  digitalWrite(salidaVentilacion, LOW);
  digitalWrite(salidaHumidificador, LOW);
  }

void loop() {
  humedadSuelo=100;
  sensorDHT.leerValores();
  analogValue = analogRead(pinLuz);
  luz = map(analogValue, 0, 4095, 0, 30000);
  temperatura = sensorDHT.getTemperatura();
  temperatura = round(temperatura);
  humedad = sensorDHT.getHumedad();

  firebaseDatos.leerValor("/Sensores/valoresCargados/temperaturaCargada", temperaturaCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/humedadCargada", humedadCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/luzCargada", luzCargada);
  firebaseDatos.leerValor("/Sensores/valoresCargados/humedadSueloCargada", humedadSueloCargada);
// Control de temperatura
  if (temperaturaCargada<temperatura){
    digitalWrite(salidaCalefactor, LOW);
    digitalWrite(salidaVentilacion, HIGH);
  }
  else{
    digitalWrite(salidaVentilacion, LOW);
    digitalWrite(salidaCalefactor, HIGH);
  }
// Control de humedad
  if(humedadCargada<humedad){
    digitalWrite(salidaHumidificador, HIGH);
  }
  else{
    digitalWrite(salidaHumidificador, LOW);
  }
// Control humedad suelo
  if(humedadSueloCargada<humedadSuelo){
    digitalWrite(salidaRiego, HIGH);
  }
  else{
    digitalWrite(salidaRiego, LOW);
  }
// Control luz
  if (luzCargada>luz){
    digitalWrite(salidaLuz, HIGH);
  }
  else{
    digitalWrite(salidaLuz, LOW);
  }
  firebaseDatos.cargarValorFloat("/Sensores/temperaturaActual", temperatura);
  firebaseDatos.cargarValorFloat("/Sensores/humedadActual", humedad);
  firebaseDatos.cargarValorInt("/Sensores/luxActual", luz);
  firebaseDatos.cargarValorInt("/Sensores/humedadSueloActual", humedadSuelo);
}