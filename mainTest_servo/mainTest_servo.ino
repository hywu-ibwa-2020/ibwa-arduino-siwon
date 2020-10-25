#include <SoftwareSerial.h>
#include <Servo.h>

Servo sv1_up, sv2_up;
Servo sv1_down, sv2_down;

// 서보모터 각도값 변수
int is_checked = 180;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 500;
//int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  sv1_up.attach(22);    // 서보모터 핀넘버
  sv1_down.attach(23);
  sv2_up.attach(24);
  sv2_down.attach(25);

  sv1_up.write(0);        // 서보모터 각도 초기화
  sv1_down.write(0);
  sv2_up.write(0);
  sv2_down.write(0);
  
  Serial.println("input");
}

void loop() {
  // put your main code here, to run repeatedly:
  operateMotorsCds();
}

void operateMotorsCds(){
  
    if(Serial1.available()){
      String mainBtn = Serial1.readStringUntil('\n');
      String cur1up = "커일업";
      String cur2up = "커이업";
      String cur1down = "커일단";
      String cur2down = "커이단";
      String cur12up = "커일이업";
      String cur12down = "커일이단";
      
      
      // 커일업
      if(mainBtn == cur1up){
        sv1_up.write(is_checked);
        delay(wait);
        sv1_up.write(is_not_checked);
      } 
          else if(mainBtn == cur2up){   // 커이업
            sv2_up.write(is_checked);
            delay(wait);
            sv2_up.write(is_not_checked);      
          } 
          else if(mainBtn == cur1down){   // 커일단
            sv1_down.write(is_checked);
            delay(wait);
            sv1_down.write(is_not_checked);      
          } 
          else if(mainBtn == cur2down){   // 커이단
            sv2_down.write(is_checked);
            delay(wait);
            sv2_down.write(is_not_checked);      
          } 
          else if(mainBtn == cur12up){   // 커일이업
            sv1_up.write(is_checked);
            sv2_up.write(is_checked);
            delay(wait);
            sv1_up.write(is_not_checked);
            sv2_up.write(is_not_checked);      
          } 
          else if(mainBtn == cur12down){   // 커일이단
            sv1_down.write(is_checked);
            sv2_down.write(is_checked);
            delay(wait);
            sv1_down.write(is_not_checked);
            sv2_down.write(is_not_checked);      
          }  

  }
}
