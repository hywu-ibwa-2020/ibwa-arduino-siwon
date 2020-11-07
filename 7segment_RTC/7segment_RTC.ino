#include "TM1637.h" 

#define CLK 24//Pins for TM1637        
#define DIO 2

TM1637 tm1637(CLK,DIO); 

// Date and time functions using a DS3231 RTC connected via I2C and Wire lib 

#include <Wire.h> 
#include "RTClib.h" 
RTC_DS3231 rtc; 

int hh, mm;  


void setup() 
  { 
    tm1637.init(); 
    tm1637.set(5);  
    //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7; 

    rtc.begin(); 
    // manual adjust 
    // January 21, 2014 at 3am you would call: 
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); 
    // automatic adjust 
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  }//end "setup()" 

    

void loop(){ 
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
  
  }// end loop()
