#include <Servo.h> 

Servo sv1_up, sv1_down, sv1_half;   // 1번 커튼 서보모터
Servo sv2_up, sv2_down, sv2_half;   // 2번 커튼 서보모터

void setup(){
  Serial.begin(9600);    // 시리얼 통신, 속도는 9600
  sv1_up.attach(22);     // 서보모터 핀넘버
  sv1_down.attach(23);   // 서보모터 핀넘버 
  sv1_half.attach(24);   // 서보모터 핀넘버
  sv2_up.attach(25);     // 서보모터 핀넘버
  sv2_down.attach(26);   // 서보모터 핀넘버 
  sv2_half.attach(27);   // 서보모터 핀넘버 

}
void loop(){
  cds_motor();  

}

void cds_motor(){
    // 조도 값: 0에 가까울수록 밝고,숫자가 클수록 어둡다.
    // 전체적인 작동 모션은 해당 조도 값에 도달했다면 버튼을 눌렀다가 0.5초 후 떼지는 형식.
    int sensor = analogRead(A0);     // 조도센서의 데이터 받아오기
    Serial.println(sensor);          // 시리얼 모니터에 조도 값 출력하기  

    // 밤, 2 up
    if(sensor > 580){         // 조도 값 580 이상, 1-2번 커튼의 up 모터 작동
      sv1_up.write(180);      // 각도 180도
      sv2_up.write(180);      // 각도 180도 
      delay(500);             // 0.5초 delay

      // while문은 조도센서 값에 변함이 없을 경우
      while(sensor >= 580 && sensor <= 1000){     // 조도 값이 1000 >= x >= 580일 경우, 1-2번 커튼 up 모터 작동
        sv1_up.write(0);            // 각도 0도
        sv2_up.write(0);            // 각도 0도
        delay(500);                 // 0.5초 delay
        sensor = analogRead(A0);    // 조도센서 값 재입력
        }
    }

    // 반암막 1 up
    if(sensor > 510){     // 조도 값 510 이상, 2번 커튼의 up 모터 작동
      sv2_up.write(180);  // 각도 180도
      delay(500);         // 0.5초 delay
      
      while(sensor >= 510 && sensor <= 570){    // 조도 값이 570 >= x >= 510일 경우, 2번 커튼 up 모터 작동
        sv2_up.write(0);                // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }

    // 암막 1 up
    if(sensor > 440){         // 조도 값 440 이상, 1번 커튼의 up 모터 작동
      sv1_up.write(180);      // 각도 180도
      delay(500);             // 0.5초 delay

      while(sensor >= 440 && sensor <= 500){    // 조도 값이 500 >= x >= 440일 경우, 1번 커튼 up 모터 작동
        sv1_up.write(0);                // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력;
        }
    }
    
    // 반암막 1 50%
    if(sensor > 370){         // 조도 값 370 이상, 2번 커튼의 half 모터 작동
      sv2_half.write(180);    // 각도 180도
      delay(500);             // 0.5초 delay

      while(sensor >= 370 && sensor <= 430){    // 조도 값이 430 >= x >= 370일 경우, 2번 커튼 half 모터 작동
        sv2_half.write(0);              // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력;
        }
    }
    
    // 암막 1 50%
    if(sensor > 300){           // 조도 값 300 이상, 1번 커튼의 half 모터 작동
      sv1_half.write(180);      // 각도 180도
      delay(500);               // 0.5초 delay

      while(sensor >= 300 && sensor <= 360){      // 조도 값이 360 >= x >= 300일 경우, 1번 커튼 half 모터 작동
        sv1_half.write(0);              // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력;
        }
    }
    
    // 2 half
    if(sensor > 230){         // 조도 값 230 이상, 1-2번 커튼의 half 모터 작동
      sv1_half.write(180);    // 각도 180도
      sv2_half.write(180);    // 각도 180도
      delay(500);             // 0.5초 delay

      while(sensor >= 230 && sensor <= 290){        // 조도 값이 290 >= x >= 230일 경우, 1-2번 커튼 half 모터 작동
        sv1_half.write(0);              // 각도 0도
        sv2_half.write(0);              // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력;
        }
    }
    
    // 반암막 1 down
    if(sensor > 160){         // 조도 값 160 이상, 2번 커튼의 down 모터 작동
      sv2_down.write(180);    // 각도 180도
      delay(500);             // 0.5초 delay

      while(sensor >= 160 && sensor <= 220){    // 조도 값이 220 >= x >= 160일 경우, 2번 커튼 down 모터 작동
        sv2_down.write(0);              // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }
    
    // 암막 1 down
    if(sensor > 90){        // 조도 값 90 이상, 1번 커튼의 down 모터 작동
      sv1_down.write(180);  // 각도 180도
      delay(500);           // 0.5초 delay

      while(sensor >= 90 && sensor <= 150){     // 조도 값이 150 >= x >= 90일 경우, 1번 커튼 down 모터 작동
        sv1_down.write(0);              // 각도 0도
        delay(500);                     // 0.5초 delay
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }
    
    // 낮, 2 down
    if(sensor > 20){          // 조도 값 20 이상, 1-2번 커튼의 down 모터 작동
      sv1_down.write(180);    // 각도 180도
      sv2_down.write(180);    // 각도 180도
      delay(500);             // 0.5초 delay

      while(sensor >= 20 && sensor <= 80){    // 조도 값이 80 >= x >= 20일 경우, 1-2번 커튼 down 모터 작동
        sv1_down.write(0);           // 각도 0도
        sv2_down.write(0);           // 각도 0도
        delay(500);                  // 0.5초 delay
        sensor = analogRead(A0);     // 조도센서 값 재입력
        }
    }  
}
