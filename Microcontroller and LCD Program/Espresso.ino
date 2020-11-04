#include <Wire.h>
#include "LCDdriver.h"

#define calibration 0.155
LCD mylcd(0x3E);    //Create LCD object

int rightButton=D7;
int leftButton=D3;
int downButton=D4;


//Variables for screens
int currentScreen=0;
char temp[15];

//Flow Screen
double flowRate=0;
double setpoint=1;
//Time Screen
int startTime=millis();
int timeElapsed=0;
//Mass Screen
double zeroMassG=0;
double currentMassG=0;
double previousMass=0;
void setup()
{
  pinMode(D5,OUTPUT);
  pinMode(rightButton,INPUT_PULLUP);
  pinMode(leftButton,INPUT_PULLUP);
  pinMode(downButton,INPUT_PULLUP);
  mylcd.init();
  digitalWrite(D5,HIGH);
  mylcd.writeString("Starting");
  mylcd.lineFeed();
  mylcd.writeString("Espresso");
  mylcd.lineFeed();
  mylcd.blinkOff();
  mylcd.cursorOff();
  delay(1000);
}

void getMass(){
  previousMass=currentMassG;
  currentMassG=analogRead(A0)*calibration;
  if(currentMassG-zeroMassG<0)
    currentMassG=zeroMassG;
}
void flowScreen(){
  getMass();
  flowRate=(currentMassG-zeroMassG-previousMass)*2;
  mylcd.clear();
  if(flowRate<0)
    flowRate=0;
  String flowString=String(flowRate,1);
  flowString.toCharArray(temp,15);
  mylcd.writeString("Flow:");
  mylcd.writeString(temp);
  mylcd.writeString("ml/s");
  mylcd.up();
  if(flowRate-setpoint<0.2)
    mylcd.writeString(15,"^");
  else if(flowRate-setpoint > 0.2)
    mylcd.writeString(15,"v");
  else
    mylcd.writeString(15,"-");
  mylcd.lineFeed();
  mylcd.writeString("<Mass     Time>");
}

void timeScreen(){
  getMass();
  flowRate=currentMassG-zeroMassG-previousMass;
  timeElapsed=millis()-startTime;
  mylcd.clear();
  String timeString=String(timeElapsed/1000);
  timeString.toCharArray(temp,15);
  mylcd.writeString("Time:");
  mylcd.writeString(temp);
  mylcd.writeString("s");
  mylcd.up();
  if(flowRate-setpoint<0.2)
    mylcd.writeString(15,"^");
  else if(flowRate-setpoint > 0.2)
    mylcd.writeString(15,"v");
  else
    mylcd.writeString(15,"-");
    
  mylcd.lineFeed();
  mylcd.writeString("<Flow     Mass>");
}

void massScreen(){
  getMass();
  flowRate=currentMassG-zeroMassG-previousMass;
  mylcd.clear();
  String massString=String(currentMassG-zeroMassG,1);
  massString.toCharArray(temp,15);
  mylcd.writeString("Mass:");
  mylcd.writeString(temp);
  mylcd.writeString("g");
  mylcd.up();
  if(flowRate-setpoint<0.2)
    mylcd.writeString(15,"^");
  else if(flowRate-setpoint > 0.2)
    mylcd.writeString(15,"v");
  else
    mylcd.writeString(15,"-");
  
  mylcd.lineFeed();
  mylcd.writeString("<Time     Flow>");
}

void loop()
{
  if(digitalRead(rightButton)==LOW){
    currentScreen++;
  }
  if(digitalRead(leftButton)==LOW){
    currentScreen--;
  }
  if(digitalRead(downButton)==LOW){
    zeroMassG=analogRead(A0)*calibration;
    startTime=millis();
  }

  if(currentScreen>2)
    currentScreen=0;

  if(currentScreen<0)
    currentScreen=2;

  switch(currentScreen){
    case 0:
      flowScreen();
      break;
    case 1:
      timeScreen();
      break;
    case 2:
      massScreen();
      break;
  }
  delay(500);
}
