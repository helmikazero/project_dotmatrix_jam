#include "LedControl.h"
LedControl lc = LedControl(12,11,10,1);
unsigned long delaytime=500;
 
//jam
uint8_t sec = 50; 
uint8_t minute = 59; 
uint8_t hour = 23;
 
//date
uint8_t day = 31; 
uint8_t month = 12; 
uint8_t year = 20;
 
uint8_t flag = 1;
bool date = false;
 
int Digits[10]={B01111110, B00110000, B01101101, B01111001,
               B00110011, B01011011, B01011111, B01110000,
               B01111111, B01111011};
int dig1; int dig2; int dig3; int dig4; int dig5; int dig6;
 
void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), buttonPressed, FALLING);
}
 
void buttonPressed()
{
    date = !date;
}
 
void loop() { 
  if(date){
    dig1 = (day/10)%10;
    dig2 = day%10;
    dig3 = (month/10)%10;
    dig4 = month%10;
    dig5 = (year/10)%10;
    dig6 = year%10;
    lc.setRow(0,0,Digits[dig1]);
    lc.setRow(0,1,Digits[dig2]);
    lc.setChar(0,2,'-',true);
    lc.setRow(0,3,Digits[dig3]);
    lc.setRow(0,4,Digits[dig4]);
    lc.setChar(0,5,'-',true);
    lc.setRow(0,6,Digits[dig5]);
    lc.setRow(0,7,Digits[dig6]);
  }else{
    dig1 = (hour/10)%10;
    dig2 = hour%10;
    dig3 = (minute/10)%10;
    dig4 = minute%10;
    dig5 = (sec/10)%10;
    dig6 = sec%10;
    lc.setRow(0,0,Digits[dig1]);
    lc.setRow(0,1,Digits[dig2]);
    lc.setChar(0,2,' ',false);
    lc.setRow(0,3,Digits[dig3]);
    lc.setRow(0,4,Digits[dig4]);
    lc.setChar(0,5,' ',false);
    lc.setRow(0,6,Digits[dig5]);
    lc.setRow(0,7,Digits[dig6]);
  }
 

    delay(delaytime);
    sec = sec+1;
    if(sec>59){
      sec = 0; minute = minute +1;
    }
    if(minute>59){
      minute = 0; hour = hour+1;
    }
    if(hour>23){
      hour = 0; minute = 0; sec = 0;
      day++;
    }
    switch(month){
      case 1:
        if(day >31){
          day = 1;
          month++;
        }
        break;
      case 2:
        if(year%4 == 0){
          if(day > 29){
            day = 1;
            month++;
          }
        }else{
          if(day > 28){
            day = 1;
            month++;
          }
        }
        break;
      case 3:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
      case 4:
        if(day > 30){
          day = 1;
          month++;
        }
        break;
      case 5:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
      case 6:
        if(day > 30){
          day = 1;
          month++;
        }
        break;
      case 7:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
      case 8:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
      case 9:
        if(day > 30){
          day = 1;
          month++;
        }
        break;
      case 10:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
      case 11:
        if(day > 30){
          day = 1;
          month++;
        }
        break;
      case 12:
        if(day > 31){
          day = 1;
          month++;
        }
        break;
    }
 
    if(month > 12){
      month = 1;
      year++;
    }
 
}