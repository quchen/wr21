#include "lib/bh1750_light.h"
#include "lib/bme280_temperature_humidity_pressure.h"
#include "lib/ws2811_rgb_led.h"
#include "sensitive/settings.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void mqtt_message_received(char* topic, byte* payload, unsigned int length) {
    Serial.print("MQTT ");
    Serial.print(topic);
    Serial.print(": ");
    for (int i=0;i<length;i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

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

WiFiClient wifiClient;
PubSubClient mqtt(MQTT_ADDRESS, MQTT_PORT, mqtt_message_received, wifiClient);

void connect_mqtt() {
    while(!mqtt.connected()) {
        Serial.println("Attempting MQTT connection");
        if (mqtt.connect("Arbitrary client name")) {
            Serial.println("connected");
            mqtt.subscribe("#");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqtt.state());
            Serial.println();
            delay(1000);
        }
    }
}

void setup() {
    setup_serial();
    setup_wifi();
    setup_rgb_led();
    setup_bh1750_light_sensor();
    setup_bme280_temperature_humidity_pressure_sensor();
    mqtt.setCallback(mqtt_message_received);
}

unsigned long last_measurement_ms = 0;
unsigned long now_ms;
unsigned long since_last_measurement_ms;
bool measurement_outstanding;

void measure_every_ms(const unsigned long measure_interval_ms) {
    now_ms = millis();
    since_last_measurement_ms = now_ms - last_measurement_ms;
    measurement_outstanding = since_last_measurement_ms > measure_interval_ms;
    if(measurement_outstanding) {
        last_measurement_ms = now_ms;
        rgb_led.setHSV(random(0, 256), 255, 255);
        FastLED.show();
        String payload = "";
        payload += "temperature[C]: "   + String(measure_temperature_celsius()) + ", ";
        payload += "humidity[rel%]: "   + String(measure_rel_humidity())    + ", ";
        payload += "pressure[Pa]: "     + String(measure_pressure_pascal()) + ", ";
        payload += "illuminance[lux]: " + String(measure_light_level_lux());
        mqtt.publish("WR/21/measurement", payload.c_str());
        FastLED.clear();
        FastLED.show();
    }
}

void loop() {
    if(!mqtt.connected()) {
        connect_mqtt();
    }
    mqtt.loop();
    measure_every_ms(3000);
}
