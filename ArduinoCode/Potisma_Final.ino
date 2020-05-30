 
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


int i=0;                                //Υγρασία γλάστρας
int z=0;                                //Αριθμός γλάστρας
int r=0;                                //Αισθητήρας βροχής

int mov1[] = {150,105,85,30};
int mov2r[] = {123,150};
int mov2l[] = {57,30};
int mov3[] = {0,0};
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
  myservoRain.write(0,20,false);
  ResetPos();  
}


void loop() {
    if (analogRead(A1)>800 & r==1){         //Αισθητήρας βροχής
      r=0;
      myservoRain.write(0,20,false);
    }
    else if (analogRead(A1)<800 & r==0){ 
      r=1;
      myservoRain.write(160,20,false);
    }
    myservo1.write(mov1[z],20,true);        //Θέση γλάστρας 1-4 για servo1 
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

//Αρχική θέση βραχίονα (μοίρες,ταχύτητα)
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

//Ενδιάμεση θέση βραχίονα μετά από μέτρηση υγρασίας (μοίρες,ταχύτητα)
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

//Θέση βραχίονα για μέτρηση υγρασίας (μοίρες,ταχύτητα)
void Pos(){
    myservo2r.write(mov2r[i],20,false); 
    myservo2l.write(mov2l[i],20,false);
    myservo3.write(mov3[i],20,false);
    myservo4.write(mov4[i],20,false);
    myservo6.write(mov6[i],20,false);
    myservo5.write(mov5[i],20,false);
    delay(10000);  
}

//Μέτρηση υγρασίας
void ReadSoil(){
  //String a;
  //a=String();
  bt.print(char(65+z));             //Αποστολή πληροφοριών στο κινητό τηλέφωνο
  bt.print("|");//BT_delimiter
  bt.println(analogRead(A0));
  if(analogRead(A0)>950){           //Έλεγχος τιμής υγρασίας και αντίστοιχη λειτουργία
    i=1;
    digitalWrite(z+22,HIGH);        //Χρώμα LED
    }
    else{
     digitalWrite(z+22,LOW);        //Χρώμα LED
    }
  delay(500);
}

//Πότισμα γλάστρας
void Pot(){ 
  tinagma();
  myservo2l.write(105,20,false);
  myservo2r.write(75,20,true);
  delay(3000);
  myservo6.write(50,20,true);
  myservo2r.write(120,20,false);
  myservo2l.write(60,20,true);
  delay(2000);
  digitalWrite(4,HIGH);
  delay(3000);
  digitalWrite(4,LOW);
  digitalWrite(z+22,LOW);
  //myservo1.write(90,20,false);
   delay(5000); 
}

//Καθαρισμός αισθητήρα υγρασίας από χώματα
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
