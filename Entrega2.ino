#include <ArduinoJson.h>  // https://arduinojson.org/
#include <PubSubClient.h> // https://github.com/knolleary/pubsubclient
#include <WiFi.h>
#include <Wire.h>
#include "DHT.h" // Include DHT library

#define DHT_PIN 22     // Defines pin number to which the sensor is connected
#define DHT_TYPE DHT22 // Defines the sensor type. It can be DHT11 or DHT22
#define ECHO_PIN 12 // Analog input that receives the echo signal
#define TRIG_PIN 13 // Digital output that sends the trigger signal

DHT dhtSensor(DHT_PIN, DHT_TYPE); // Defines the sensor dht

// Replace the next variables with your Wi-Fi SSID/Password
const char *WIFI_SSID = "xxxxx";
const char *WIFI_PASSWORD = "xxxxxxx";
char macAddress[18];

// Add MQTT Broker settings
const char *MQTT_BROKER_IP = "iiot-upc.gleeze.com";
const int MQTT_PORT = 1883;
const char *MQTT_USER = "iiot-upc";
const char *MQTT_PASSWORD = "xxxxx";
const bool RETAINED = true;

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.println("\nBooting device...");

  mqttClient.setServer(MQTT_BROKER_IP, MQTT_PORT); // Connect the configured mqtt broker

  connectToWiFiNetwork(); // Connects to the configured network
  connectToMqttBroker();  // Connects to the configured mqtt broker

  dhtSensor.begin(); // Starts sensor communication

  pinMode(ECHO_PIN, INPUT);  // Sets the ECHO_PIN as an Input
  pinMode(TRIG_PIN, OUTPUT); // Sets the TRIG_PIN as an Output
}

void loop() {
  checkConnections(); // We check the connection every time

  // Publish every 10 seconds
  static int nowTime = millis();
  static int startTime = 0;
  static int elapsedTime = 0;
  nowTime = millis();
  elapsedTime = nowTime - startTime;
  if (elapsedTime >= 10000) {
    publishAmbient1();  
    publishAmbient2();
    publishAmbientOficina1();
    publishAmbientOficina2();
    publishAmbientOficina3();
    publishAmbientOficina4();
    publishTankState();
    startTime = nowTime;
  }
}

/* Publicar dades ambient 1 granja*/
void publishAmbient1() {
  static const String topicStr = createTopic("MA_Ambient1");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Ambient1"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

/* Publicar dades ambient 2 granja*/
void publishAmbient2() {
  static const String topicStr = createTopic("MA_Ambient2");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Ambient2"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

/* Publicar dades Tank granja*/
void publishTankState() {
  static const String topicStr = createTopic("MA_Tank");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Tank"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["Level"] = String(getdistance());

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}


/* Publicar dades ambient Oficina 1*/
void publishAmbientOficina1() {
  static const String topicStr = createTopic("Oficina1");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Oficina1"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

/* Publicar dades ambient Oficina 2*/
void publishAmbientOficina2() {
  static const String topicStr = createTopic("Oficina2");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Oficina2"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

/* Publicar dades ambient Oficina 3*/
void publishAmbientOficina3() {
  static const String topicStr = createTopic("Oficina3");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Oficina3"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

/* Publicar dades ambient Oficina 4*/
void publishAmbientOficina4() {
  static const String topicStr = createTopic("Oficina4");
  static const char *topic = topicStr.c_str();

  StaticJsonDocument<128> doc; // Create JSON document of 128 bytes
  char buffer[128]; // Create the buffer where we will print the JSON document
                    // to publish through MQTT

  JsonObject MasAlmar = doc.createNestedObject("Oficina4"); // We can add another Object
  MasAlmar["temp"] = getTemperature();
  MasAlmar["humi"] = getHumidity();

  // Serialize the JSON document to a buffer in order to publish it
  serializeJson(doc, buffer);
  mqttClient.publish(topic, buffer, RETAINED);
  Serial.println(" <= " + String(topic) + ": " + String(buffer));
}

String getTemperature(){
  static float temperature;
  
  temperature = dhtSensor.readTemperature(); // Reads the temperature, it takes
                                             // about 250 milliseconds
                                       
  Serial.println("Temperature: " + String(temperature) + "°C"); // Prints in a new line the result

  return String(temperature);
}

String getHumidity(){
  static float humidity;
  
  humidity = dhtSensor.readHumidity(); // Reads the humidity, it takes about 250
                                       // milliseconds
                                       
  Serial.println("Humidity: " + String(humidity) +" %"); // Prints in a new line the result

  return String(humidity);
}

float getdistance(){

  digitalWrite(TRIG_PIN, LOW); // Clear the TRIG_PIN by setting it LOW
  delayMicroseconds(5);

  // Trigger the sensor by setting the TRIG_PIN to HIGH for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH); // pulseIn() returns the duration (length of the pulse) in microseconds

  return duration * 0.034 / 2; // Returns the distance in cm
}

String createTopic(char *topic) {
  String topicStr =  String(macAddress) + "/" + topic;
  return topicStr;
}

void connectToWiFiNetwork() {
  Serial.print(
      "Connecting with Wi-Fi: " +
      String(WIFI_SSID)); // Print the network which you want to connect
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".."); // Connecting effect
  }
  Serial.print("..connected!  (ip: "); // After being connected to a network,
                                       // our ESP32 should have a IP
  Serial.print(WiFi.localIP());
  Serial.println(")");
  String macAddressStr = WiFi.macAddress().c_str();
  strcpy(macAddress, macAddressStr.c_str());
}

void connectToMqttBroker() {
  Serial.print(
      "Connecting with MQTT Broker:" +
      String(MQTT_BROKER_IP));    // Print the broker which you want to connect
  mqttClient.connect(macAddress, MQTT_USER, MQTT_PASSWORD);// Using unique mac address from ESP32
  while (!mqttClient.connected()) {
    delay(500);
    Serial.print("..");             // Connecting effect
    mqttClient.connect(macAddress); // Using unique mac address from ESP32
  }
  Serial.println("..connected! (ClientID: " + String(macAddress) + ")");
}

void checkConnections() {
  if (mqttClient.connected()) {
    mqttClient.loop();
  } else { // Try to reconnect
    Serial.println("Connection has been lost with MQTT Broker");
    if (WiFi.status() != WL_CONNECTED) { // Check wifi connection
      Serial.println("Connection has been lost with Wi-Fi");
      connectToWiFiNetwork(); // Reconnect Wifi
    }
    connectToMqttBroker(); // Reconnect Server MQTT Broker
  }
}
