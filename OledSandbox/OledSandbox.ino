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
 

// Include the correct display library
// For a connection via I2C using Wire include
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
//#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include "SH1106Wire.h", legacy include: `#include "SH1106.h"`
// For a connection via I2C using brzo_i2c (must be installed) include
// #include <brzo_i2c.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Brzo.h"
// #include "SH1106Brzo.h"
// For a connection via SPI include
// #include <SPI.h> // Only needed for Arduino 1.6.5 and earlier
// #include "SSD1306Spi.h"
// #include "SH1106SPi.h"

// Include custom images
#include "images.h"
#include "font35.h"
#include "sun.h"
// Initialize the OLED display using SPI
// D5 -> CLK
// D7 -> MOSI (DOUT)
// D0 -> RES
// D2 -> DC
// D8 -> CS
// SSD1306Spi        display(D0, D2, D8);
// or
// SH1106Spi         display(D0, D2);

// Initialize the OLED display using brzo_i2c
// D3 -> SDA
// D5 -> SCL
// SSD1306Brzo display(0x3c, D3, D5);
// or
// SH1106Brzo  display(0x3c, D3, D5);

// Initialize the OLED display using Wire library
// SSD1306Wire  display(0x3c, D3, D5);

// SH1106Wire(uint8_t _address, uint8_t _sda, uint8_t _scl, OLEDDISPLAY_GEOMETRY g = GEOMETRY_128_64)
   SH1106Wire display(0x3c, D2, D3);


#define DEMO_DURATION 3000
typedef void (*Demo)(void);
void SandBox(void);
void pirtext(int status);
void magtext(int status);
void sun(int status);

void print_count(int count,int cmd);
void show_count(int count);

int demoMode = 0;
int counter = 1;

#define INIT  0
#define SHOW  1
#define OFF   2

void setup() {
 
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

}

void drawFontFaceDemo() {
    // Font Demo1
    // create more fonts at http://oleddisplay.squix.ch/
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, 0, "Hello world");
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "Hello world");
    display.setFont(ArialMT_Plain_24);
    display.drawString(0, 26, "Hello world");
}

void drawTextFlowDemo() {
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}

void drawTextAlignmentDemo() {
    // Text alignment demo
  display.setFont(ArialMT_Plain_10);

  // The coordinates define the left starting point of the text
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "Left aligned (0,10)");

  // The coordinates define the center of the text
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 22, "Center aligned (64,22)");

  // The coordinates define the right end of the text
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, "Right aligned (128,33)");
}

void drawRectDemo() {
      // Draw a pixel at given position
    for (int i = 0; i < 10; i++) {
      display.setPixel(i, i);
      display.setPixel(10 - i, i);
    }
    display.drawRect(12, 12, 20, 20);

    // Fill the rectangle
    display.fillRect(14, 14, 17, 17);

    // Draw a line horizontally
    display.drawHorizontalLine(0, 40, 20);

    // Draw a line horizontally
    display.drawVerticalLine(40, 0, 20);
}

void drawCircleDemo() {
  for (int i=1; i < 8; i++) {
    display.setColor(WHITE);
    display.drawCircle(32, 32, i*3);
    if (i % 2 == 0) {
      display.setColor(BLACK);
    }
    display.fillCircle(96, 32, 32 - i* 3);
  }
}

void drawProgressBarDemo() {
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void drawImageDemo() {
    // see http://blog.squix.org/2015/05/esp8266-nodemcu-how-to-create-xbm.html
    // on how to create xbm files
    display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
}

Demo demos[] = {drawFontFaceDemo, drawTextFlowDemo, drawTextAlignmentDemo, drawRectDemo, drawCircleDemo, drawProgressBarDemo, drawImageDemo};
int demoLength = (sizeof(demos) / sizeof(Demo));
long timeSinceLastModeSwitch = 0;
unsigned int done =0;

unsigned int count=30;

void loop() {





  if (millis() - timeSinceLastModeSwitch > 1000) {
    SandBox3();
    if(count >0)
    count--;
    timeSinceLastModeSwitch = millis();
  }
  delay(10); // a bare minimum
  
/*********** 
  // clear the display
  display.clear();
  // draw the current demo method
  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();

  if (millis() - timeSinceLastModeSwitch > DEMO_DURATION) {
    demoMode = (demoMode + 1)  % demoLength;
    timeSinceLastModeSwitch = millis();
  }
  counter++;
  delay(10);
  *************/
}


void SandBox(void)
{
  
  display.clear();
  display.display();

  
 // display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
 // display.setFont(ArialMT_Plain_10);
 //   display.setFont(ArialMT_Plain_24);
  display.setFont(Dialog_plain_35);
  if (count<10)
  display.drawString(30, 0, String("0" + String(count)));
  else
  display.drawString(30, 0, String( count));
  display.display();

 
  
  ///Esto es para no olvidarse nunca: guarda con bloquear el loop mucho tiempo (cuidado con el perro)
  // No hacer esto
 // delay(30*1000); 
 // while(1);       
}

void SandBox1(void)
{
  
//  display.clear();
//  display.display();
  if (!done)
  {
 
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(Dialog_plain_35);

  display.drawString(50, 0, String( count));
  //display.setColor(BLACK);

  // Fill the rectangle
  // void fillRect(int16_t x, int16_t y, int16_t width, int16_t height);
  display.fillRect(50,0, 35, 42);
  display.display();
  done=1;
  }
 
  
  ///Esto es para no olvidarse nunca: guarda con bloquear el loop mucho tiempo (cuidado con el perro)
  // No hacer esto
 // delay(30*1000); 
 // while(1);       
}

void SandBox2(void)
{
  
  //display.clear();
  //display.display();

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
  display.display();

 
  
  ///Esto es para no olvidarse nunca: guarda con bloquear el loop mucho tiempo (cuidado con el perro)
  // No hacer esto
 // delay(30*1000); 
 // while(1);       
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
   print_count(count,SHOW);
   else{
    print_count(count,SHOW);
    print_count(count,OFF);
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
    
    if (cmd==SHOW)
    {
      
      display.setColor(BLACK);
      show_count(last_count);
      display.setColor(WHITE);
      show_count(count);  
      last_count=count;
    }
    else if(cmd==INIT)
    {
      last_count=count;
    }
    else if(cmd==OFF)
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
