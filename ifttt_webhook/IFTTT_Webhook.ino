#include <ESP8266WiFi.h>
#include "DHT.h"

//Set time between each trigger. Currently set to 30 seconds:
#define timeInterval 30000 // time between each trigger
#define DHTPIN D4          // what digital pin we're connected to
#define DHTTYPE DHT22      // DHT 22

DHT dht(DHTPIN, DHTTYPE);

//Set Wi-Fi network credentials:
const char* ssid = "IoT Lab";
const char* password = "csiot335";

//Set IFTTT requirements:
const char* host = "maker.ifttt.com";
const char* privateKey = "Q4oPKAsgM4o-NAxei5c5c";
const char* event = "Hightemperaturenaja";//"HOT_temp";
long lastTime = 0; // holds previous time trigger was sent

// Initialize serial communication and the dht sensor and connect
// ESP8266 module to the Wi-Fi network:

void setup() {
  Serial.begin(115200); // initialize serial communication
  dht.begin(); // initialize DHT11 sensor
  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
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
  // Read sensor inputs
  // get temperature reading in Celsius
  float temperature = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  while (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000); // delay before next measurements
    //get the measurements once more
    temperature = dht.readTemperature();
  }

  if(temperature > 26 && millis()- lastTime > timeInterval){ 
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }
    // We now create a URI for the request
    String url = "/trigger/";
      url += event;
      url += "/with/key/";
      url += privateKey;
      url += "?value1=";
      url += String(temperature);
    Serial.print("Requesting URL: "); 
    Serial.println(url);

    // This will send the request to the server
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
    
    // Read all the lines of the reply from server and print them to Serial
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println();
    Serial.println("closing connection");
    lastTime = millis(); // save time of last trigger
  }
}
