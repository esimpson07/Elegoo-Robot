#include <IRremote.h>
#include <Servo.h>

Servo myservo;
Servo myservo1;
Servo myservo2;

#define F 551527005
#define B 551510685
#define L 551543325
#define R 551490285
#define S 551494365
#define RTurn 551534655
#define LTurn 551502015
#define RTurn1 551518335
#define LTurn1 551485695
#define RTurn2 551540775
#define LTurn2 551506605
int RECV_PIN = 13;
int in1=4;
int in2=28;
int in3=30;
int in4=6;
int ENA=3;
int ENB=5;
int ABS=115;
int maxCountDown = 16;
int countDown = maxCountDown;
int pos = 80;
int pos1 = 80;
int pos2 = 100;

IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long val;

void _LTurn()
{
  pos = pos - 10;
  if (pos < 0){
    pos = 0;
  }
  myservo.write(pos);
}
void _RTurn()
{
  pos = pos + 10;
  if (pos > 180){
    pos = 180;
  }
  myservo.write(pos);
}
void _LTurn1()
{
  pos1 = pos1 - 10;
  if (pos1 < 0){
    pos1 = 0;
  }
  myservo1.write(pos1);
}
void _RTurn1()
{
  pos1= pos1 + 10;
  if (pos1 > 180){
    pos1 = 180;
  }
  myservo1.write(pos1);
}
void _LTurn2()
{
  pos2 = pos2 - 10;
  if (pos2 < 50){
    pos2 = 50;
  }
  myservo2.write(pos2);
}
void _RTurn2()
{
  pos2 = pos2 + 10;
  if (pos2 > 166){
    pos2 = 166;
  }
  myservo2.write(pos2);
}
void _mForward()
{ 
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,HIGH);//digital output
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go forward!");
}
void _mBack()
{
  digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  /*digitalWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);*/
  Serial.println("go back!");
}
void _mleft()
{
  analogWrite(ENA,HIGH);
  digitalWrite(ENA,HIGH);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW); 
  Serial.println("go left!");
}
void _mright()
{
  analogWrite(ENA,HIGH);
  digitalWrite(ENB,HIGH);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
  Serial.println("go right!");
}
void _mStop()
{
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  Serial.println("STOP!");  
}

void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(ENA,OUTPUT);
  pinMode(ENB,OUTPUT);
  _mStop();
  irrecv.enableIRIn();  
  Serial.begin(115200);
  myservo.attach(12);
  myservo1.attach(11);
  myservo2.attach(10);
}

void loop() {
  if (irrecv.decode(&results)){ 
    val = results.value;
    Serial.println(results.value);
    irrecv.resume();
    //if (val == 3494706272 || 1641747682 || 1920100934 || 116954692 || 541477668){
    if (val == 551527005 || 551510685 || 551543325 || 551490285 || 4294967295 || 551502015 || 551502015 || 551485695 || 551518335 || 551506605 || 551540775){
      countDown = maxCountDown;
    }
    switch(val){
      case F: _mForward(); break;
      case B: _mBack(); break;
      case L: _mleft(); break;
      case R: _mright(); break;
      case S: _mStop(); break;
      case RTurn: _RTurn(); break;
      case LTurn: _LTurn(); break;
      case RTurn1: _RTurn1(); break;
      case LTurn1: _LTurn1(); break;
      case RTurn2: _RTurn2(); break;
      case LTurn2: _LTurn2(); break;
      default:break;
    }
  }
  delay(10);
  if (countDown >= 0){
    countDown --;
  }
  if (countDown <= 0){
    val = 541477668;
    _mStop();
    countDown = maxCountDown;
  }
}
