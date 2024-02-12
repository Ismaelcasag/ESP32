//https://microcontrollerslab.com/reconnect-esp32-to-wifi-after-lost-connection/


#include <WiFi.h>

const char* ssid = "Your_SSID";
const char* password = "Your_Password";

unsigned long previous_time = 0;
unsigned long delay = 20000;  // 20 seconds delay

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WIFI network");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  initWiFi();
}

void loop() {
  unsigned long current_time = millis(); // number of milliseconds since the upload

  // checking for WIFI connection
  if ((WiFi.status() != WL_CONNECTED) && (current_time – previous_time >=delay)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WIFI network");
    WiFi.disconnect();
    WiFi.reconnect();
    previous_time = current_time;
  }
}