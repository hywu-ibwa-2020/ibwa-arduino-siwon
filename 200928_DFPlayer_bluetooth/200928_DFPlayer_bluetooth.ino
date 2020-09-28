#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial DFPlayerSerial(10, 11); // DFPlayer RX, TX

void setup() {
  Serial.begin (9600);
  Serial1.begin (9600);               // 블루투스 모듈 통신
  DFPlayerSerial.begin (9600);        // 소프트웨어 시리얼 통신 시작
  mp3_set_serial (DFPlayerSerial);    // DFPlayer 모듈에 소프트웨어 시리얼 설정
  delay(1);                           // 볼륨이 설정될 동안 1ms 대기
  mp3_set_volume (20);                // 볼륨 설정 (0~30)
  Serial.println("Enter the key!");       // 키 입력하기
  Serial.println("1 = 1st song");         // 1를 누른다면 첫 번째 노래 재생
  Serial.println("2 = 2nd song");         // 2를 누른다면 두 번째 노래 재생
  Serial.println("3 = 3th song");         // 3를 누른다면 세 번째 노래 재생
  Serial.println("4 = 4th song");         // 4를 누른다면 네 번째 노래 재생
  Serial.println("5 = Stop");             // 5를 누른다면 노래 중단
  Serial.println("6 = Continue\n");       // 6을 누른다면 이어서 재생
}

void loop() {
  if(Serial1.available())  // 시리얼모니터가 사용가능할 때
  {
    char input = Serial1
    .read(); // 시리얼모니터에서 문자 입력받기

    // 첫 번째 노래
    if(input == '1')    // 1 키를 누를 때
    {
      Serial.print("1st song\n");  // '1st song'를 시리얼 모니터에 출력
      mp3_play(1); // 첫 번째 노래 재생
    }
      else if (input == '5'){        // 5번 누를 시 음악 중단
        Serial.print("stop\n");      // 'stop'을 시리얼 모니터에 출력
        mp3_pause();                 
      }
        else if(input == '6'){         // 6번 누를 시 이어서 재생
          Serial.print("continue\n");  // 'continue'을 시리얼 모니터에 출력
          mp3_play();
        }

    // 두 번째 노래    
    if(input == '2')    // 2 키를 누를 때
    {
      Serial.print("2nd song\n");  // '2nd song'를 시리얼 모니터에 출력
      mp3_play(2);                 // 두 번째 노래 재생
    }
      else if (input == '5'){        // 5번 누를 시 음악 중단
        mp3_pause();                 
      }
        else if(input == '6'){       // 6번 누를 시 이어서 재생
          mp3_play();
        }
        
    // 세 번째 노래    
    if(input == '3')    // 3 키를 누를 때
    {
      Serial.print("3rd song\n");  // '3rd song'를 시리얼 모니터에 출력
      mp3_play(3);                 // 세 번째 노래 재생
    }
      else if (input == '5'){        // 5번 누를 시 음악 중단
        mp3_pause();                 
      }
        else if(input == '6'){       // 6번 누를 시 이어서 재생
          mp3_play();
        }

    // 네 번째 노래
    if(input == '4')    // 4 키를 누를 때
    {
      Serial.print("4th song\n");  // '4th song'를 시리얼 모니터에 출력
      mp3_play(4);                 // 네 번째 노래 재생
    }
      else if (input == '5'){        // 5번 누를 시 음악 중단
        mp3_pause();                 
      }
        else if(input == '6'){       // 6번 누를 시 이어서 재생
          mp3_play();
        }
    }
}
