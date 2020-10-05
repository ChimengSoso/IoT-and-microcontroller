#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid = "IoT Lab";
const char* password = "csiot335";

#define APPID "ChiApp"
#define KEY "W5wwspwT9N24OaT"
#define SECRET "OzA6mqIqwsH2uPjd2tZgNebuq"
#define ALIAS "pieblink"

WiFiClient client;

int timer = 0;
char state = 0;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  Serial.print("Incoming message -->");
  msg[msglen] = '\0';
  Serial.println((char *)msg);

  if (*(char *)msg == '1') {
    digitalWrite(LED_BUILTIN, LOW); // LED on
  } else {
    digitalWrite(LED_BUILTIN, HIGH); // LED off
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
  pinMode(LED_BUILTIN, OUTPUT);
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
    Serial.println("connected");
    microgear.loop();

    if (timer >= 1000) {
      Serial.println("Publish...");
      
      if (state == 0) {
        microgear.chat(ALIAS, state);
        state = 1;
      } else {
        microgear.chat(ALIAS, state);
        state = 0;
      }
      timer = 0;
    }
    else timer += 100;
  }
  else {
    Serial.println("connection lost, reconnect...");
    if (timer >= 5000) {
      microgear.connect(APPID);
      timer = 0;
    }
    else timer += 100;
  }
  delay(100);
}
