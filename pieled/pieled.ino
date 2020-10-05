#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid = "IoT Lab";
const char* password = "csiot335";

#define APPID "ChiApp"
#define KEY "W5wwspwT9N24OaT"
#define SECRET "OzA6mqIqwsH2uPjd2tZgNebuq"

#define ALIAS "pieled"

WiFiClient client;

int timer = 0;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message -->");
  msg[msglen] = '\0';
  Serial.println((char *)msg);

  if (*(char *)msg == '1') {
    digitalWrite(D4, LOW); // LED on
    microgear.chat("switch", "0");
  } else {
    digitalWrite(D4, HIGH); // LED off
    microgear.chat("switch", "1");
  }
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void setup() {
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);

  Serial.begin(115200);
  Serial.println("Starting...");
  
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  
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
    Serial.println("...");
    microgear.loop();
    timer = 0;
  } else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);
}
