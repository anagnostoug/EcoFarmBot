 
#include <VarSpeedServo.h>
#include <SoftwareSerial.h>
#include <Wire.h>

VarSpeedServo myservoRain;
VarSpeedServo myservo1;
VarSpeedServo myservo2r;
VarSpeedServo myservo2l;
VarSpeedServo myservo3;
VarSpeedServo myservo4;
VarSpeedServo myservo5;
VarSpeedServo myservo6;

const int servoRain = 2;
const int servoPin1 = 6;
const int servoPin2r = 7;
const int servoPin2l = 8;
const int servoPin3 = 9;
const int servoPin4 = 10;
const int servoPin5 = 11;
const int servoPin6 = 12;
int i=0;
int z=0;
int r=0;

int mov1[] = {160,105,85,30};
int mov2r[] = {105,150};
int mov2l[] = {75,30};
int mov3[] = {40,0};
int mov4[] = {45,20};
int mov5[] = {130,45};
int mov6[] = {130,40};
SoftwareSerial bt(3, 5);


void setup() {
  myservoRain.attach(servoRain);
  myservo1.attach(servoPin1);
  myservo2r.attach(servoPin2r);
  myservo2l.attach(servoPin2l);
  myservo3.attach(servoPin3);
  myservo4.attach(servoPin4);
  myservo5.attach(servoPin5);
  myservo6.attach(servoPin6);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(2,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(22,OUTPUT);
  pinMode(23,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(22,HIGH);
  digitalWrite(23,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(25,HIGH);
  bt.begin(9600);
  
  ResetPos(); 
  myservoRain.write(0,20,true); 
}

void loop() {
    if (analogRead(A1)>500 & r==1){
      r=0;
      myservoRain.write(0,20,true);
    }
    else if (analogRead(A1)<800 & r==0){ 
      r=1;
      myservoRain.write(160,20,true);
    }
    myservo1.write(mov1[z],20,true);
    Pos(); 
    ReadSoil();
    if(i>0){ 
       Pot();
    }
    EndPos();
    z++;
    if(z>3){z=0;} 
    i=0;
    
}
void ResetPos(){ 
  myservo1.write(90,20,false);
  myservo2r.write(0,20,false);
  myservo2l.write(180,20,false);
  myservo3.write(100,20,false);
  myservo4.write(0,20,false);
  myservo5.write(0,20,false);
  myservo6.write(0,20,false);
  delay(5000);  
}
void EndPos(){
  tinagma();
  myservo2l.write(180,20,false);
  myservo2r.write(0,20,true);
  myservo5.write(0,20,false);
  myservo4.write(45,20,false);
  myservo3.write(100,20,true);
  myservo6.write(0,20,false);
  delay(3000);
  myservo1.write(90,20,false);
   delay(5000); 
}

void Pos(){
  myservo5.write(mov5[i],20,true);
  myservo6.write(mov6[i],20,true);
    myservo2r.write(mov2r[i],20,false); 
    myservo2l.write(mov2l[i],20,false);
    myservo3.write(mov3[i],20,false);
    myservo4.write(mov4[i],20,false); 
    delay(10000);  
}
void ReadSoil(){
  bt.print(char(65+z));
  bt.print("|");//BT_delimiter
  bt.println(analogRead(A0));
  if(analogRead(A0)>800){
    i=1;
    digitalWrite(z+22,HIGH);
    }
    else{
     digitalWrite(z+22,LOW); 
    }
  delay(500);
}
void Pot(){ 
  tinagma();
  myservo2l.write(95,20,false);
  myservo2r.write(85,20,true);
  delay(3000);
  myservo6.write(50,20,true);
  myservo2r.write(95,20,false);
  myservo2l.write(85,20,true);
  delay(2000);
  digitalWrite(4,HIGH);
  delay(3000);
  digitalWrite(4,LOW);
  digitalWrite(z+22,LOW);
  //myservo1.write(90,20,false);
   delay(5000); 
}
void tinagma(){
  myservo2l.write(105,20,false);
  myservo2r.write(75,20,true);
  delay(3000);
  for(int d=0;d<20;d++){
  myservo6.write(130,180,true);
  myservo6.write(100,180,true);
  }
   delay(5000); 
}
