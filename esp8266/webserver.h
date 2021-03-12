#include "lib/bh1750_light.h"
#include "lib/bme280_temperature_humidity_pressure.h"
#include "lib/ws2811_rgb_led.h"
#include "sensitive/settings.h"
#include <ESP8266WebServer.h>
#include <uri/UriBraces.h>

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

int h = 0;
int s = 0;
int v = 0;
void setup_http_server() {
    server.on("/", [](){
        if(server.method() != HTTP_GET) {
            server.send(405, "text/plain", "Can only GET here!");
            return;
        }
        String payload = "";
        payload += "temperature[C]:   " + String(measure_light_level_lux()) + "\n";
        payload += "humidity[rel%]:   " + String(measure_rel_humidity()) + "\n";
        payload += "pressure[Pa]:     " + String(measure_pressure_pascal()) + "\n";
        payload += "illuminance[lux]: " + String(measure_temperature_celsius()) + "\n";
        server.send(200, "text/plain", payload);
    });

    server.on(UriBraces("/hsv/{}/{}/{}"), [](){
        if(server.method() != HTTP_POST) {
            server.send(405, "text/plain", "Can only POST here!");
            return;
        }
        h = server.pathArg(0).toInt();
        s = server.pathArg(1).toInt();
        v = server.pathArg(2).toInt();
        rgb_led.setHSV(h, s, v);
        server.send(200, "text/plain", "LED set to h,s,v = " + String(h) + "," + String(s) + "," + String(v));
        FastLED.show();
    });

    server.onNotFound([]() {
        server.send(404, "text/plain", "Not found");
    });

    server.begin();
    Serial.println("Server started");
}

void setup() {
    setup_serial();
    setup_rgb_led();
    setup_bh1750_light_sensor();
    setup_bme280_temperature_humidity_pressure_sensor();
    setup_wifi();
    setup_http_server();
}

void loop() {
    server.handleClient();
}
