/*
  Grove_LCD_RGB_Backlight.h
  2013 Copyright (c) Seeed Technology Inc.  All right reserved.

  Author:Loovee
  2013-9-18

  add rgb backlight fucnction @ 2013-10-15
  
  The MIT License (MIT)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.1  USA
*/


#ifndef __Grove_LCD_RGB_Backlight_H__
#define __Grove_LCD_RGB_Backlight_H__

#include <inttypes.h>
#include <mbed.h>

// Device I2C Adrress for V5.0
// In V5.0 docs for ARDUINO and RASPBERRY PI
// Addresses are given as (0x7c>>1) or 0x3c 
// but values are sent in reverse order s0
// 0x3c becomes 0x7C
// The other address is given by 0x30 which when
// reversed is 0x60
#define LCD_ADDRESS     (0x7c)   
#define RGB_ADDRESS     (0x60)


// color define 
#define WHITE           0
#define RED             1
#define GREEN           2
#define BLUE            3

// for LCD V5.0 these are the RED/GREEN/BLUE addresses
#define REG_RED         0x06       // pwm2
#define REG_GREEN       0x07        // pwm1
#define REG_BLUE        0x08        // pwm0

#define REG_MODE1       0x00
#define REG_MODE2       0x01
#define REG_OUTPUT      0x08

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

class Grove_LCD_RGB_Backlight // : public Print 
{

public:
  Grove_LCD_RGB_Backlight(PinName sda, PinName scl);

  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void createChar(uint8_t, uint8_t[]);
  void locate(uint8_t, uint8_t); 
  
  virtual size_t write(uint8_t);
  void command(uint8_t);
  
  // color control
  void setRGB(unsigned char r, unsigned char g, unsigned char b);               // set rgb
  void setPWM(unsigned char color, unsigned char pwm){setReg(color, pwm);}      // set pwm
  
  void setColor(unsigned char color);
  void setColorAll(){setRGB(0, 0, 0);}
  void setColorWhite(){setRGB(255, 255, 255);}

  // blink the LED backlight
  void blinkLED(void);
  void noBlinkLED(void);
  
  // using Print::write;

  // Print
  void print(char *str);
  
private:
  void send(uint8_t, uint8_t);
  void setReg(char addr, char val);

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;

  uint8_t _numlines,_currline;

  I2C i2c;
};

#endif
