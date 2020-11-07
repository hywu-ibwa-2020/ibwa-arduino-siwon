#include <SoftwareSerial.h>
#include <Servo.h>
Servo svMotor;
String mainBtn;

// 서보모터 각도값 변수
int is_checked = 30;    // 버튼 클릭시 서보모터 10도 작동
int is_not_checked = 0; // 버튼 클릭 안했을 떄 서보모터 0도 작동

// 서보모터 delay 시간 값
int wait = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);

  svMotor.attach(22);
  svMotor.write(0);

  Serial.println("input");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    mainBtn = Serial1.readStringUntil('\n');
    if(mainBtn == "c1up"){
      svMotor.write(is_checked);
      delay(wait);
      svMotor.write(is_not_checked);
      }
    }
}
