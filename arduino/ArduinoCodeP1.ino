byte sensorPin = 6; 
volatile byte pulseCount = 0; 
unsigned long oldTime = 0; 

void setup() {
  Serial.begin(9600); 
  pinMode(sensorPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING); 
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - oldTime >= 5000) { 
    detachInterrupt(digitalPinToInterrupt(sensorPin)); 

    Serial.print("Rotations: ");
    Serial.print(pulseCount);
    Serial.print(", Time: ");
    Serial.println(currentTime);

    pulseCount = 0; 
    oldTime = currentTime; 

    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING); 
  }
}

void pulseCounter() {
  pulseCount++; 
}
