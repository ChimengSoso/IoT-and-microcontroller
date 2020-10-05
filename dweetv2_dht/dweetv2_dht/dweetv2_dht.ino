// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include <ArduinoJson.h>

const char* ssid = "IoT Lab";
const char* password = "csiot335";

const char* host = "http://www.dweetpro.io/v2/dweets";

#define DHTPIN 2 
#define DHTTYPE DHT22 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Serial
  Serial.begin(115200);
  dht.begin();
  delay(10);

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
  delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Read sensor inputs
  // get humidity reading
  float h = dht.readHumidity();
  // get temperature reading in Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  while (isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
     delay(2000); // delay before next measurements
     //get the measurements once more
     h = dht.readHumidity();
     t = dht.readTemperature();
  }

  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(host);

      String str_h = String(h);
      String str_t = String(t);

      Serial.print("Humidity = ");
      Serial.println(str_h);
      Serial.print("Temperature = ");
      Serial.println(str_t);

      // If you need an HTTP request with a content type: application/json, use the following:
      http.addHeader("Content-Type", "application/json");
      http.addHeader("X-DWEET-AUTH", "eyJ1c2VybmFtZSI6IndvcmFrdW5fYUBlbGVhcm5pbmcuY211LmFjLnRoIiwicGhvbmUiOiIwNjEwNjg4MDY0IiwiZmlyc3ROYW1lIjoiV29yYWt1biIsImxhc3ROYW1lIjoiQXRhIiwicm9sZSI6ImFkbWluIiwibGFzdExvZ2luIjpudWxsLCJhY2NvdW50IjpbeyJuYW1lIjoiQ0hJX0lOQyIsInJvbGUiOiJhZG1pbiJ9XSwiY29tcGFueSI6IkNISV9JTkMiLCJ2YWxpZGl0eSI6MTYwMDkyNjUxMzc2MX0=.0e2643af2e5751e6614c0b17b4ca97070aa7fd26f11da15f76f2556123ef6616");

      //Send static value
      //int httpResponseCode = http.POST("{\"thing\":\"flashnode\",\"key\":\"\",\"content\":{\"humidity\":2,\"temperature\":1}}");

      //Send value from a DHT sensor
      int httpResponseCode = http.POST("{\"thing\":\"chinode2\",\"key\":\"\",\"content\":{\"humidity\":" + str_h + ",\"temperature\":" + str_t + "}}");

      StaticJsonBuffer<200> jsonBuffer;
      JsonObject &root = jsonBuffer.createObject();   
     
      root.printTo(Serial);
      
      char json_str[100];
      root.prettyPrintTo(json_str, sizeof(json_str));
      
      if (httpResponseCode > 0)
        {
            String response = http.getString();

            Serial.println(httpResponseCode);
            Serial.println(response);
        }
        else
        {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }
        http.end();
  }
  
  else {
      Serial.println("WiFi Disconnected");
    }
}
