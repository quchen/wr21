#include "ESP8266WiFi.h"

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    delay(100);
    Serial.println("Setup done");
}

int scan_average_wifi_strength() {
    int numNetworks = WiFi.scanNetworks();
    int total = 0;
    for(int i = 0; i < numNetworks; ++i) {
        total += WiFi.RSSI(i);
    }
    return total/numNetworks;
}

void loop() {
    int average_strength = scan_average_wifi_strength();
    Serial.println(average_strength);
}
