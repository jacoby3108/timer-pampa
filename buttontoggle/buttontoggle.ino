/*
  Button Toggle led on rising edge
  
*/
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



#define LED D0
#define BOTON D6
#define RISING 0
#define FALLING 1

#define EDGE FALLING

int estado;
int lectura;
int last;
long TimeSinceLastMeasure = 0;

void setup() {
 
  pinMode(LED, OUTPUT);
  pinMode(BOTON,INPUT_PULLUP);
  estado=0;
  Serial.begin(115200);      // open the serial port at 115200 bps
}


void loop() {

    if (millis() - TimeSinceLastMeasure > 200 )   // Delay between measurements 200mseg.(for debonce)
    
    {   

        TimeSinceLastMeasure = millis();          // Update
        lectura=digitalRead(BOTON);               // Read input

        // debug_message("\nstate:%d",estado);

        if (last==EDGE && last!=lectura)  // if Rising(Falling) edge on input toggle state
        {
    
          estado=!estado;
    
        }
        
        last=lectura;
    }

    if(estado)
    digitalWrite(LED,HIGH);
    else
    digitalWrite(LED,LOW);

}
