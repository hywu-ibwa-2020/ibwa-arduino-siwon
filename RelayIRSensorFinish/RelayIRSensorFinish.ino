#include <SoftwareSerial.h>
#define HalfDN 3  // 반암막 ir센서 
#define HalfUP 4
#define ScreenDN 6  // 암막
#define ScreenUP 7  // 암막
#define IN1 50   // 반암막 IN1 DOWN
#define IN2 51   // 반암막 IN2 UP 
#define IN3 52
#define IN4 53

// 디폴트가 ON = LOW
// 감지 0, 미감지 1
// in2이 on이면 내리기 = LOW, in1이 on = low면 올리기
// 짝수 LOW면 ON - 내리기, 홀수 LOW면 ON - 올리기
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(HalfDN, INPUT);
  pinMode(HalfUP, INPUT);
  pinMode(ScreenDN, INPUT);
  pinMode(ScreenUP, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop(){
  
  String input;
  String n = ""+'\n';
  if(Serial.available()) {
    Serial.println("--------------------------------------------");
    input = Serial.readStringUntil('\n');
    Serial.println("입력된 input: " + input);
    String data = input.substring(0, 1);
    Serial.println("정제된 데이터: " + data);
    Serial.println("--------------------------------------------");
    if (data == "m") {                             // 분위기별 맞춤 추천 기능
      Serial.println("<< 분위기별 맞춤 추천 기능 >>");
      operateRemoteCtrl(input);
    }
  
}
}


void operateRemoteCtrl(String input){
  Serial.println("m01. 혼술하기 딱 좋은: DN - UP");
  while(true){
     if(input == "m01"){
      // 암막-반암막 전부 내려온 상태에서 암막만 올리기 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("half = 0, screen = 0: 암막만 올리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("half = 1, screen = 1: 암막 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end

        // 전부 올라간 상태에서 반암막만 내리기 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("전부 올라간 상태에서 반암막만 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("반암막 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end

        // DN-UP 그대로 유지 // half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("DN-UP 그대로 유지");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
//              Serial.println("반암막 내리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            } // 유지하기 때문에 NO?
        } // 1 end

        // 반암막 내리고 암막 올리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("반암막 내리고 암막 올리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("반암막 내리고 암막 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m01 end


        // m02. 기분전환이 필요해
        if(input == "m02"){
        Serial.println("m02. 기분전환이 필요해: UP - UP");
        // 암막-반암막 전부 내려온 상태에서 암막만 올리기 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("half = 0, screen = 0: 둘 다 올리기");
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("half = 1, screen = 1: 둘 다 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end

        // 그대로 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("그대로");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
//              Serial.println("반암막 내리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            } // 그대로 유지
        } // 1 end

        // 반암막만 올리기 // half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("반암막만 올리기");
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("반암막 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 
        } // 1 end

        // 암막만 올리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("암막만 올리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("암막만 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m02 end



        // m03. 캠프파이어
        if(input == "m03"){
        Serial.println("m03. 캠프파이어: DN - DN");
        
        // 그대로 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("half = 0, screen = 0: 그대로");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
//              Serial.println("half = 1, screen = 1: 암막 올리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            }
        } // 1 end

        // 둘 다 내리기 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("둘 다 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("둘 다 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 둘 다 내리기
        } // 1 end

        // 암막만 내리기 // half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("암막만 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 
        } // 1 end

        // 반암막만 내리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("반암막만 내리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("반암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m03 end


      // m04. 위로받고 싶을 때
      if(input == "m04"){
        Serial.println("m04. 위로받고 싶을 때: UP - UP");

        // 둘 다 올리기 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("half = 0, screen = 0: 둘 다 올리기");
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP))
              Serial.println("둘 다 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end


        // 그대로 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("그대로");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
//              Serial.println("둘 다 내리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            } // 둘 다 내리기
        } // 1 end

        // 반암막만 올리기 half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("반암막만 올리기");
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("반암막만 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 
        } // 1 end

        // 암막만 올리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("암막만 올리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, LOW); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("암막만 올리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m04 end



      // m05. 스터디 집중모드
      if(input == "m05"){
        Serial.println("m05. 스터디 집중모드: DN - DN");
        
        
        // 그대로 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("half = 0, screen = 0: 둘 다 그대로");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
//              Serial.println("둘 다 올리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            }
        } // 1 end


        // 둘 다 내리기 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("둘 다 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("둘 다 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 둘 다 내리기
        } // 1 end

        // 암막만 내리기 half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
          Serial.println("암막만 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){
              Serial.println("암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 
        } // 1 end

        // 반암막만 내리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("반암막만 내리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("반암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m05 end



        // m06. 피톤치드 뿜뿜
        if(input == "m06"){
          Serial.println("m06. 피톤치드 뿜뿜: DN - DN");


        // 그대로 half = 0, screen = 0
        if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("half = 0, screen = 0: 둘 다 그대로");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, HIGH);
          while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
//              Serial.println("둘 다 올리기 중단");
//              digitalWrite(IN1, HIGH);
//              digitalWrite(IN2, HIGH);
//              digitalWrite(IN3, HIGH);
//              digitalWrite(IN4, HIGH);
//                while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
//            }
        } // 1 end


        // 둘 다 내리기 half = 1, screen = 1
        if(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("둘 다 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("둘 다 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 둘 다 내리기
        } // 1 end

        // 암막만 내리기 half = 0, screen = 1
        if(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("암막만 내리기");
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          while(!digitalRead(HalfDN) && digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            } // 
        } // 1 end

        // 반암막만 내리기 half = 1, screen = 0
        if(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
          Serial.println("반암막만 내리기");
          digitalWrite(IN1, HIGH); // 반암막
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, HIGH); // 암막
          digitalWrite(IN4, HIGH);
          while(digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            if(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP)){ 
              Serial.println("반암막만 내리기 중단");
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, HIGH);
              digitalWrite(IN3, HIGH);
              digitalWrite(IN4, HIGH);
                while(!digitalRead(HalfDN) && !digitalRead(ScreenDN) && !digitalRead(HalfUP) && !digitalRead(ScreenUP));
            }
        } // 1 end
        } // m06 end
//     } // while end
     
} // void end
