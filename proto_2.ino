#include <LedControl.h>



LedControl lc = LedControl(12,11,10,4);

bool deAngka [10][15] = {
    {
        1,1,1,
        1,0,1,
        1,0,1,
        1,0,1,
        1,1,1  
    },
    {
        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1  
    },
    {
        1,1,1,
        0,0,1,
        1,1,1,
        1,0,0,
        1,1,1  
    },
    {
        1,1,1,
        0,0,1,
        1,1,1,
        0,0,1,
        1,1,1  
    },
    {
        1,0,1,
        1,0,1,
        1,1,1,
        0,0,1,
        0,0,1  
    },
    {
        1,1,1,
        1,0,0,
        1,1,1,
        0,0,1,
        1,1,1  
    },
    {
        1,1,1,
        1,0,0,
        1,1,1,
        1,0,1,
        1,1,1  
    },
    {
        1,1,1,
        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1  
    },
    {
        1,1,1,
        1,0,1,
        1,1,1,
        1,0,1,
        1,1,1  
    },
    {
        1,1,1,
        1,0,1,
        1,1,1,
        0,0,1,
        0,0,1  
    }
};

//jam
uint8_t sec = 40; 
uint8_t minute = 23; 
uint8_t hour = 22;
 
//date
uint8_t day = 9; 
uint8_t month = 6; 
uint8_t year = 21;
 
uint8_t flag = 1;
bool date = false;

uint8_t dig1; uint8_t dig2; uint8_t dig3; uint8_t dig4; uint8_t dig5; uint8_t dig6;


unsigned long delayTime = 1;

uint8_t secRate = 10;

uint8_t button_[4] = {4,5,6,7};
bool lastButtonState[4];
bool currentButtonState[4];

bool debugBool = 1;

int debugInt = 0;
// int diz = 0;
// int xoz = 0;

void setup(){
  for (int i = 0; i < 4; i++){
      lc.shutdown(i,false);
      lc.setIntensity(i,1);
      lc.clearDisplay(i);
  }

  for(int i = 0; i < sizeof(button_); i++){
    pinMode(button_[i],INPUT_PULLUP);

    currentButtonState[i] =digitalRead(button_[i]);
  }


}

void loop(){
  for(int i = 0; i < sizeof(lastButtonState); i++){
    lastButtonState[i] = currentButtonState[i];
    currentButtonState[i] = digitalRead(button_[i]);
  }

  if(lastButtonState[0] == HIGH && currentButtonState[0] == LOW){
    date = !date;
  }


  if(digitalRead(button_[0]) == LOW){
    lc.setLed(3,0,0,true);
  }else{
    lc.setLed(3,0,0,false);
    // date = false;
  }
  
  
  Time2DigConvert();
  DisplayDig();

  if(secRate > 0){
    secRate--;
  }else{
    secRate = 10;
    debugBool = !debugBool;
    TimeFlow();
  }

  lc.setLed(3,0,1,debugBool);
  lc.setLed(3,0,2,date);

  // diz = debugInt / 8;
  // xoz = debugInt % 8;
  
  // lc.setLed(3-debugInt/8,1,debugInt % 8,true);

  // if(debugInt < 32){
  //   debugInt++;
  // }else{
  //   debugInt = 0;
  //   for(int i = 0; i < 8; i++){
  //     lc.setLed(0,1,i,false);
  //     lc.setLed(1,1,i,false);
  //     lc.setLed(2,1,i,false);
  //     lc.setLed(3,1,i,false);
  //   }
  // }

  delay(delayTime);

}


void Time2DigConvert(){
  if(date){
    dig1 = (day/10)%10;
    dig2 = day%10;
    dig3 = (month/10)%10;
    dig4 = month%10;
    dig5 = (year/10)%10;
    dig6 = year%10;
  }else{
    dig1 = (hour/10)%10;
    dig2 = hour%10;
    dig3 = (minute/10)%10;
    dig4 = minute%10;
    dig5 = (sec/10)%10;
    dig6 = sec%10;
  }
}

void DisplayDig(){
  printKeyDyna(5,2,dig1,deAngka);
  printKeyDyna(9,2,dig2,deAngka);
  
  printKeyDyna(15,2,dig3,deAngka);
  printKeyDyna(19,2,dig4,deAngka);

  printKeyDyna(25,2,dig5,deAngka);
  printKeyDyna(29,2,dig6,deAngka);
}

void TimeFlow(){
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

void printKeyOffset( int deviceIndex, int xoff, int yoff,int keyIndex, bool keyGroup[][15]){
    int con = 0;

    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 3; i++){
            if(keyGroup[keyIndex][con] == 0){
                lc.setLed(deviceIndex,j+yoff,i+xoff, false);
            }else{
                lc.setLed(deviceIndex,j+yoff,i+xoff, true);
            }

            con++;
        }
    }

}

void printKeyDyna(int xoff, int yoff, int keyIndex, bool keyGroup[][15]){
  int con = 0;

  for(int j = 0; j < 5; j++){
    for(int i = 0; i < 3; i++){

      lc.setLed(3-((i+xoff)/8),j+yoff,(i+xoff) % 8,keyGroup[keyIndex][con]);

      con++;
    }
  }
}

