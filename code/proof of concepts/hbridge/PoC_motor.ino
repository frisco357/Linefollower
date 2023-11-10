#define AIN1 3
#define AIN2 5
#define BIN1 6
#define BIN2 9

void setup() {
  Serial.begin(9600);
  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  
}
 
void loop() {


  for(int i = 0; i<=255;i++){
    analogWrite(AIN1,i);
    analogWrite(BIN1,i); 
    delay(10);
  }

  digitalWrite(AIN1,LOW); 
  digitalWrite(BIN1,LOW); 

  delay(1000);

  for(int i = 0; i<=255;i++){
    analogWrite(AIN2,i);
    analogWrite(BIN2,i); 
    delay(10);
  }

  digitalWrite(AIN2,LOW);
  digitalWrite(BIN2,LOW);
  delay(1000);

}
