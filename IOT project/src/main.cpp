#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "index.cpp"

// Définition des pins
const int oneWireBus = 4;    // Pin pour le bus OneWire (capteur Dallas)
const int BUZZER_PIN = 12;   // GPIO 14 pour le buzzer
const int BLUE_LED = 18;     // Pin pour la LED bleue
const int RED_LED = 5;       // Pin pour la LED rouge

// Paramètres du buzzer
const int FREQ_MIN = 300;    // Fréquence minimale
const int FREQ_MAX = 800;   // Fréquence maximale
const int DELAY_TIME = 15;   // Temps entre chaque changement de fréquence

// Paramètres WiFi
const char* ssid = "iPhone de Othmane";
const char* password = "othmane59";

// Paramètres de timing
unsigned long previousMillis = 0;
const long interval = 500;   // Intervalle de lecture en millisecondes

// Initialisation des objets
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);
AsyncWebServer server(80);

// Fonction pour jouer une alarme sonore
void playAlarm() {
  // Augmentation progressive de la fréquence
  for (int freq = FREQ_MIN; freq <= FREQ_MAX; freq += 5) {
    tone(BUZZER_PIN, freq);
    delay(DELAY_TIME);
  }
  
  // Diminution progressive de la fréquence
  for (int freq = FREQ_MAX; freq >= FREQ_MIN; freq -= 5) {
    tone(BUZZER_PIN, freq);
    delay(DELAY_TIME);
  }
}

void setup() {
  // Initialisation de la communication série
  Serial.begin(115200);
  
  // Initialisation du capteur de température
  sensors.begin();

  // Configuration des pins
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Éteindre les LEDs au démarrage
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);

  // Connexion au réseau WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion au WiFi...");
  }
 
  Serial.println("Connecté au WiFi");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  // Configuration des routes du serveur web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    sensors.requestTemperatures();
    String temperature = String(sensors.getTempCByIndex(0));
    request->send(200, "text/plain", temperature);
  });

  // Démarrage du serveur web
  server.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Lecture de la température
    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);

    // Affichage de la température
    Serial.print("Temperature: ");
    Serial.println(temperatureC);

    // Gestion des LEDs et du buzzer selon la température
    if (temperatureC < 0) {
      // Clignotement de la LED bleue et bip de déconnexion
      digitalWrite(BLUE_LED, !digitalRead(BLUE_LED)); // Inversion de l'état de la LED
      tone(BUZZER_PIN, 1000, 100); // Bip court à 1000Hz pendant 100ms
      digitalWrite(RED_LED, !digitalRead(RED_LED));
    }
    else if (temperatureC < 28.5) {
      digitalWrite(BLUE_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      noTone(BUZZER_PIN);
    } 
    else if (temperatureC > 28.5) {
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      playAlarm();
    }
    else {
      digitalWrite(BLUE_LED, LOW);
      digitalWrite(RED_LED, LOW);
      noTone(BUZZER_PIN);
    }

    Serial.println("========ETAT MEMOIRE==========");
    Serial.printf("Free heap: %d bytes\n", ESP.getFreeHeap());
    Serial.printf("Total heap: %d bytes\n", ESP.getFreePsram());
    Serial.println("================================");
  }
}