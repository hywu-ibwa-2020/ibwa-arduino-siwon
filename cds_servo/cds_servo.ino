#include <Servo.h> 

Servo sv1_up, sv1_down;   // 1번 커튼 서보모터
Servo sv2_up, sv2_down;   // 2번 커튼 서보모터

// 서보모터 각도값 변수 
int is_checked = 10;        // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0;   // 버튼 클릭 안했을 때 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 10000;

void setup(){
  Serial.begin(9600);    // 시리얼 통신, 속도는 9600
  sv1_up.attach(22);     // 서보모터 핀넘버
  sv1_down.attach(23);   // 서보모터 핀넘버 
  sv2_up.attach(24);     // 서보모터 핀넘버
  sv2_down.attach(25);   // 서보모터 핀넘버 
  
  sv1_up.write(0);        // 서보모터 각도 초기화
  sv1_down.write(0);
  sv2_up.write(0);
  sv2_down.write(0);
}
void loop(){
  cds_motor();  

}

void cds_motor(){
    // 조도 값: 0에 가까울수록 밝고,숫자가 클수록 어둡다.
    // 전체적인 작동 모션은 해당 조도 값에 도달했다면 버튼을 눌렀다가 0.5초 후 떼지는 형식.
    // 1번 암막 2번 반암막
    int sensor = analogRead(A0);     // 조도센서의 데이터 받아오기
    Serial.println(sensor);          // 시리얼 모니터에 조도 값 출력하기  

    // 밤, 2 up
    if(sensor > 575){         // 조도 값 575 이상, 1-2번 커튼의 up 모터 작동
      sv1_up.write(is_checked);      // 각도 10도
      sv2_up.write(is_checked);      // 각도 10도 
      delay(wait);             

      // while문은 조도센서 값에 변함이 없을 경우
      while(sensor >= 575 && sensor <= 1000){     // 조도 값이 1000 >= x >= 575일 경우, 1-2번 커튼 up 모터 작동
        sv1_up.write(is_not_checked);            // 각도 0도
        sv2_up.write(is_not_checked);            // 각도 0도
        delay(wait);                
        sensor = analogRead(A0);    // 조도센서 값 재입력
        }
    }

    // 반암막 1 up
    if(sensor > 464){     // 조도 값 464 이상, 2번 커튼의 up 모터 작동
      sv2_up.write(is_checked);  // 각도 10도
      delay(wait);         // 0.5초 delay
      
      while(sensor >= 464 && sensor <= 574){    // 조도 값이 574 >= x >= 464일 경우, 2번 커튼 up 모터 작동
        sv2_up.write(is_not_checked);                // 각도 0도
        delay(wait);                    
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }

    // 암막 1 up
    if(sensor > 353){         // 조도 값 353 이상, 1번 커튼의 up 모터 작동
      sv1_up.write(is_checked);      // 각도 10도
      delay(wait);            

      while(sensor >= 353 && sensor <= 463){    // 조도 값이 463 >= x >= 353일 경우, 1번 커튼 up 모터 작동
        sv1_up.write(is_not_checked);                // 각도 0도
        delay(wait);                     
        sensor = analogRead(A0);        // 조도센서 값 재입력;
        }
    }
    
    
    // 반암막 1 down
    if(sensor > 242){         // 조도 값 242 이상, 2번 커튼의 down 모터 작동
      sv2_down.write(is_checked);    // 각도 10도
      delay(wait);            

      while(sensor >= 242 && sensor <= 352){    // 조도 값이 352 >= x >= 242일 경우, 2번 커튼 down 모터 작동
        sv2_down.write(is_not_checked);              // 각도 0도
        delay(wait);                    
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }
    
    // 암막 1 down
    if(sensor > 131){        // 조도 값 131 이상, 1번 커튼의 down 모터 작동
      sv1_down.write(is_checked);  // 각도 10도
      delay(wait);          

      while(sensor >= 131 && sensor <= 241){     // 조도 값이 241 >= x >= 131일 경우, 1번 커튼 down 모터 작동
        sv1_down.write(is_not_checked);              // 각도 0도
        delay(wait);                   
        sensor = analogRead(A0);        // 조도센서 값 재입력
        }
    }
    
    // 낮, 2 down
    if(sensor > 20){          // 조도 값 20 이상, 1-2번 커튼의 down 모터 작동
      sv1_down.write(is_checked);    // 각도 10도
      sv2_down.write(is_checked);    // 각도 10도
      delay(wait);            

      while(sensor >= 20 && sensor <= 130){    // 조도 값이 130 >= x >= 20일 경우, 1-2번 커튼 down 모터 작동
        sv1_down.write(is_not_checked);           // 각도 0도
        sv2_down.write(is_not_checked);           // 각도 0도
        delay(wait);                
        sensor = analogRead(A0);     // 조도센서 값 재입력
        }
    }  
}
