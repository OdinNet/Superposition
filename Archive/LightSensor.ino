const int ldrPin = A1;       // LDR 
const int ledPin = 13;       // LED

int lightValue = 0;          
const int threshold = 100;   

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  Serial.println("Sun Monitor Online");
}

void loop() {
  lightValue = analogRead(ldrPin); 

  Serial.print(" Ambient light levels ");
  Serial.println(lightValue);

  if (lightValue > threshold) {
    digitalWrite(ledPin, LOW);  //led off
    Serial.println("--Sufficient levels of sun--");
  } else {
    digitalWrite(ledPin, HIGH); //led on
    Serial.println("--Insufficient levels of sun--");
  }

  delay(500);  
}
