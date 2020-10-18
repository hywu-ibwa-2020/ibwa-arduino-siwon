#include <SoftwareSerial.h>
#include <Servo.h>

Servo sv1_up, sv2_up;
//Servo sv1_down, sv2_down;

// 서보모터 각도값 변수
int is_checked = 10;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 500;
//int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  sv1_up.attach(22);    // 서보모터 핀넘버
//  sv1_down.attach(23);
  sv2_up.attach(26);
//  sv2_down.attach(25);

  sv1_up.write(0);        // 서보모터 각도 초기화
//  sv1_down.write(0);
  sv2_up.write(0);
//  sv2_down.write(0);
  
  Serial1.println("input");
}

void loop() {
  // put your main code here, to run repeatedly:
  operateMotorsCds();
}

void operateMotorsCds(){
    if(Serial1.available()){
      delay(100); // 모든 데이터 수신완료 될 때까지 대기
      String mainBtn = Serial1.readStringUntil('\n');
      
      // 암막 up
      if(mainBtn == "커일업"){
        sv1_up.write(is_checked);
        delay(wait);
        sv1_up.write(is_not_checked);
      } else if(mainBtn == "커이업"){   // 반암막 up
            sv2_up.write(is_checked);
            delay(wait);
            sv2_up.write(is_not_checked);       
          } else if(mainBtn == "조도줘"){    // 하단 조도 버튼 누를 때
              int sensor = analogRead(A0);
              if(sensor >= 500){    // 조도 값이 500 이상이면 기기에 Blue 값 전송
                Serial1.println("Blue");
                }else {   // 조도 값이 500 미만이면 기기에 Red 값 전송
                  Serial1.println("Red");
                  }          
        }
  }
}
