

/*
  LCD.cpp - Library for using the MIDAS MCCOG21605B6W-FPTLWI 16x2 Black on white 
  LCD, with I2C interface with the ESP8266 that comes with the ESP8266 NodeMCU.
  The I2C interface uses
  ESP8266   |         |LCD
            |         |  
            |         |Pin 1 Boost Capacitor 1  
            |         |Pin 2 Capacitor 2 N  
            |         |Pin 3 Capacitor 2 P
 Vcc (3.3V) |---------|Pin 4 Vdd (Boost Capacitor 1)
        Gnd |---------|Pin 5 Gnd      
        D2  |---------|Pin 6 (SDA)
        D1  |---------|Pin 7 (SCL)
        D6  |---------|Pin 8 (RST)
        D5  |---------| A (Backlight Anode)
        Gnd |---------| K (Backlight Cathode)

       
  4.7kohm pullups are used on pins 6, 7, 8. Two 1uF capacitors are required
  between pins 1 and 4 and between 2 and 3 when using a 3V supply.
   
  Created by Benn Thomsen, 15 February, 2014.
  Released into the public domain.
  Edited by Miruna Moraru for ESP8266 20 March 2018
*/

#ifndef LCD_h
#define LCD_h

class LCD
{
  public:
    LCD(char address);                 //Object constructor
    void init();                       //Initialise LCD display must be called first
    void clear();                      //Clear display and return cursor to home
    void home();                       //Return cursor to home
    void lineFeed();                   //Move to first column of second line
    void blinkOn();                    //Turn blinking cursor on
    void blinkOff();                   //Turn blinking cursor off
    void cursorOn();                   //Turn cursor on
    void cursorOff();                  //Turn cursor off
    void backSpace();                  //Backspace
    void forward();                    //Forward one space
    void back();                       //Back one space
    void up();                         //Up one line
    void down();                       //Down one line
    void deleteChar();                 //Delete current character
    void writeString(char);            //Write byte at current cursor position
    void writeString(char*);           //Write string at current cursor position
    void writeString(char, char*);     //Write string at specified position (0-15)
    void backLight(char level);        //Set backlight intensity accepts values from 0-999

  private:
    char _address;
    char _display;
    char _line;
    char _column;
};

#endif
