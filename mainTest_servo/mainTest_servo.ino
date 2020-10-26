#include <SoftwareSerial.h>
#include <Servo.h>

Servo sv1_up, sv2_up;
Servo sv1_down, sv2_down;

// 서보모터 각도값 변수
int is_checked = 30;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 500;

// millis 관련 변수
unsigned long previousMillis = 0; // 현재 시간 저장
unsigned long currentMillis;
long sv1_up_interval = 5000; // 커튼1, 1초간 onClick
long sv1_down_interval = 5000; // 커튼1, 2초간 onClick
long sv2_up_interval = 5000; // 커튼2, 3초간 onClick
long sv2_down_interval = 5000; // 커튼2, 4초간 onClick
String mainBtn, cur1up, cur2up, cur1down, cur2down, cur12up, cur12down;

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

//void loop() {
//  // put your main code here, to run repeatedly:
//
//  operateMotorsCds();
//  
//}

void loop(){
//  if(Serial1.available() == 0){
      mainBtn = Serial1.readStringUntil('\n');
      cur1up = "c1up";
      cur2up = "c2up";
      cur1down = "c1down";
      cur2down = "c2down";
      cur12up = "c12up";
      cur12down = "c12down";

      currentMillis = millis(); //현재 시간 측정

      // 서보모터 is_checked 각도로 움직이기
      if(mainBtn == cur1up){  // 커일업
        sv1_up.write(is_checked);
        previousMillis = currentMillis;
      } 
        if(mainBtn == cur2up){     // 커이업
          previousMillis = currentMillis;
          sv2_up.write(is_checked);   
        } 
        if(mainBtn == cur1down){   // 커일단
          previousMillis = currentMillis;
          sv1_down.write(is_checked);     
        } 
        if(mainBtn == cur2down){   // 커이단
          previousMillis = currentMillis;
          sv2_down.write(is_checked);
        }
        if(mainBtn == cur12up){    // 커일이업
          previousMillis = currentMillis;
          sv1_up.write(is_checked);
          sv2_up.write(is_checked);      
        } 
        if(mainBtn == cur12down){   // 커일이단
          previousMillis = currentMillis;
          sv1_down.write(is_checked);
          sv2_down.write(is_checked);     
        }
//  }
      // is_checked 후 interval 시간차에 따라 is_not_checked 각도 이동
      if(currentMillis - previousMillis > sv1_up_interval){
        sv1_up.write(is_not_checked);
        }
        if(currentMillis - previousMillis > sv1_down_interval){
        sv1_down.write(is_not_checked);
        }
        if(currentMillis - previousMillis > sv2_up_interval){
        sv2_up.write(is_not_checked);
        }
        if(currentMillis - previousMillis > sv2_down_interval){
        sv2_down.write(is_not_checked);
        }
  
  }