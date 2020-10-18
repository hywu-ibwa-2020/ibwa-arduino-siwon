#include <SoftwareSerial.h>
#include <Servo.h>

Servo sv1_up;
Servo sv2_up;

// 서보모터 각도값 변수
int is_checked = 10;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값(10초)
int wait = 5000;

int sensorValue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  sv1_up.attach(22);    // 서보모터 핀넘버
//  sv1_down.attach(23);
  sv2_up.attach(24);
//  sv2_down.attach(25);

  sv1_up.write(0);        // 서보모터 각도 초기화
//  sv1_down.write(0);
  sv2_up.write(0);
//  sv2_down.write(0);
  
  Serial.println("input");
}

void loop() {
  // put your main code here, to run repeatedly:
  mainCdsServo();
}

void mainCdsServo(){
    if(Serial1.available()){
      char mainBtn = Serial1.read();
      // 암막 up
      if(mainBtn == '1'){
        sv1_up.write(is_checked);
        delay(wait);
        sv1_up.write(is_not_checked);
      } else if(mainBtn == '3'){   // 반암막 up
            sv2_up.write(is_checked);
            delay(wait);
            sv2_up.write(is_not_checked);
          } else if(mainBtn == '2'){      // 조도센서
              int sensor = analogRead(A0);
              if(sensor >= 500){
                Serial.println("Red");
                }else {
                  Serial.println("blue");
                  }
        }
    }
  
}
