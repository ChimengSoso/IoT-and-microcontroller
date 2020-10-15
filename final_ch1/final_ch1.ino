// Libraries
#include <ESP8266WiFi.h>
// Wifi network
const char* ssid ="IoT Lab";
const char* password = "csiot335";

// host 
const char* host = "dweet.io";

void setup() {
  // Start serial
  Serial.begin(115200);
  delay(10);
  
  // Connecting to a WiFi network
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
  delay(5000);
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
  String url = "/dweet/for/flashnode?value=hellomydarknessmyoldfriend&parameter2=whatisup";

  // Send request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout == 0) {
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

  // Close connecting
  Serial.println();
  Serial.println("closing connection");
}
