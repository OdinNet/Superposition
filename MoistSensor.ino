#include <dht.h>

dht DHT11; 

#define DHT11_PIN 5



void main() {
    float chk = DHT11.read11(DHT11_PIN); 
    Serial.print("Temperature"); 
    Serial.println(DHT11.temperature); 
    Serial.print("Humditiy = ");
    Serial.println(DH11.humidity);
}