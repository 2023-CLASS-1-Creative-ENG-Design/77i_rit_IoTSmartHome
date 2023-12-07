#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>

//주변환경의 온도와 습도를 측정하여 시리얼모니터에 출력하기

#define DHTPIN 7
#define DHTTYPE DHT11

int Contrast=75;
LiquidCrystal lcd(12,11,5,4,3,2);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  analogWrite(6,Contrast);
  lcd.begin(16,2);
}

void loop() {
  //온도와 습도 값을 측정하고 변수에 저장하기
  float humi, temp;
  temp = dht.readTemperature();
  humi = dht.readHumidity();

  //센서가 측정하지 못 할 경우 측정 종료
  if(isnan(humi) || isnan(temp)){
    Serial.println("Failed to read from DHT sensor!!");
    return;
  }

  //측정된 온도와 습도 출력하기
  Serial.print("온도:");
  Serial.print(temp);
  Serial.println("℃");
  Serial.print("습도:");
  Serial.print(humi);
  Serial.println("%");

  lcd.setCursor(0,0);
  lcd.print("temp:");
  lcd.print(temp);
  lcd.write((uint8_t)223);
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("humidity:");
  lcd.print(humi);
  lcd.print("%");

}