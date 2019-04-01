/*
  Staircase timer

  This implementation is intendet 
  turns on the lights on the falling edge of input
  The elapsed time starts to count on the rising edge of the input

  A short low going pulse can be used to fire the timer as long Tw > 300ms
    
  
*/


#include "oled.h"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++
#define RETARDO 10      //Retardo del timer en segundos
// +++++++++++++++++++++++++++++++++++++++++++++++++++++

#define DEBUG_OFF  0
#define DEBUG_ON   1

#define debug DEBUG_ON


#define DEBUG_OFF  0
#define DEBUG_ON   1

#define debug DEBUG_ON

#define debug_message(fmt,...)          \
  do {              \
    if (debug)          \
       Serial.printf (fmt, ##__VA_ARGS__);     \
  } while(0)



#define RELAY D1            // Relay Pin
#define INPUT_STATUS D0     // This pin is connected to on board led to show the input status (Active low !!!)
#define PIR_INPUT D6        // This is the PIR input pin and it is used to trigger the timer
#define MAG_INPUT D7        // This is the Magnetic Switch input pin and it is used to trigger the timer

#define RISING 0
#define FALLING 1

#define EDGE_PIR RISING
#define EDGE_MAG FALLING
int estado;


long TimeSinceLastMeasure1 = 0;
long TimeSinceLastMeasure2 = 0;
int  TimerCount=0;

int Read_PIR_Input(void);
int Read_Magnetic_Switch(void);
void Update_oled(void);

void setup() {
 
  pinMode(RELAY, OUTPUT);
  pinMode(INPUT_STATUS, OUTPUT);
  pinMode(PIR_INPUT,INPUT_PULLUP);
  pinMode(MAG_INPUT,INPUT_PULLUP);
  estado=0;
  Serial.begin(115200);      // open the serial port at 115200 bps
  Oled_setup();
  
  pirtext(ON);
  magtext(ON);
  sun(ON);
  delay(1000); 
  pirtext(OFF);
  magtext(OFF);
  sun(OFF);

  
}


void loop() {

int temp;

    if (millis() - TimeSinceLastMeasure1 > 200 )   // Delay between measurements 200mseg.(for debonce)
    
    {   

        TimeSinceLastMeasure1 = millis();          // Update
        temp=Read_PIR_Input();
        temp|=Read_Magnetic_Switch();
        digitalWrite(INPUT_STATUS,!temp);       // Show input status (use onboard LED Active low !!!)
        Update_oled();                          // Show updated inputs (PIR & MAG)
    }


    if (TimerCount)                                   // if timer is in progress update counter until time is elapsed
    {
       
        
        if (millis() - TimeSinceLastMeasure2 > 1000 ) // 1 second (tick)
        {

             TimeSinceLastMeasure2 = millis();          // Update timer counter
             TimerCount--;
             print_count(TimerCount,D_SHOW);
             if(TimerCount==0){                          // timer elapsed?
                digitalWrite(RELAY,LOW);                  // if yes turn off lights
                sun(OFF);                                 // Also the sun icon
             }
        }
    }

   

}


int Read_PIR_Input(void)
{
  int lectura;
  static int last=RISING;
        
        lectura=!digitalRead(PIR_INPUT);            // Read input (invert since active low)
        
        //debug_message("\nstate:%d",estado);

        if (last==RISING && last!=lectura)  // if Rising(Leading) edge on input start timer
        {
    
          TimerCount=RETARDO;                              // Timer Delay in seconds
          digitalWrite(RELAY,HIGH);                     // Turn on lights
          sun(ON);                                     // Also the sun icon
          TimeSinceLastMeasure2 = millis();           // Update (Sync like output compare)
          print_count(TimerCount,D_SHOW);
        }
        
        last=lectura;                                 // Update button State

        if(lectura==1)                                // While input stays active freeze timer 
            TimerCount=RETARDO;                       // Timer Delay in seconds
  
  return(lectura); 
}

int Read_Magnetic_Switch(void)
{
  int lectura;
  static int last=RISING;
        
        lectura=digitalRead(MAG_INPUT);          // Read magnetic switch input (active high)
     
        // debug_message("\nstate:%d",estado);

        if (last==RISING && last!=lectura)  // if Rising(leading) edge on input start timer
        {
    
          TimerCount=RETARDO;                              // Timer Delay in seconds
          digitalWrite(RELAY,HIGH);                     // Turn on lights
          sun(ON);                                     // Also the sun icon
          TimeSinceLastMeasure2 = millis();           // Update (Sync like output compare)
          print_count(TimerCount,D_SHOW);
        }
        
        last=lectura;                                 // Update button State

        if(lectura==1)                                // While input stays active freeze timer 
            TimerCount=RETARDO;                       // Timer Delay in seconds
  
  return(lectura); 
}


void Update_oled(void)
{
    if(Read_PIR_Input())
      pirtext(ON);
    else
      pirtext(OFF);

    if(Read_Magnetic_Switch())
      magtext(ON);
    else
      magtext(OFF);
      
  
}

