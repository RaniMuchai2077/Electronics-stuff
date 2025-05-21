/*
  74HC595 Shift Register with 7-segment LED display
  74hc595-7segdisplay.ino
  Traffic light system with LEDS &  displaying 0-9 count on 7-segment Common Cathode LED display 


*/

// Define Connections to 74HC595

// DS pin 14
const int dataPin = 2;
// ST_CP pin 12
const int latchPin = 3;
// SH_CP pin 11
const int clockPin = 4;

//timing
unsigned long startTime;
int interval = 1000;
int num =0;
//Traffic lights
int red =8;
int amber =9;
int green =10;
int i =0;
unsigned long trafficStartTime;
int trafficInterval =10000;


// Patterns for characters 0,1,2,3,4,5,6,7,8,9
//0-9
int datArray[10] = {B0111111, B0000110, B11011011, B1001111, B1100110, B1101101, B1111101, B0000111, B1111111, B1101111};

//  9-0
int datArrayAsc[10] = {B1101111,  B1111111, B0000111, B1111101, B1101101, B1100110,  B1001111,  B11011011, B0000110, B0111111};

void setup ()
{
  // Setup pins as Outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //traffic lights as OUTPUTS
  pinMode(red, OUTPUT);
  pinMode(amber, OUTPUT);
  pinMode(green, OUTPUT);
  switch_lights(i);
}
void loop()
{
  //7-SEG Timer functions 
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;

//Traffic lights timer function
 unsigned long T_current = millis();
 unsigned long T_elapsed = T_current -trafficStartTime;

//switch lights in 10 second intervals
 if(T_elapsed >= trafficInterval){ 
  trafficStartTime = T_current;
    
    //function call
    switch_lights(i);
    i+= 1;
      if(i>=3){
        i=0;
        }
 }

//display counter using 7-seg display in 1 second intervals
  if(elapsedTime >= interval){
    
    startTime = currentTime;
     

    digitalWrite(latchPin, LOW);

    shiftOut(dataPin, clockPin, MSBFIRST, datArrayAsc[num]);

    digitalWrite(latchPin, HIGH);

    num+=1;
    if(num>=10){num =0;
    }


  }
  


  }


// function to switch between traffic lights
 void switch_lights(int i){
  digitalWrite(red, LOW);
  digitalWrite(amber, LOW);
  digitalWrite(green, LOW);
  switch(i){
    case 0:
      digitalWrite(red, HIGH);
      digitalWrite(amber, LOW);
      digitalWrite(green, LOW);
      break;
    case 1:
      digitalWrite(red,LOW);
      digitalWrite(amber, HIGH);
      digitalWrite(green, LOW);
      break;

    case 2:
      digitalWrite(red, LOW);
      digitalWrite(amber, LOW);
      digitalWrite(green, HIGH);
      break;


  }
 }
