#include <LedControl.h>



LedControl lc = LedControl(12,11,10,4);


unsigned long delayTime = 1;

int secRate = 1000;

// int button_[4] = {4,5,6,7};

bool debugBool = true;

void setup(){
  for (int i = 0; i < 4; i++){
      lc.shutdown(i,false);
      lc.setIntensity(i,1);
      lc.clearDisplay(i);
  }

//   for(int i = 0; i < sizeof(button_); i++){
//     pinMode(button_[i],INPUT_PULLUP);
//   }


}

void loop(){

    if(secRate > 0){
        secRate--;
    }else{
        secRate = 1000;
        debugBool = !debugBool;
    }

    lc.setLed(3,0,0,debugBool);


    delay(delayTime);

}
