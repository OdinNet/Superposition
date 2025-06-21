// Libraries #################################
#include <Wire.h>
#include "Adafruit_TCS34725.h"
// ###########################################

// Constants #################################
const int outputPin = A1; 
const int LED_PIN = 9;
// ###########################################

// Objects ###################################
// Initialize the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

// ###########################################

int soilsensor(int analog_pin) {
    return analogRead(analog_pin);
}

void setup() {
    Serial.begin(9600);
    Serial.print("--- Main Initiating ---");

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    if (tcs.begin()) {
        Serial.println("Found TCS34725 sensor");
        tcs.setInterrupt(true);  // Turn off LED until needed
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1); // Halt if sensor is not found
    }
}

void loop() {
    digitalWrite(LED_PIN, HIGH);  // Turn on the LED for consistent lighting
    delay(500);  // Allow the LED to stabilize

    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);

    // Normalize the color values
    float sum = (float)c;
    float red   = r / sum;
    float green = g / sum;
    float blue  = b / sum;

    Serial.print("R: "); Serial.print(r);
    Serial.print(" G: "); Serial.print(g);
    Serial.print(" B: "); Serial.print(b);
    Serial.print(" C: "); Serial.println(c);

    uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
    uint16_t lux       = tcs.calculateLux(r, g, b);
    Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.println(lux);

    // Determine the dominant color
    if (red > green && red > blue) {
        Serial.println("Detected Color: RED");
    } else if (green > red && green > blue) {
        Serial.println("Detected Color: GREEN");
    } else if (blue > red && blue > green) {
        Serial.println("Detected Color: BLUE");
    } else {
        Serial.println("Detected Color: UNKNOWN");
    }

    digitalWrite(LED_PIN, LOW);  // Turn off the LED after reading
    delay(2000);  // Wait before the next reading
}
