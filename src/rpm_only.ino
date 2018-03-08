#include <LedControl.h>

// inputs: DIN pin, CLK pin, LOAD pin. number of chips
LedControl mydisplay = LedControl(12, 10, 11, 1);

//RPM--------------------------------------------------------------
//Configuration for the Tachometer variables
const int sensorPin = 2;
const int sensorInterrupt = 0;
volatile unsigned long lastPulseTime;
volatile unsigned long interval = 0;
//volatile int timeoutCounter;

int rpm;
int rpmlast = 3000;
//----------------------------------------------------------------

void setup(void) { 
  mydisplay.shutdown(0, false);  // turns on display
  mydisplay.setIntensity(0, 8); // 15 = brightest
  printTrueno();  //prints my car's name
  delay(3000);
  initToZero();
   
  //Config for the Tach
  pinMode(sensorPin, INPUT);
  attachInterrupt(sensorInterrupt, &sensorIsr, RISING);
  lastPulseTime = 0;
  //timeoutCounter = 0;
}
 
void loop() { 
  //RPM--------------------------------------------------------------
  if(rpm >= 0) {  //Remove the error readings of minus values   
    
    //Let's keep this RPM value under control, between 0 and 9999
    rpm = constrain (rpm, 0, 9999);

    //If the engine is not running, print 0
    if ((micros() - lastPulseTime) < 5e6 ) {
      rpm = rpm;
    }
    else {
      rpm = 0;
    }
    
    if (rpm < 250)
      rpm = 0;

    printNumber(rpm, 1);
  }
  //-----------------------------------------------------------------
}

//Each time the interrupt receives a rising tach signal, it'll run this subroutine
void sensorIsr() {
  unsigned long now = micros();
  interval = now - lastPulseTime;
  if (interval > 5000){
     rpm = 61000000UL/(interval * 2);
     lastPulseTime = now;
  }
}

void printNumber(int v, int flag) {
    int ones;
    int tens;
    int hundreds;
    int thousands;
    
    if (flag==0){  // display speed
      ones = v%10;
      v = v/10;
      tens = v%10;
      v= v/10;
      hundreds = v;
     
      //Now print the number digit by digit
      if (hundreds>0)
        mydisplay.setDigit(0,0,(byte)hundreds,false);
      else
        mydisplay.setChar(0,0,' ',false);
        
      mydisplay.setDigit(0,1,(byte)tens,false);       
      mydisplay.setDigit(0,2,(byte)ones,false);
    }
    else if (flag=1) {  // display RPM
      ones = v%10;
      v = v/10;
      tens = v%10;
      v = v/10;
      hundreds = v%10;
      v = v/10;
      thousands = v%10;

      //Now print the number digit by digit
      mydisplay.setDigit(0,4,(byte)thousands,false);
      mydisplay.setDigit(0,5,(byte)hundreds,false);
      mydisplay.setDigit(0,6,(byte)tens,false);
      mydisplay.setDigit(0,7,(byte)ones,false);
    }
}

void printTrueno(){
  mydisplay.setLed(0,0,7,true);
  
  //Display 't'
  mydisplay.setLed(0,1,4,true);
  mydisplay.setLed(0,1,5,true);
  mydisplay.setLed(0,1,6,true);
  mydisplay.setLed(0,1,7,true);
  
  //Display 'r'
  mydisplay.setLed(0,2,5,true);
  mydisplay.setLed(0,2,6,true);
  mydisplay.setLed(0,2,7,true);
  
  //Display 'u'
  mydisplay.setLed(0,3,2,true);
  mydisplay.setLed(0,3,3,true);
  mydisplay.setLed(0,3,4,true);
  mydisplay.setLed(0,3,5,true);
  mydisplay.setLed(0,3,6,true);
  
  //Display 'e'
  mydisplay.setLed(0,4,1,true);
  mydisplay.setLed(0,4,2,true);
  mydisplay.setLed(0,4,4,true);
  mydisplay.setLed(0,4,5,true);
  mydisplay.setLed(0,4,6,true);
  mydisplay.setLed(0,4,7,true);
  
  //Display 'n'
  mydisplay.setLed(0,5,1,true);
  mydisplay.setLed(0,5,2,true);
  mydisplay.setLed(0,5,3,true);
  mydisplay.setLed(0,5,5,true);
  mydisplay.setLed(0,5,6,true);
  
  //Display 'o'
  mydisplay.setLed(0,6,1,true);
  mydisplay.setLed(0,6,2,true);
  mydisplay.setLed(0,6,3,true);
  mydisplay.setLed(0,6,4,true);
  mydisplay.setLed(0,6,5,true);
  mydisplay.setLed(0,6,6,true);
  
  mydisplay.setLed(0,7,7,true);
}

void initToZero(){
  mydisplay.setDigit(0,0,0,false);
  mydisplay.setDigit(0,1,0,false);
  mydisplay.setDigit(0,2,0,false);
  mydisplay.setChar(0,3,' ',false);
  mydisplay.setDigit(0,4,0,false);
  mydisplay.setDigit(0,5,0,false);
  mydisplay.setDigit(0,6,0,false);
  mydisplay.setDigit(0,7,0,false);
}
