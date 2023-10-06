int ledPin = 13;
int interruptPin = 3;
bool running;

void setup() 
{
	pinMode(ledPin, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(interruptPin), ISR_test, RISING);
}
 
void loop() 
{

}
 
void ISR_test() {
  if(running){
    running = false;
    digitalWrite(ledPin,LOW);
  }else{
    //move lijnvolger
    digitalWrite(ledPin,HIGH);
    running = true;
  }
}
