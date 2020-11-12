#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);


int voice_recogn=0;

#define HalfDN 3  // 반암막 ir센서 
#define HalfUP 4
#define ScreenDN 6  // 암막
#define ScreenUP 7  // 암막
#define IN1 50   // 반암막 IN1 DOWN
#define IN2 51   // 반암막 IN2 UP 
#define IN3 52
#define IN4 53

// custom function 선언
void colorWipe(uint32_t c, int colorWait);
void colorByMood(char color);

int r, g, b;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  pinMode(HalfDN, INPUT);
  pinMode(HalfUP, INPUT);
  pinMode(ScreenDN, INPUT);
  pinMode(ScreenUP, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 
  strip.setBrightness(50);
  
  Serial.println("input");
  delay(1000);
  Serial2.write(0xAA);    // compact mode 사용
  Serial2.write(0x37);
  delay(1000);
  Serial2.write(0xAA);    // 그룹1 음성 명령어 imported
  Serial2.write(0x21);

  Serial.println("The settings are complete");
}

// 지정한 컬러로 픽셀 하나씩 출력해주는 함수
void colorWipe(uint32_t c, int wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
} 

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial2.available())
   {
     Serial.println("음성 명령 시작");
     voice_recogn=Serial2.read();
  
     switch(voice_recogn)
     {
       case 0x11:
        if(digitalRead(HalfDN) && !digitalRead(HalfUP) && digitalRead(ScreenDN) && !digitalRead(ScreenUP)){
        Serial.println("1, 2번 커튼을 모두 내립니다.");
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        while(digitalRead(HalfDN) && !digitalRead(HalfUP) && digitalRead(ScreenDN) && !digitalRead(ScreenUP));
        if(!digitalRead(HalfDN) && !digitalRead(HalfUP) && !digitalRead(ScreenDN) && !digitalRead(ScreenUP)){
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);     
          while(!digitalRead(HalfDN) && !digitalRead(HalfUP) && !digitalRead(ScreenDN) && !digitalRead(ScreenUP));
      }  
    }  
         break;
       
       case 0x12:
         Serial.println("둘 다 올려");
        if(!digitalRead(HalfDN) && !digitalRead(HalfUP) && !digitalRead(ScreenDN) && !digitalRead(ScreenUP)){
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        while(!digitalRead(HalfDN) && !digitalRead(HalfUP) && !digitalRead(ScreenDN) && !digitalRead(ScreenUP));
        if(digitalRead(HalfDN) && !digitalRead(HalfUP) && digitalRead(ScreenDN) && !digitalRead(ScreenUP)){
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(HalfUP) && digitalRead(ScreenDN) && !digitalRead(ScreenUP));
          }      
    }
         break;
  
       case 0x13:
        Serial.println("조명 켜");
        colorWipe(strip.Color(230, 255, 65), 50);  // 노랑
        break;
  
       
       case 0x14:
         Serial.println("조명 꺼");
         colorWipe(strip.Color(0, 0, 0), 50);
         break;
  
            
       case 0x15:
         Serial.println("막내 실행");
         Serial1.println("막내실행");
  
    }
   }
}
