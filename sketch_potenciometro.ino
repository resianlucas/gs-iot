#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configurações do broker MQTT
const char* mqtt_server = "test.mosquitto.org";
const char* mqtt_topic_dados = "esp32/dados";
const char* mqtt_topic_potencia = "esp32/potencia";

WiFiClient espClient;
PubSubClient client(espClient);

const int potPin = 36; // Pino analógico do potenciômetro

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("WiFi conectado!");

  client.setServer(mqtt_server, 1883);

  while (!client.connected()) {
    if (client.connect("ESP32_POT")) {
      Serial.println("Conectado ao broker MQTT!");
    } else {
      delay(1000);
      Serial.println("Tentando reconectar ao MQTT...");
    }
  }
}

void loop() {
  if (!client.connected()) {
    client.connect("ESP32_POT");
  }
  client.loop();

  // Lê o valor do potenciômetro
  int potValue = analogRead(potPin);
  float potPercent = map(potValue, 0, 4095, 0, 100); // Mapeia para 0-100%

  // Envia para o tópico esp32/dados
  char messageDados[50];
  snprintf(messageDados, sizeof(messageDados), "{\"potencia\":%.2f}", potPercent);
  client.publish(mqtt_topic_dados, messageDados);

  // Envia para o tópico esp32/potencia
  char messagePotencia[50];
  snprintf(messagePotencia, sizeof(messagePotencia), "{\"rawValue\":%d,\"percentage\":%.2f}", potValue, potPercent);
  client.publish(mqtt_topic_potencia, messagePotencia);

  // Log no Serial Monitor
  Serial.print("Enviado para esp32/dados: ");
  Serial.println(messageDados);
  Serial.print("Enviado para esp32/potencia: ");
  Serial.println(messagePotencia);

  delay(500);
}
