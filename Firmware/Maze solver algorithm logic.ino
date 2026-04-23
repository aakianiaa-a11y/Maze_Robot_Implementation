#include <Servo.h>                                        // this library is used for servo initiation 
#include "NewPing.h"                                      // this library is used for ultrasonic initiation

////
int i=0; 
//

int serv = 5;                                    // Servo pin

//motor A
int enA  = 11;                                   // Right
int in1  = 12;                                   // Right backward
int in2  = 8;                                    // Right foreward

// Motor B
int enB   = 6;                                    // Left
int in3   = 7;                                    // Left backward
int in4   = 4;                                    // Left - forward

int pos   = 0;                                    // variable to store the servo position
int start = 13;                                   // this the start push button
int Rightdist1;                                   // cotain the right distance
int Leftdist1;                                    // cotain the left distance
int foreward;
int timediv1;                                     // it is use for scaling the time 
int timediv2;                                     // it is use for scaling the time 
int d = 15;                                       // it indicates the margin distance
int scantime = 1500;                              // the asigned for scaning
int  num_time;
int scannum = 0;

//Ultrasonic pins
// Hook up HC-SR04 with Trig to Arduino Pin 9, Echo to Arduino pin 10
#define TRIGGER_PIN 9
#define ECHO_PIN    10
#define MAX_DISTANCE 1000	                             // Maximum distance we want to ping for (in centimeters).
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);    // NewPing setup of pins and maximum distance.
Servo myservo;







void setup() {
  /////////////////
  digitalWrite(enB, 120);
  digitalWrite(enA, 100);
  ///////////////////
  myservo.attach(serv);  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(start,INPUT_PULLUP);
  Serial.begin(9600);

  while(digitalRead(start) == 0){          // this is a loop which needs press push button to start the robot functions    
    delay(100);
  }
 delay(500);
}

void loop() {
  stop();
  scan();
  if(scannum>=2){
    stop();
    digitalWrite(in1,HIGH);
    digitalWrite(in3,HIGH);
    delay(500);
    stop();
    scannum = 0;
  }
    if (foreward >= d ){
    num_time = foreward / 3;
    for (int i =0 ; i < 0.55*num_time ; i++){               //defining the safaty factor 
      go();
      delay(100);
      Leftdist1 = sonar.ping_cm();
      if(Leftdist1 <40){
        if(Leftdist1 >20  ){
        i += 3;
        stop();
        digitalWrite(in2 , HIGH);
        delay(200);
        digitalWrite(in4 , HIGH);       
        delay(100);
        digitalWrite(in2 , LOW);  
        delay(100);
        stop();
      }
      if(Leftdist1 <10){
        i += 3;
        stop();
        digitalWrite(in4 , HIGH);
        delay(200);
        digitalWrite(in2 , HIGH);       
        delay(100);
        digitalWrite(in4 , LOW);  
        delay(100);
        stop();
      }
      }
      }}
      else if((Rightdist1 - Leftdist1) > 10 ) {turn_right();}
      else if((Leftdist1 - Rightdist1) > 10 ) {turn_left();}
      else if (Rightdist1 > 30  &&  Leftdist1 >35  && foreward > 35 ){ stop();}
     }
  
//--------------------scaning the environment---------------------------
void scan(){
  scannum += 1;
 stop();
 myservo.write(0);
 delay(scantime);
 Rightdist1 = sonar.ping_cm();
 myservo.write(90);
 delay(scantime);
 foreward = sonar.ping_cm();
 myservo.write(180);
 delay(scantime);
 Leftdist1 = sonar.ping_cm();
 delay(500);
}

//----------------going foreward------------------------------------
void go(){ 
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH); 
  scannum = 0;
  }


//----------------tuen off the motors-----------------------------
void stop(){
   digitalWrite(in1, LOW);  
   digitalWrite(in2, LOW);
   digitalWrite(in3, LOW);  
   digitalWrite(in4, LOW);
  
}


//-------------------TURN LEFT----------------------------
void turn_left(){
   digitalWrite(in4,LOW);
   digitalWrite(in1,LOW);
   digitalWrite(in2, HIGH);  
   digitalWrite(in3, HIGH);  
   delay(500);
   digitalWrite(in2, LOW);  
   digitalWrite(in3, LOW); 
   delay(100);
   scannum = 0;
}



//---------------------TURN RIGHT------------------------
void turn_right(){
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4, HIGH);  
  digitalWrite(in1, HIGH);  
  delay(500);
  digitalWrite(in4, LOW);  
  digitalWrite(in1, LOW); 
  delay(100);
  scannum = 0;
}


void sidetune(){                                                //this function is used to keep the robot in the middle of the road
      scannum = 0;
if(Rightdist1 >= 40  |  Leftdist1 >= 40){
} 
  else{
    if(Rightdist1>20){
    timediv1 = 200;
    timediv2 = 150;
    turn_right();
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH); 
    delay(timediv1); 
    stop();
    turn_left();
  }
  else if(Leftdist1>20){
    timediv1 = 200;
    timediv2 = 200;
    turn_left();
    digitalWrite(in2, HIGH);
    digitalWrite(in4, HIGH); 
    delay(timediv1); 
    stop();
    turn_right();
  }
  }  
}