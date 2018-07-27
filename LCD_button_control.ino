//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);      //default pins for the Arduino Uno

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

const int top_button = A0;
const int mid_button = A1;
const int bottom_button = A2;

// read the onboard buttons
int read_onboard_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor
 // my buttons when read are centered at these values: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close

 if (adc_key_in < 50)   return btnRIGHT;
 if (adc_key_in < 195)  return btnUP;
 if (adc_key_in < 380)  return btnDOWN;
 if (adc_key_in < 555)  return btnLEFT;
 if (adc_key_in < 790)  return btnSELECT;



 return btnNONE;  // when all others fail, return this...
}

// read external read_onboard_LCD_buttons
int read_external_LCD_buttons()
{
  int up = digitalRead(top_button);
  int click = digitalRead(mid_button);
  int down = digitalRead(bottom_button);

  // up was pressed
  if(click == LOW)
  {
    return btnSELECT;
  }
  else if(down == LOW)
  {
    return btnDOWN;
  }
  else if(up == LOW)
  {
    return btnUP;
  }
  else
  {
    return btnNONE;
  }
}

void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(0,0);
 pinMode(top_button, INPUT_PULLUP);
 pinMode(mid_button, INPUT_PULLUP);
 pinMode(bottom_button, INPUT_PULLUP);
 lcd.print("Push the buttons"); // print a simple message
}

void loop()
{
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(millis()/1000);      // display seconds elapsed since power-up


 lcd.setCursor(0,1);            // move to the begining of the second line
 lcd_key = read_external_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }
}
