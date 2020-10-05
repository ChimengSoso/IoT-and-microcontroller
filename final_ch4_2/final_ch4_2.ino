#include <ESP8266WiFi.h>
#include "DHT.h"

// Wi-Fi network SSID and password
const char* ssid = "IoT Lab";
const char* password = "csiot335";

// meng741258_001@gmail.com
// 112233445566

// Host
const char* host = "dweet.io";

#define DHTPIN 2 // what digital pin DHT22 is connected to
#define DHTTYPE DHT22 // DHT 11 sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Serial
  Serial.begin(115200); // initialize serial interface
  dht.begin(); // initialize DHT22 sensor
  delay(10);
  
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  // Read sensor inputs
  // get humidity reading
  float h = dht.readHumidity();
  // get tempeature reading in Celsius
  float t = dht.readTemperature();
  // Check if any reads failed an exit early (to try again).
  while (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(200); // delay before next measurements
    // get the measurement once more
    h = dht.readHumidity();
    t = dht.readTemperature();
  }
  // We now create a URI for the request
  String url = "/get/latest/dweet/for/chinode";

  // Send request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
     "Host: " + host + "\r\n" +
     "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read all the lines from the answer
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  // close connecting 
  Serial.println();
  Serial.println("closing connection");
}
