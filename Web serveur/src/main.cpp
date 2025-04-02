#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const int oneWireBus = 4;  // Pin pour le bus OneWire (capteur Dallas)

OneWire oneWire(oneWireBus);  // Création de l'objet OneWire
DallasTemperature sensors(&oneWire);  // Création de l'objet DallasTemperature

AsyncWebServer server(80);  // Création du serveur web sur le port 80

const int BLUE_LED = 18;  // Pin pour la LED bleue
const int RED_LED = 5;    // Pin pour la LED rouge
const char* ssid = "iPhone de Othmane";  // Nom du réseau WiFi
const char* password = "othmane59";      // Mot de passe du réseau WiFi

unsigned long  previousMillis = 0; // Store the last time the LED was updated
const long interval = 500; // Interval at which to blink (milliseconds)

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>ESP32 Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin: 0px auto; padding-top: 30px;}
    .sensor-data {
      font-size: 24px;
      margin: 20px;
      padding: 10px;
      background-color: #f0f0f0;
      border-radius: 5px;
    }
  </style>
  <script>
    // Fonction pour mettre à jour la température toutes les 2 secondes
    function updateData() {
      fetch('/temperature')
        .then(response => response.text())
        .then(data => document.getElementById('temperature').innerHTML = data + ' °C');
      
      setTimeout(updateData, 1000);
    }
    window.onload = updateData;
  </script>
</head>
<body>
  <h1>ESP32 Web Server</h1>
  <div class="sensor-data">
    <p>Température: <span id="temperature">--</span></p>
  </div>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  sensors.begin();  // Initialisation du capteur

  // Configuration des pins LED en sortie
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Éteindre les LEDs au démarrage
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
 

  // Configuration des routes du serveur web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);  // Envoi de la page HTML
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    sensors.requestTemperatures();  // Demande une nouvelle lecture de température
    String temperature = String(sensors.getTempCByIndex(0));  // Récupère la température
    request->send(200, "text/plain", temperature);  // Envoi de la température
  });

  // Démarrage du serveur web
  server.begin();
}

void loop() {

  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // put your main code here, to run repeatedly:
    sensors.requestTemperatures(); // Send the command to get temperatures
    float temperatureC = sensors.getTempCByIndex(0); // Get the temperature in Celsius

    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(temperatureC);

    if (27.5 < temperatureC && temperatureC < 28.5 ) {
      digitalWrite(BLUE_LED, HIGH); // Turn the LED on (HIGH is the voltage level)
    } 
    else if (temperatureC > 28.5) {
      digitalWrite(RED_LED, HIGH); // Turn the LED off (LOW is the voltage level)
    }
    else {
      digitalWrite(BLUE_LED, LOW); // Turn the LED off (LOW is the voltage level)
      digitalWrite(RED_LED, LOW); // Turn the LED off (LOW is the voltage level)
    }
  }
}