int ledPin = 13;
bool running;

void setup() 
{
	pinMode(ledPin, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(3), ISR_test, RISING);
}
 
void loop() 
{
  if(running){
    //move lijnvolger
    digitalWrite(ledPin,HIGH);
  }else{
    digitalWrite(ledPin,LOW);
  }
}
 
void ISR_test() {
  if(running){
    running = false;
  }else{
    running = true;
  }
}
