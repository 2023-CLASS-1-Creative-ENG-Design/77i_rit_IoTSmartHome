#include <Stdio.h>
int pir=2; //PIR모션센서
int led=10; //LED
int led2 = 13; // 조도센서 LED
int pirState = LOW; //시작 시, 어떠한 움직임도 감지되지 않았다고 가정

void setup(){
  pinMode(pir, INPUT); //디지털 2번핀을 입력모드로 설정
  pinMode(led, OUTPUT); //디지털 3번핀을 출력모드로 설정
  pinMode(led2,OUTPUT);
  Serial.begin(9600); //시리얼 통신 시작, 통신 속도는 9600
}
void loop(){
  int val = digitalRead(pir); //PIR 모션센서로부터 입력값을 얻어옴
  Serial.println(val); // 시리얼 모니터에 val값을 출력

  if(val == HIGH) { //PIR 모션센서 입력값(val)이 HIGH이면
    if(pirState == LOW){
      digitalWrite(led, HIGH); // LED ON
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  } else { //LOW인 경
    if(pirState == HIGH){
      digitalWrite(led, LOW);
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  }
  
  int readValue = analogRead(A0);
  Serial.println(readValue);

  if(readValue > 215)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
}