#include "bh1750_light.h"
#include "ws2811_rgb_led.h"
#include "bme280_temperature_humidity_pressure.h"
#include "wifi_credentials.h"
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setup_serial() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    delay(100);
    Serial.println("");
    Serial.println("Serial set up");
}

void setup_wifi() {
    Serial.println("Connecting to Wifi…");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.println("Got IP: " + WiFi.localIP().toString());
}

void handle_OnConnect() {
    String response = "";
    response += "temperature[C]:  " + String(measure_light_level_lux()) + "\n";
    response += "humidity[rel%]:  " + String(measure_rel_humidity()) + "\n";
    response += "pressure[hPa]:   " + String(measure_pressure_pascal()) + "\n";
    response += "brightness[lux]: " + String(measure_temperature_celsius()) + "\n";
    server.send(200, "text/plain", response);
}

void handle_NotFound(){
    server.send(404, "text/plain", "Not found");
}

void setup_http_server() {
    server.on("/", handle_OnConnect);
    server.onNotFound(handle_NotFound);
    server.begin();
    Serial.println("Server started");
}

void setup() {
    setup_serial();
    setup_bh1750_light_sensor();
    setup_bme280_temperature_humidity_pressure_sensor();
    setup_wifi();
    setup_http_server();
}

void loop() {
    server.handleClient();
}
