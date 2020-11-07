#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 15

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
Servo sv1_up, sv2_up;
Servo sv1_down, sv2_down;


// 서보모터 각도값 변수
int is_checked = 30;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 5000;

int voice_recogn=0;


// custom function 선언
void colorWipe(uint32_t c, int colorWait);
void colorByMood(char color);

int r, g, b;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600);
  
  sv1_up.attach(22);    // 서보모터 핀넘버
  sv1_down.attach(23);
  sv2_up.attach(24);
  sv2_down.attach(25);

  sv1_up.write(0);        // 서보모터 각도 초기화
  sv1_down.write(0);
  sv2_up.write(0);
  sv2_down.write(0);

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
         Serial.println("둘 다 내려");
         sv1_down.write(is_checked);
         sv2_down.write(is_checked);
         delay(wait);
         sv1_down.write(is_not_checked);
         sv2_down.write(is_not_checked);
         break;
       
       case 0x12:
         Serial.println("둘 다 올려");
         sv1_up.write(is_checked);
         sv2_up.write(is_checked);
         delay(wait);
         sv1_up.write(is_not_checked);
         sv2_up.write(is_not_checked);
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
         Serial1.println("막내 실행");
  
    }
   }
}
