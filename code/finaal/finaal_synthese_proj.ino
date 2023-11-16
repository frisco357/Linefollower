#include "SerialCommand.h"
#include "EEPROMAnything.h"

#define Baudrate 9600

#define MotorLeftForward 6
#define MotorLeftBackward 9
#define MotorRightForward 5
#define MotorRightBackward 3

SerialCommand sCmd(Serial);
bool debug;
bool running;
unsigned long previous, calculationTime;

const int sensor[] = {A0, A1, A2, A3, A4, A5, A6, A7};

struct param_t
{
  unsigned long cycleTime;
  int power;
  int black[8];
  int white[8];
  float diff;
  float kp;
} params;

int normalised[8];


void setup()
{
  running = false;
  Serial.begin(Baudrate);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), StartStop, FALLING);
  
  sCmd.addCommand("set", onSet);
  sCmd.addCommand("debug", onDebug);
  sCmd.addCommand("start", onStart);
  sCmd.addCommand("stop", onStop);
  sCmd.addCommand("calibrate", onCalibrate);
  sCmd.setDefaultHandler(onUnknownCommand);

  EEPROM_readAnything(0, params);
  
  Serial.println("setup done");
}

void loop()
{
  sCmd.readSerial();
  unsigned long current = micros();
  if (current - previous >= params.cycleTime)
  {
    previous = current;
    
    for (int i= 0; i< 8; i++)
    {
      normalised[i] = map(analogRead(sensor[i]), params.black[i], params.white[i], 0, 1000);
    }

    int index = 0;
    float position = 0;
    for (int i = 1; i < 8; i++) if (normalised[i] < normalised[index]) index = i;

   
    
    if (index == 0) index = 1;
    else if (index == 7) index = 6;

    int sZero = normalised[index];
    int sMinOne = normalised[index-1];
    int sPlusOne = normalised[index+1];

    float b = ((float) (sPlusOne - sMinOne)) / 2;

    float a = sPlusOne - b - sZero;
    position = -b /(2 * a);
    position += index - 2.5;
    position *= 9.5;

    float error = -position;
    float output = error * params.kp;
    
    output = constrain(output, -510, 510);

    int powerLeft = 0;
    int powerRight = 0;

    if (running) if (output >= 0)
    {
      powerLeft = constrain(params.power + params.diff * output, -255, 255);
      powerRight = constrain(powerLeft - output, -255, 255);
      powerLeft = powerRight + output;
    }
    else
    {
      powerRight = constrain(params.power - params.diff * output, -255, 255);
      powerLeft = constrain(powerRight + output, -255, 255);
      powerRight = powerLeft - output;
    }

    //aansturen motoren
    analogWrite(MotorLeftForward, powerLeft > 0 ? powerLeft : 0);
    analogWrite(MotorLeftBackward, powerLeft < 0 ? -powerLeft : 0);
    analogWrite(MotorRightForward, powerRight > 0 ? powerRight : 0);
    analogWrite(MotorRightBackward, powerRight < 0 ? -powerRight : 0);
  }

  unsigned long difference = micros() - current;
  if (difference > calculationTime) calculationTime = difference;
}


void onUnknownCommand(char *command)
{
  Serial.print("unknown command: \"");
  Serial.print(command);
  Serial.println("\"");
}

void onDebug()
{
  Serial.print("cycle time: ");
  Serial.println(params.cycleTime);
  
  Serial.print("power: ");
  Serial.println(params.power);
  Serial.print("diff: ");
  Serial.println(params.diff);
  Serial.print("kp: ");
  Serial.println(params.kp);

  Serial.print("black: ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(params.black[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  Serial.print("white: ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(params.white[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  Serial.print("normalised: ");
  for (int i =0; i < 8; i++)
  {
    Serial.print(normalised[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  
  Serial.print("calculation time: ");
  Serial.println(calculationTime);
  calculationTime = 0;
}


void onSet()
{
  char* param = sCmd.next();
  char* value = sCmd.next();  
  
  if (strcmp(param, "cycle") == 0) params.cycleTime = atol(value);
  else if (strcmp(param, "power") == 0) params.power = atol(value);
  else if (strcmp(param, "diff") == 0) params.diff = atof(value);
  else if (strcmp(param, "kp") == 0) params.kp = atof(value);
  
  EEPROM_writeAnything(0, params);
}

void onCalibrate()
{
  char* param = sCmd.next();

  if (strcmp(param, "black") == 0)
  {
    Serial.print("start calibrating black... ");
    for (int i = 0; i < 8; i++) params.black[i]=analogRead(sensor[i]);
    Serial.println("done");
  }
  else if (strcmp(param, "white") == 0)
  {
    Serial.print("start calibrating white... ");    
    for (int i = 0; i < 8; i++) params.white[i]=analogRead(sensor[i]);  
    Serial.println("done");      
  }

  EEPROM_writeAnything(0, params);
}

void onStart()
{
  running = true;  
}

void onStop()
{
  running = false;
}

void StartStop()
{
  running = !running;
  Serial.println("interrupt button");
}
