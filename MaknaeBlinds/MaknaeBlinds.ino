#include <Adafruit_NeoPixel.h>
#include <DFPlayer_Mini_Mp3.h>
#include <SoftwareSerial.h>

#include "TM1637.h"

#define LED_PIN 12
#define LED_COUNT 15

int voice_recogn=0;

#define IN2 50    // 릴레이
#define IN1 51
#define IN4 52
#define IN3 53

#define CLK 30  //Pins for TM1637        
#define DIO 2

TM1637 tm1637(CLK,DIO); 

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib 

#include <Wire.h> 
#include "RTClib.h" 
RTC_DS3231 rtc; 

int hh, mm;

int sunny = 22;
int cloudy = 23;
int snowy = 24;
int rainy = 29;
int lightning = 26;
int sunset = 25;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
SoftwareSerial DFPlayerSerial(10, 11); // DFPlayer RX, TX

// custom function 선언
void colorWipe(uint32_t c, int colorWait);
void colorByMood(char color);

int r, g, b;

unsigned long previousMillis,currentMillis ; // 음악, 조명
//unsigned long previousMillisMT, currentMillisMT; // 모터
const long interval = 1000; // 10초;
//const long intervalMT = 1000; // 모터 interval
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);  // 블루투스 모듈 통신
  Serial2.begin(9600);

  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 
  strip.setBrightness(15);
  
  DFPlayerSerial.begin(9600);        // 소프트웨어 시리얼 통신 시작
  mp3_set_serial(DFPlayerSerial);    // DFPlayer 모듈에 소프트웨어 시리얼 설정
  delay(1);                           // 볼륨이 설정될 동안 1ms 대기
  mp3_set_volume (17);                // 볼륨 설정 (0~30)
//  mp3_pause();
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(sunny, OUTPUT);
  pinMode(cloudy, OUTPUT);
  pinMode(snowy, OUTPUT);
  pinMode(rainy, OUTPUT);
  pinMode(lightning, OUTPUT);
  pinMode(sunset, OUTPUT);
  
  digitalWrite(sunny, HIGH);
  digitalWrite(cloudy, LOW);
  digitalWrite(snowy, LOW);
  digitalWrite(rainy, LOW);
  digitalWrite(lightning, LOW);
  digitalWrite(sunset, LOW);


  Serial.println("input");
  delay(1000);
  Serial2.write(0xAA);    // compact mode 사용
  Serial2.write(0x37);
  delay(1000);
  Serial2.write(0xAA);    // 그룹1 음성 명령어 imported
  Serial2.write(0x21);

  Serial.println("The settings are complete");
  
  tm1637.init(); 
  tm1637.set(5); 

   rtc.begin(); 
}
// ---------------------------------------------------------------------------
void loop() {
  DateTime now = rtc.now(); 
  hh = now.hour(), DEC; 
  mm = now.minute(), DEC; 

  tm1637.point(POINT_ON); 
  if ((hh/10) == 0) tm1637.display(0,17); 
  else 
      tm1637.display(0,hh/10);     // hour 
      tm1637.display(1,hh%10); 
      tm1637.display(2,mm/10);    // minutes 
      tm1637.display(3,mm%10);    //  
  delay(500); 

      tm1637.point(POINT_ON); 
  if ((hh/10) == 0) tm1637.display(0,17); 
  else 
      tm1637.display(0,hh/10);     // hour 
      tm1637.display(1,hh%10); 
      tm1637.display(2,mm/10);    // minutes 
      tm1637.display(3,mm%10);    //  
  delay(500); 
  
  String input;
  String n = ""+'\n';
  if(Serial1.available()) {
    Serial1.println("--------------------------------------------");
    input = Serial1.readStringUntil('\n');
    Serial1.println("입력된 input: " + input);
    String data = input.substring(0, 1);
    Serial1.println("정제된 데이터: " + data);
    Serial1.println("--------------------------------------------");
    
      if(data == "m"){
        Serial1.println("<< m 모터 기능 >>");
        recByMood(input);
        mSeriesCtrl(input);
        }
     else if (data == "r") {
      Serial1.println("<< 사용자 지정 조명 색 변경 기능 >>");
      printCustomColor(input);                      // 사용자 색상 변경 "255,255,255" 형태로 전달됨
    } else if (data == "o") {
      colorWipe(strip.Color(0, 0, 0), 10);
    } else if (data == "a") {
      colorByMN(input);
      musicByMN(input);
    } else if (data == "c") {
        operateRemoteCtrl(input); // c1up
    }
      else if (data == "w") {
        printWhether(input);
        printIsSunset(input);
    }
    else {
      Serial.println("입력된 값이 없습니다.");
    }

  }
  
  
  while(Serial2.available()) {
     Serial.println("음성 명령 시작");
     voice_recogn=Serial2.read();
  
     switch(voice_recogn) {
       case 0x11:
        Serial1.println("음성인식");
         digitalWrite(IN1, HIGH);
         digitalWrite(IN2, LOW);
         digitalWrite(IN3, HIGH);
         digitalWrite(IN4, LOW);
         break;
       
       case 0x12:
        Serial1.println("둘 다 올려");
         digitalWrite(IN1, LOW);
         digitalWrite(IN2, HIGH);
         digitalWrite(IN3, LOW);
         digitalWrite(IN4, HIGH);
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
         colorWipe(strip.Color(100, 0, 205), 50);  // 파랑
//         mp3_play(2);
   
}
  }
}

