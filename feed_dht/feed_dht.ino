#include <DHT.h>
#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid = "IoT Lab";
const char* password = "csiot335";

#define APPID "ChiApp"
#define KEY "W5wwspwT9N24OaT"
#define SECRET "OzA6mqIqwsH2uPjd2tZgNebuq"

#define ALIAS "piedht"
#define FEEDID "ChiFeed"

#define INTERVAL 5000
#define T_INCREMENT 200
#define T_RECONNECT 5000
#define BAUD_RATE 115200
#define MAX_TEMP 100
#define MAX_HUMID 100


WiFiClient client;

int timer = 0;
char str[32];

#define DHTTYPE DHT22
#define DHTPIN D4
DHT dht(DHTPIN, DHTTYPE);

float humid;
float temp;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message --> ");
  msg[msglen] = '\0';
  Serial.println((char *)msg);
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() {
  dht.begin();

  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);

  Serial.begin(BAUD_RATE);
  Serial.println("Starting...");

  // initiate Wifi
  if (WiFi.begin(ssid, password)) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
}

void loop() {
  if (microgear.connected()) {
    Serial.print("*");
    microgear.loop();
    humid = dht.readHumidity();
    temp = dht.readTemperature();

    if (timer >= INTERVAL) {
      Serial.print("\nHumidity: ");
      Serial.print(humid);
      Serial.print(" %\t");
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" C%\n");

      String data = "{\"humid\":";
      data += humid;
      data += ", \"temp\":";
      data += temp;
      data += "}";
      if (isnan(humid) || isnan(temp) || humid >= MAX_HUMID || temp >= MAX_TEMP) {
        Serial.println("Failed to read from DHT sensor!");
      } else {
        Serial.print("Sending -->");
        Serial.println((char *) data.c_str());
        microgear.writeFeed(FEEDID, data); 
      }
      timer = 0;
    } else timer += T_INCREMENT;
  } else {
    Serial.println("connection lost, reconnect...");
    if (timer >= T_RECONNECT) {
      microgear.connect(APPID);
      timer = 0;
    } else timer += T_INCREMENT;
  }
  delay(200);
}
