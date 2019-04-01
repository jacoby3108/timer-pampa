/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 *
 */

/*
 * This code was adapted for sh1106 (is is suposed to work with ssd1306 too!!!!!!!!)
 * 
 * Used library
 * 
 * https://github.com/ThingPulse/esp8266-oled-ssd1306
 * 
 * 
 * 
 */
 

#include "SH1106Wire.h", legacy include: `#include "SH1106.h"`
#include "oled.h"

// Include custom images

#include "images.h"
#include "font35.h"
#include "sun.h"

// SH1106Wire(uint8_t _address, uint8_t _sda, uint8_t _scl, OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64)
   SH1106Wire display(0x3c, D2, D3);// Data, clk



void SandBox3(void);
void pirtext(int status);
void magtext(int status);
void sun(int status);

void print_count(int count,int cmd);
void show_count(int count);

int demoMode = 0;
int counter = 1;



void Oled_setup(void) {
 
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}




long timeSinceLastModeSwitch = 0;
unsigned int done =0;

unsigned int count=30;

void Oled_loop(void) {





  if (millis() - timeSinceLastModeSwitch > 1000) {
    SandBox3();
    if(count >0)
    count--;
    timeSinceLastModeSwitch = millis();
  }
  delay(10); // a bare minimum
  

}







void SandBox3(void)
{
  static int tog=0;


 /******* 
  display.setColor(BLACK);
  // Fill the rectangle
  // void fillRect(int16_t x, int16_t y, int16_t width, int16_t height);
  display.fillRect(30,0, 45, 42);
  display.display();
  
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Dialog_plain_35);
  
  if (count<10)
  display.drawString(30, 0, String("0" + String(count)));
  else
  display.drawString(30, 0, String( count));
******/
   if(tog%2)
   print_count(count,D_SHOW);
   else{
    print_count(count,D_SHOW);
    print_count(count,D_OFF);
   }
   

   
   pirtext(tog%2);
   magtext(!(tog%2));
   sun(tog%2);
   tog++;
   
  ///Esto es para no olvidarse nunca: guarda con bloquear el loop mucho tiempo (cuidado con el perro)
  // No hacer esto
 // delay(30*1000); 
 // while(1);       
}

void sun(int status)
{
  
  if (status)
  {
      display.setColor(WHITE);
      // Draw a XBM
      // void drawXbm(int16_t x, int16_t y, int16_t width, int16_t height, const uint8_t *xbm);
      display.drawXbm(80, 0, sunbw_width, sunbw_height, sunbw_bits);
    
  }
  else
  {   
      display.setColor(BLACK);
      display.drawXbm(80, 0, sunbw_width, sunbw_height, sunbw_bits);
      display.setColor(WHITE);
  }

    display.display();
}


void pirtext(int status)

{
 
  if (status)
  {
    display.setColor(WHITE);
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 40, String("PIR"));
  
  }
  else

  {
     display.setColor(BLACK);
     display.setFont(ArialMT_Plain_24);
     display.drawString(0, 40, String("PIR"));
     display.setColor(WHITE);
  }
 
  display.display();


  
}


void magtext(int status)

{
 
  if (status)
  {
    display.setColor(WHITE);
    display.setFont(ArialMT_Plain_24);
    display.drawString(72,40, String("MAG"));
  
  }
  else

  {
     display.setColor(BLACK);
     display.setFont(ArialMT_Plain_24);
     display.drawString(72,40, String("MAG"));
     display.setColor(WHITE);
  }
 
  display.display();


  
}

void print_count(int count,int cmd)
{

  static int last_count;

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(Dialog_plain_35);
    
    if (cmd==D_SHOW)
    {
      
      display.setColor(BLACK);
      show_count(last_count);
      display.setColor(WHITE);
      show_count(count);  
      last_count=count;
    }
    else if(cmd==D_INIT)
    {
      last_count=count;
    }
    else if(cmd==D_OFF)
    {
      display.setColor(BLACK);
      show_count(last_count);
      display.setColor(WHITE);
    }
    
}

void show_count(int count)
{
  if (count<10)
  display.drawString(30, 0, String("0" + String(count)));
  else
  display.drawString(30, 0, String( count));

}