void operateRemoteCtrl(String input){
  if(input == "c1up"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    }  
  else if(input == "c1down"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
    }
  else if(input == "c2up"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if(input == "c2down"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else if(input == "c12up"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else if(input == "c12down"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  }
  else {
    Serial1.println("잘못된 접근입니다.");
    }
  
}

void mSeriesCtrl(String input){
  if(input == "m01"){ // 혼술하기 딱 좋은 : DN - UP
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    }
    else if(input == "m02"){  // 기분전환이 필요해: UP - UP
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      }
    else if(input == "m03"){  // 캠프파이어: DN - DN
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else if(input == "m04"){  // 위로받고 싶을 떄: UP - UP
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if(input == "m05"){  // 스터디 집중모드: DN - DN
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else if(input == "m06"){  // 피톤치드 뿜뿜: DN - DN
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    else {
      Serial1.println("잘못된 접근입니다.");
      }
  
  
}


// 분위기별 맞춤 추천 기능 제어하는 함수
void recByMood(String input) {
  if (input == "mpause") {
    Serial.println("음악을 잠시 멈춥니다.");
    mp3_pause();
  } else if (input == "mstart") {
    Serial.println("음악을 다시 재생합니다.");
    mp3_play();
  } else if (input == "mstop") {
    Serial.println("맞춤 추천 기능을 종료합니다.");
    Serial.println("음악을 멈춥니다.");
    mp3_stop();
    Serial.println("조명을 끕니다.");
    colorWipe(strip.Color(0, 0, 0), 50);
  } else {
    Serial.println("input: " + input);
    Serial.println("조명을 켭니다.");
    colorByMood(input);
    Serial.println("음악을 재생합니다.");
    playMusicByMood(input);
  }
}

// 사용자 지정 색상 출력
void printCustomColor(String RGBValue) {
  String n = "";
  if (RGBValue != n) {
    r = splitRValue(RGBValue);
    Serial.println(r);
    g = splitGValue(RGBValue);
    Serial.println(g);
    b = splitBValue(RGBValue);
    Serial.println(b);

    colorWipe(strip.Color(g, r, b), 50);
  }
}
// 문자열 정수값으로 변환
int stringToInt(String str) {
  char exampleChar[1];
  str.toCharArray(exampleChar, 3);
  int intStr = atoi(exampleChar);
  return intStr;
}
int splitRValue(String str) {
  int first = str.indexOf(",");// 첫 번째 콤마 위치
  int second = str.indexOf(",",first+1); // 두 번째 콤마 위치
  int length = str.length(); // 문자열 길이

  String str1 = str.substring(1, first); // 첫 번째 토큰 (0, 3)

  char char1[1];
  str1.toCharArray(char1, 4);
  int r = atoi(char1);

  return r;
}
int splitGValue(String str) {
  int first = str.indexOf(",");// 첫 번째 콤마 위치
  int second = str.indexOf(",",first+1); // 두 번째 콤마 위치
  int length = str.length(); // 문자열 길이

  String str1 = str.substring(first+1, second); // 두 번째 토큰 (4, 7)

  char char1[1];
  str1.toCharArray(char1, 4);
  int g = atoi(char1);
  return g;
}
int splitBValue(String str) {
  int first = str.indexOf(",");// 첫 번째 콤마 위치
  int second = str.indexOf(",",first+1); // 두 번째 콤마 위치
  int length = str.length(); // 문자열 길이

  String str1 = str.substring(second+1,length); // 세 번째 토큰(8, 10)  
  char char1[1];
  str1.toCharArray(char1, 4);
  int b = atoi(char1);

  return b;
}
// 지정한 컬러로 픽셀 하나씩 출력해주는 함수
void colorWipe(uint32_t c, int colorWait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(colorWait);
  }
}
// 분위기별 맞춤 노래
void playMusicByMood(String input) {
  if (input == "m01") {
    Serial.println("첫번째 노래를 재생합니다.");
    mp3_play(21);
  } else if (input == "m02") {
    Serial.println("두번째 노래를 재생합니다.");
    mp3_play(22);
  } else if (input == "m03") {
    Serial.println("세번째 노래를 재생합니다.");
    mp3_play(23);
  } else if (input == "m04") { 
    Serial.println("네번째 노래를 재생합니다.");
    mp3_play(24);
  } else if (input == "m05") { 
    Serial.println("다섯번째 노래를 재생합니다.");
    mp3_play(25);
  } else if (input == "m06") { 
    Serial.println("여섯번째 노래를 재생합니다.");
    mp3_play(26);
  } else {
    Serial.println("잘못된 접근입니다.");
  }
}

// 분위기별 맞춤 조명
void colorByMood(String input) {
    if (input == "m01") {
      Serial.println("m01: 보라색 조명을 켭니다.");
      colorWipe(strip.Color(104, 123, 238), 50);  // 보라
    } else if (input == "m02") {
      Serial.println("m02: 노랑색 조명을 켭니다.");
      colorWipe(strip.Color(230, 255, 65), 50);  // 노랑
    } else if (input == "m03") {
      Serial.println("m03: 빨강색 조명을 켭니다.");
      colorWipe(strip.Color(0, 255, 0), 50);  // 빨강
    } else if (input == "m04") { 
      Serial.println("m04: 분홍색 조명을 켭니다.");
      colorWipe(strip.Color(158, 255, 155), 50);  // 분홍
    } else if (input == "m05") {
      Serial.println("m05: 파랑색 조명을 켭니다.");
      colorWipe(strip.Color(100, 0, 205), 50);  // 파랑
    } else if (input == "m06") { 
      Serial.println("m06: 초록색 조명을 켭니다.");
      colorWipe(strip.Color(100, 0, 0), 50);  // 초록
    } else {
      Serial.println("잘못된 접근입니다.");
    }
}


// 막내 추천 조명
void colorByMN(String input) {
  if (input == "a01") {
    colorWipe(strip.Color(255, 0, 255), 50);  // 아침 맑음
//    rainbowCycle(100);
//    rgbCycle(214, 34, 178, 50);
  } else if (input == "a02") {
    colorWipe(strip.Color(100, 70, 155), 50);  // 아침 흐림
  } else if (input == "a03") {
    colorWipe(strip.Color(234, 120, 255), 50);  // 아침 눈
  } else if (input == "a04") {
    colorWipe(strip.Color(184, 70, 255), 50);  // 아침 비번개
  } 
  
  else if (input == "a05") {
    colorWipe(strip.Color(225, 128, 42), 50);  // 점심 맑음
  } else if (input == "a06") {
    colorWipe(strip.Color(200, 90, 200), 50);  // 점심 흐림
  } else if (input == "a07") {
    colorWipe(strip.Color(214, 34, 178), 50);  // 점심 눈
  } else if (input == "a08") {
    colorWipe(strip.Color(205, 100, 60), 50);  // 점심 비번개
  } 
  
  else if (input == "a09") {
    colorWipe(strip.Color(130, 255, 0), 50);  // 저녁 맑음
  } else if (input == "a10") {
    colorWipe(strip.Color(50, 185, 50), 50);  // 저녁 흐림
  } else if (input == "a11") {
    colorWipe(strip.Color(109, 229, 41), 50);  // 저녁 눈
  } else if (input == "a12") {
    colorWipe(strip.Color(109, 229, 41), 50);  // 저녁 비번개
  } 
  
  else if (input == "a13") {
    colorWipe(strip.Color(126, 102, 234), 50);  // 밤 맑음
  } else if (input == "a14") {
    colorWipe(strip.Color(140, 161, 209), 50);  // 밤 흐림
  } else if (input == "a16") {
    colorWipe(strip.Color(117, 37, 252), 50);  // 밤 비번개
  } else if (input == "a15") {
    colorWipe(strip.Color(231, 94, 223), 50);  // 밤 눈
  } 
  
  else if (input == "a17") {
    colorWipe(strip.Color(122, 255, 133), 50);  // 새벽 맑음
  } else if (input == "a18") {
    colorWipe(strip.Color(160, 160, 200), 50);  // 새벽 흐림
  } else if (input == "a20") {
    colorWipe(strip.Color(217, 207, 223), 50);  // 새벽 비번개
  } else if (input == "a19") {
    colorWipe(strip.Color(255, 255, 255), 50);  // 새벽 눈
  }
}
// 막내 추천 음악
void musicByMN(String input) {
  if (input == "a01") {
    Serial.println("아침 맑음 노래를 재생합니다.");
    mp3_play(1);  // 아침 맑음
  } else if (input == "a02") {
    Serial.println("아침 흐림 노래를 재생합니다.");
    mp3_play(2);   // 아침 흐림
  } else if (input == "a03") {
    Serial.println("아침 눈 노래를 재생합니다.");
    mp3_play(3);   // 아침 눈
  } else if (input == "a04") {
    Serial.println("아침 비번개 노래를 재생합니다.");
    mp3_play(4);     // 아침 비번개
  } 
  
  else if (input == "a05") {
    Serial.println("점심 맑음 노래를 재생합니다.");
    mp3_play(5);  // 점심 맑음
  } else if (input == "a06") {
    Serial.println("점심 흐림 노래를 재생합니다.");
    mp3_play(6);   // 점심 흐림
  } else if (input == "a07") {
    Serial.println("점심 눈 노래를 재생합니다.");
    mp3_play(7);   // 점심 눈
  } else if (input == "a08") {
    Serial.println("점심 비번개 노래를 재생합니다.");
    mp3_play(8);     // 점심 비번개
  } 
  
  else if (input == "a09") {
    Serial.println("저녁 맑음 노래를 재생합니다.");
    mp3_play(9);  // 저녁 맑음
  } else if (input == "a10") {
    Serial.println("저녁 흐림 노래를 재생합니다.");
    mp3_play(10);   // 저녁 흐림
  } else if (input == "a11") {
    Serial.println("저녁 눈 노래를 재생합니다.");
    mp3_play(11);   // 저녁 눈
  } else if (input == "a12") {
    Serial.println("저녁 비번개 노래를 재생합니다.");
    mp3_play(12);     // 저녁 비번개
  } 
  
  else if (input == "a13") {
    Serial.println("밤 맑음 노래를 재생합니다.");
    mp3_play(13);  // 밤 맑음
  } else if (input == "a14") {
    Serial.println("밤 흐림 노래를 재생합니다.");
    mp3_play(14);   // 밤 흐림
  } else if (input == "a15") {
    Serial.println("밤 눈 노래를 재생합니다.");
    mp3_play(15);   // 밤 눈
  } else if (input == "a16") {
    Serial.println("밤 비번개 노래를 재생합니다.");
    mp3_play(16);     // 밤 비번개
  } 
  
  else if (input == "a17") {
    Serial.println("새벽 맑음 노래를 재생합니다.");
    mp3_play(17);  // 새벽 맑음
  } else if (input == "a18") {
    Serial.println("새벽 흐림 노래를 재생합니다.");
    mp3_play(18);   // 새벽 흐림
  } else if (input == "a19") {
    Serial.println("새벽 눈 노래를 재생합니다.");
    mp3_play(19);   // 새벽 눈
  } else if (input == "a20") {
    Serial.println("새벽 비번개 노래를 재생합니다.");
    mp3_play(20);     // 새벽 비번개
  }
}


void printIsSunset(String input) {
  if (input == "wSunset") {
    Serial.println("sunset");
    digitalWrite(sunset, LOW);
  } else if (input == "wSunrise") {
    Serial.println("sunrise");
    digitalWrite(sunset, HIGH);
  }
}
// 날씨 업데이트가 1시간에 한번씩은 필요할 듯?
void printWhether(String whether) {
  if (whether == "wSunny") {
    Serial.println("sunny");
    digitalWrite(sunny, HIGH);
    digitalWrite(cloudy, LOW);
    digitalWrite(snowy, LOW);
    digitalWrite(rainy, LOW);
    digitalWrite(lightning, LOW);
  } else if (whether == "wSunnyCloudy") {
    Serial.println("sunny cloudy");
    digitalWrite(sunny, HIGH);
    digitalWrite(cloudy, HIGH);
    digitalWrite(snowy, LOW);
    digitalWrite(rainy, LOW);
    digitalWrite(lightning, LOW);
  } else if (whether == "wCloudy") {
    Serial.println("cloudy");
    digitalWrite(sunny, LOW);
    digitalWrite(cloudy, HIGH);
    digitalWrite(snowy, LOW);
    digitalWrite(rainy, LOW);
    digitalWrite(lightning, LOW);
  } else if (whether == "wSnowy") {
    Serial.println("snowy");
    digitalWrite(sunny, LOW);
    digitalWrite(cloudy, LOW);
    digitalWrite(snowy, HIGH);
    digitalWrite(rainy, LOW);
    digitalWrite(lightning, LOW);
  } else if (whether == "wRainy") {
    Serial.println("rainy");
    digitalWrite(sunny, LOW);
    digitalWrite(cloudy, LOW);
    digitalWrite(snowy, LOW);
    digitalWrite(rainy, HIGH);
    digitalWrite(lightning, LOW);
  } else if (whether == "wLightning") {
    Serial.println("lightning");
    digitalWrite(sunny, LOW);
    digitalWrite(cloudy, LOW);
    digitalWrite(snowy, LOW);
    digitalWrite(rainy, LOW);
    digitalWrite(lightning, HIGH);
  }
}
