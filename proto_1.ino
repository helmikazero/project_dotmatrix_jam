#include <LedControl.h>



LedControl lc = LedControl(12,11,10,4);

bool dePointer [5][32] = {
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1
  },
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0
  },
  {
    0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  },
  {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
  },
};


bool deAngka [12][15] = {
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
    },
    {
        0,0,0,
        0,1,0,
        0,0,0,
        0,1,0,
        0,0,0  
    },
    {
        0,0,0,
        0,0,0,
        1,1,1,
        0,0,0,
        0,0,0  
    }
};

// CHANGE MODE
uint8_t changeHoldThreshold = 10;
uint8_t changeHold = 0;
bool changeMode = false;
uint8_t pointerLoc = 0;


//jam
uint8_t sec = 0; 
uint8_t minute = 23; 
uint8_t hour = 22;
 
//date
uint8_t day = 9; 
uint8_t month = 6; 
uint8_t year = 21;

 
uint8_t flag = 1;
bool date = false;

uint8_t dig1; uint8_t dig2; uint8_t dig3; uint8_t dig4; uint8_t dig5; uint8_t dig6;

uint8_t jamdig[6];
uint8_t tgldig[6];


unsigned long delayTime = 1;

uint8_t secRate = 7;

uint8_t button_[4] = {4,5,6,7};
bool lastButtonState[4];
bool currentButtonState[4];

bool debugBool = 1;

int debugInt = 0;

uint8_t jam_x_pos[2] = {2,2};
uint8_t tgl_x_pos[2] = {32,32};

//DELAY SELANG SELING JAM - TANGGAL
uint8_t cleanStartSec = 10;

uint8_t showDateTime[2] = {5,5};

uint8_t showHourTime[2] = {15,15};

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

  if(digitalRead(button_[0]) == LOW){
    lc.setLed(3,0,0,true);
    changeHold++;
    if(changeHold >= changeHoldThreshold){
      printPointerDyna(0,7,32,1,pointerLoc,dePointer);
      printPointerDyna(0,7,32,1,3,dePointer);
    }
  }else{
    lc.setLed(3,0,0,false);
    if(changeHold >= changeHoldThreshold){
        changeMode = !changeMode;
    }else if(changeHold > 0 && changeHold < changeHoldThreshold){
      date = !date;
      ClearAllDisplay();
    }
    changeHold = 0;
  }

  

  if(changeMode){
    if(lastButtonState[1] == HIGH && currentButtonState[1] == LOW){
      pointerLoc++;
      if(pointerLoc >= 3){
        pointerLoc = 0;
      }
    }

    if(lastButtonState[2] == HIGH && currentButtonState[2] == LOW){
      switch(pointerLoc){
        case 0:
          if(date){
            year++;
          }else{
            sec++;
          }
          break;
        case 1:
          if(date){
            month++;
          }else{
            minute++;
          }
          break;
        case 2:
          if(date){
            day++;
          }else{
            hour++;
          }
          break;
      }
    }

    if(lastButtonState[3] == HIGH && currentButtonState[3] == LOW){
      switch(pointerLoc){
        case 0:
          if(date){
            year--;
          }else{
            sec--;
          }
          break;
        case 1:
          if(date){
            month--;
          }else{
            minute--;
          }
          break;
        case 2:
          if(date){
            day--;
          }else{
            hour--;
          }
          break;
      }
    }

    printPointerDyna(0,7,32,1,pointerLoc,dePointer);
  }else{
    printPointerDyna(0,7,32,1,3,dePointer);
  }
  
  TimeFlow();
  Time2DigConvert();

  
  if(date){
    DisplayDig(1,2,tgldig,11);
  }else{
    DisplayDig(1,2,jamdig,10);
  }

  if(secRate > 0){
    secRate--;
    lc.setLed(3-(secRate+12)/8,0,(secRate+12)%8,debugBool);
  }else{
    secRate = 7;
    sec = sec+1;

    if(!changeMode){
      if(sec >= cleanStartSec){
        if(sec == 10){
          date = true;
        }
        if(!date){
          if(showHourTime[0] > 0){
            showHourTime[0]--;
          }else{
            showHourTime[0] = showHourTime[1];
            date = true;
            ClearAllDisplay();
          }
        }else{
          if(showDateTime[0] > 0){
            showDateTime[0]--;
          }else{
            showDateTime[0] = showDateTime[1];
            date = false;
            ClearAllDisplay();
          }
        }
      }else{
        date = false;
      }
    }

    debugBool = !debugBool;
    
  }


  delay(delayTime);

}

void ClearAllDisplay(){
  lc.clearDisplay(0);
  lc.clearDisplay(1);
  lc.clearDisplay(2);
  lc.clearDisplay(3);
}

void Time2DigConvert(){


  jamdig[0] = (hour/10)%10;
  jamdig[1] = hour%10;
  jamdig[2] = (minute/10)%10;
  jamdig[3] = minute%10;
  jamdig[4] = (sec/10)%10;
  jamdig[5] = sec%10;

  tgldig[0] = (day/10)%10;
  tgldig[1] = day%10;
  tgldig[2] = (month/10)%10;
  tgldig[3] = month%10;
  tgldig[4] = (year/10)%10;
  tgldig[5] = year%10;

}



void DisplayDig(uint8_t xl, uint8_t yl, uint8_t digMode[], uint8_t indenForm){
  printKeyDyna(xl,yl,3,5,digMode[0],deAngka);
  printKeyDyna(xl+4,yl,3,5,digMode[1],deAngka); //4
  
  printKeyDyna(xl+8,yl,3,5,indenForm,deAngka);

  printKeyDyna(xl+12,yl,3,5,digMode[2],deAngka); //10
  printKeyDyna(xl+16,yl,3,5,digMode[3],deAngka); //14

  printKeyDyna(xl+20,yl,3,5,indenForm,deAngka);

  printKeyDyna(xl+24,yl,3,5,digMode[4],deAngka); //20
  printKeyDyna(xl+28,yl,3,5,digMode[5],deAngka); //24
}


void TimeFlow(){
  
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

void printKeyDyna(int xoff, int yoff, uint8_t format_i,uint8_t format_j, int keyIndex, bool keyGroup[][15]){
  int con = 0;

  for(int j = 0; j < format_j; j++){
    for(int i = 0; i <  format_i; i++){

      lc.setLed(3-((i+xoff)/8),j+yoff,(i+xoff) % 8,keyGroup[keyIndex][con]);

      con++;
    }
  }
}

void printPointerDyna(int xoff, int yoff, uint8_t format_i,uint8_t format_j, int keyIndex, bool keyGroup[][32]){
  int con = 0;

  for(int j = 0; j < format_j; j++){
    for(int i = 0; i <  format_i; i++){

      lc.setLed(3-((i+xoff)/8),j+yoff,(i+xoff) % 8,keyGroup[keyIndex][con]);

      con++;
    }
  }
}

