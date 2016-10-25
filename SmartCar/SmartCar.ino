#include <Servo.h> 

Servo myservo;

const int servoPin=7;

const int A_1A = 10; 
const int A_1B = 11; 
const int B_1A = 8; 
const int B_1B = 9; 

const int disOut=6;
const int disIn=5;

boolean autoFlag=true;
const int maxDis=10;//cm

//int dis1=0;
//int dis2=0;
//int distance=0;

String comdata = "";
void setup() {
  //Serial.begin(9600);
  pinMode(A_1A, OUTPUT);
  pinMode(A_1B, OUTPUT);
  pinMode(B_1A, OUTPUT);
  pinMode(B_1B, OUTPUT);
  //left(500);
  stopit();
  //right(500);
  
  pinMode(disIn,INPUT);
  pinMode(disOut,OUTPUT);
  
  myservo.attach(servoPin);
  myservo.write(90);
}

void loop(){
  comdata = "";
  if(!autoFlag)
  {
      while (Serial.available() > 0 )  
      {
          comdata += char(Serial.read());
          delay(2);
      }
      if (comdata.length() > 0)
      {
          switch(comdata[0])
          {
            case 'F':
              forword();
              break;
            case 'B':
              back();
              break;
            case 'L':
              left();
              break;
            case 'R':
              right();
              break;
            case 'A':
              autoFlag=true;
            default:
              stopit();
              break;
          }
      }
  }else{
//    if(detectForword()){
//       Serial.println("F>>");
//       forword(300);
//    }else{
//      if(detectLeft()){
//        Serial.println("L>>");
//        left(300);
//      }else if(detectRight()){
//        Serial.println("R>>");
//         right(300);
//      }else{
//        Serial.println("B>>");
//        back(300);
//      }
//    }
    if(getDis()>maxDis){
      forword();
      delay(300);
    }else{
      stopit();
      myservo.write(160);
      delay(400);
      int disL=getDis();
      myservo.write(20);
      delay(500);
      int disR=getDis();
      while(disL<maxDis && disR<maxDis){
          back();
          myservo.write(90);
          delay(300);
          stopit();
          delay(100);
          myservo.write(160);
          delay(500);
          int disL=getDis();
          myservo.write(20);
          delay(500);
          int disR=getDis();
      }
        if(disL>disR){
          left();
          myservo.write(90);
          delay(300);
          stopit();
          delay(100);
        }else{
          right();
          myservo.write(90);
          delay(300);
          stopit();
          delay(100);
        }
      }
    }
}

 void forword(){
  digitalWrite(A_1A, HIGH);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, HIGH);
 }
  void back(){
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, HIGH);
  digitalWrite(B_1A, HIGH);
  digitalWrite(B_1B, LOW);
 }
  void left(){
  digitalWrite(A_1A, HIGH);
  digitalWrite(A_1B, LOW);
  digitalWrite(B_1A, HIGH);
  digitalWrite(B_1B, LOW);
 }
  void right(){
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, HIGH);
  digitalWrite(B_1A, LOW);
  digitalWrite(B_1B, HIGH);
 }
  void stopit(){
  digitalWrite(A_1A, HIGH);
  digitalWrite(A_1B, HIGH);
  digitalWrite(B_1A, HIGH);
  digitalWrite(B_1B, HIGH);
 }
 int getDis(){
    int dis1=dis();
    int dis2=dis();
    int distance=(dis1+dis2)/2;
    return distance;
 }
  float dis(){
    digitalWrite(disOut, LOW); 
    delayMicroseconds(2);
    digitalWrite(disOut, HIGH);
    delayMicroseconds(10);
    digitalWrite(disOut, LOW);  
    int distance = pulseIn(disIn, HIGH);
    return distance/58;
  }
  boolean detectForword(){
    //myservo.write(90);
    //delay(200);
    int dis1=dis();
    delay(10);
    int dis2=dis();
    int distance=(dis1+dis2)/2;
    Serial.print("F:");
    Serial.println(distance);
    if(distance>maxDis){
       return true;
    }else{
      return false;
    }
  }
  boolean detectLeft(){
    myservo.write(150);
    delay(250);
    int dis1=dis();
    delay(10);
    int dis2=dis();
    myservo.write(90);
    //delay(250);
    int distance=(dis1+dis2)/2;
    Serial.print("L:");
    Serial.println(distance);
    if(distance>maxDis){
       return true;
    }else{
      return false;
    }
  }
  boolean detectRight(){
    myservo.write(30);
    delay(250);
    int dis1=dis();
    delay(10);
    int dis2=dis();
    myservo.write(90);
    //delay(250);
    int distance=(dis1+dis2)/2;
    Serial.print("R:");
    Serial.println(distance);
    if(distance>maxDis){
       return true;
    }else{
      return false;
    }
  }

