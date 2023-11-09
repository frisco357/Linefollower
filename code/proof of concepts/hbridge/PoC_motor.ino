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
  
  digitalWrite(AIN1,HIGH); 
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH); 
  digitalWrite(BIN2,LOW);

  delay(1000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,LOW);
  
  delay(1000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,HIGH);

  delay(1000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW); 
  digitalWrite(BIN2,LOW);
  
  delay(1000);
   
}
