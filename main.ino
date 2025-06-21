// Libraries #################################
#include <Wire.h>
#include "Adafruit_TCS34725.h"
// ###########################################

// Constants #################################
const int SOIL_PIN = A1; 
const int LED_PIN = 9;
// ###########################################

// Objects ###################################
// Initialize the TCS34725 sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
// ###########################################

int read_soilsensor(int analog_pin) {
    return analogRead(analog_pin);
}

void start_rgbsensor() {
    if (tcs.begin()) {
        Serial.println("Found TCS34725 sensor");
        tcs.setInterrupt(true);  // Turn off LED until needed
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1); // Halt if sensor is not found
    }
}

void print_rgbcolor(int r, int g, int b, int c) {
    // Normalize the color values
    float sum = (float)c;
    float red   = r / sum;
    float green = g / sum;
    float blue  = b / sum;

    // Serial.print("R: "); Serial.print(r);
    // Serial.print(" G: "); Serial.print(g);
    // Serial.print(" B: "); Serial.print(b);
    // Serial.print(" C: "); Serial.println(c);

    // // Determine the dominant color
    // if (red > green && red > blue) {
    //     Serial.println("Detected Color: RED");
    // } else if (green > red && green > blue) {
    //     Serial.println("Detected Color: GREEN");
    // } else if (blue > red && blue > green) {
    //     Serial.println("Detected Color: BLUE");
    // } else {
    //     Serial.println("Detected Color: UNKNOWN");
    // }
    uint16_t colorTemp = tcs.calculateColorTemperature(r, g, b);
    uint16_t lux       = tcs.calculateLux(r, g, b);
    // Serial.print("Color Temp: "); Serial.print(colorTemp); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.println(lux);
}

void setup() {
    Serial.begin(9600);
    Serial.print("--- Main Initiating ---");

    // Start LED on RGB sensor
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    // Start RGB sensor
    start_rgbsensor();
}

void loop() {
    Serial.println(read_soilsensor(SOIL_PIN));
    
    // LED on RGB sensor HIGH
    digitalWrite(LED_PIN, HIGH);    // Turn on the LED for consistent lighting
    delay(100);                     // Allow the LED to stabilize

    // Start printing color output/lux of RGB sensor
    uint16_t r, g, b, c;
    tcs.getRawData(&r, &g, &b, &c);
    print_rgbcolor(r, g, b, c);
    

    digitalWrite(LED_PIN, LOW);     // Turn off the LED after reading
    delay(500);                    // Wait before the next reading
}


