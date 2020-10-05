#include <ESP8266WiFi.h>
#include <MicroGear.h>

const char* ssid = "IoT Lab";
const char* password = "csiot335";

#define APPID "ChiApp"
#define KEY "W5wwspwT9N24OaT"
#define SECRET "OzA6mqIqwsH2uPjd2tZgNebuq"

#define ALIAS "pieled"

WiFiClient client;

char state = 0;
char stateOutdated = 0;
char buff[16];

MicroGear microgear(client);

void sendState() {
  if (state == 0)
    microgear.publish("/pieled/state", "0");
  else 
    microgear.publish("/pieled/state", "1");
  Serial.print("send state (");
  Serial.print((int)state);
  Serial.println(")..");
  stateOutdated = 0;
}

void updateIO() {
  if (state >= 1) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) {
  char m = *(char *)msg;
  
  Serial.print("Incoming message -->");
  msg[msglen] = '\0';
  
  Serial.println((char *)msg);

  if (m == '0' || m == '1') {
    state = m == '0' ? 0 : 1;
    updateIO();
  }
  stateOutdated = 1;
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) {
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
  stateOutdated = 1;
}

void setup() {
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
  
  microgear.on(MESSAGE, onMsghandler);
  microgear.on(CONNECTED, onConnected);
  microgear.init(KEY, SECRET, ALIAS);
  microgear.connect(APPID);
}

void loop() {
  if (microgear.connected()) {
    if (stateOutdated) sendState();
    microgear.loop();
  } else {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
}
