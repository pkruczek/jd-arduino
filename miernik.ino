//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define UNIT_START_POS 8

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/


 return btnNONE;  // when all others fail, return this...
}

int calcPressure(int pinValue) 
{
  const float k = 1.859248;
  const float bias = 186.397085;
  int result = k * pinValue - bias;
  return result > 0 ? result : 0;
}

void printResult(int result) 
{
  int startPos = UNIT_START_POS-1;
  for (int i = result; i /= 10; i > 0) {
    startPos--;
  }
  lcd.setCursor(startPos, 0);
  lcd.print(result);
}

void setup()
{
 lcd.begin(16, 2);              // start the library
 lcd.setCursor(UNIT_START_POS,0);
 lcd.print("bar");
}
 
void loop()
{
 lcd.setCursor(0,0);            
 printResult(calcPressure(analogRead(A1))); 
 delay(500); 


 //lcd.setCursor(0,1);            // move to the begining of the second line
// lcd_key = read_LCD_buttons();  // read the buttons

// switch (lcd_key)               // depending on which button was pushed, we perform an action
// {
//   case btnRIGHT:
//     {
//     Serial.println("RIGHT");
//     lcd.print("RIGHT ");
//     break;
//     }
//   case btnLEFT:
//     {
//     Serial.println("LEFT");
//     lcd.print("LEFT   ");
//     break;
//     }
//   case btnUP:
//     {
//     Serial.println("UP");
//     lcd.print("UP    ");
//     break;
//     }
//   case btnDOWN:
//     {
//     Serial.println("DOWN");
//     lcd.print("DOWN  ");
//     break;
//     }
//   case btnSELECT:
//     {
//     Serial.println("SELECT");
//     lcd.print("SELECT");
//     break;
//     }
//     case btnNONE:
//     {
//     Serial.println("NONE");
//     lcd.print("NONE  ");
//     break;
//     }
// }

}
 
