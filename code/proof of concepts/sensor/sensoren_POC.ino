void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:

  Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  Serial.println(analogRead(A2));
  Serial.println(analogRead(A3));
  Serial.println(analogRead(A4));
  Serial.println(analogRead(A5));
  Serial.println(analogRead(A6));
  Serial.println(analogRead(A7));
  Serial.println(" ");
  delay(1000);
  
}
