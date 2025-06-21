const int outputPin = A1; 


void setup() {
    Serial.begin(9600);

    Serial.print("Soil Sensor Function Started.");
}

void loop() {
    int val; 
    val = analogRead(A1); // Connecting Sensor to Analog 0
    Serial.println(val); // Print the value
    delay(500);  
}
