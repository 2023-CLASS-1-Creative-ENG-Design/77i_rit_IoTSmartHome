#include <Arduino.h>
const byte segValue[10][7] = {
   {1,1,1,1,1,1,0}, //0
   {0,1,1,0,0,0,0}, //1
   {1,1,0,1,1,0,1}, //2
   {1,1,1,1,0,0,1}, //3
   {0,1,1,0,0,1,1}, //4
   {1,0,1,1,0,1,1}, //5
   {1,0,1,1,1,1,1}, //6
   {1,1,1,0,0,0,0}, //7
   {1,1,1,1,1,1,1}, //8
   {1,1,1,1,0,1,1}  //9  
};

const byte segPin[8] = {7, 3, A3, A1, A0, 6, A4, A2};
const byte digitPin[4] = {8, 5, 4, A5};
const byte interruptPin = 2;
boolean state = false;
extern volatile unsigned long timer0_millis;
unsigned long readTime;
int hour, min, sec;

void setup() {
  Serial.begin(9600);  
  
  pinMode(interruptPin, INPUT_PULLUP); 
  attachInterrupt(digitalPinToInterrupt(interruptPin), switchFn, FALLING);
  
  for(int i=0;i<10;i++){
    pinMode(segPin[i], OUTPUT);
  }
  for(int j=0;j<4;j++){
    pinMode(digitPin[j], OUTPUT);    
    digitalWrite(digitPin[j], HIGH); 
  }  
}

void loop() {   
  if(Serial.available()){ //입력시간 읽기
    String inString = Serial.readStringUntil('\n');    
    int index1 = inString.indexOf(':'); 
    int index2 = inString.indexOf(':',index1+1);   
    int index3 = inString.length();
    
    hour = inString.substring(0, index1).toInt();
    min = inString.substring(index1+1,index2).toInt();
    sec = inString.substring(index2+1,index3).toInt(); 
    
    timer0_millis = ((long)hour*3600+min*60+sec)*1000;   //입력시간 초변환
  } 
    
  if(millis()>=86400000){ //타이머 리셋
     timer0_millis=0;
  }
  readTime = millis()/1000; //현재시간 읽기
  sec = readTime%60;
  min = (readTime/60)%60;
  hour = (readTime/(60*60))%24; 

  if(state==true){ //12시 or 24시 출력모드
    hour = hour%12;
  } 
  segOutput(3,min%10,0); //min 1의 자리
  segOutput(2,min/10,0); //min 10의 자리
  segOutput(1,hour%10,1); //hour 1의 자리
  segOutput(0,hour/10,0); //hour 10의 자리    
}

//12시 or 24시 출력 변경
void switchFn(){
  state=!state;
}

//LED 초기화
void segClear(){ 
  for(int i=0;i<8;i++){
    digitalWrite(segPin[i], LOW);        
  }
}
//LED 출력
void segOutput(int d, int Number, int dp){ 
  segClear();
  digitalWrite(digitPin[d], LOW); 
  for(int i=0;i<7;i++){
     digitalWrite(segPin[i], segValue[Number][i]);        
  }
  digitalWrite(segPin[7], dp);
  delayMicroseconds(1000);
  digitalWrite(digitPin[d], HIGH); 
}