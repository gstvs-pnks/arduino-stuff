#include <LiquidCrystal.h>

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
int x = 0;
int y = 0;

// read the buttons
int read_LCD_buttons()
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 1000) return btnNONE; 
  if (adc_key_in < 50)   return btnRIGHT;
  if (adc_key_in < 195)  return btnUP;
  if (adc_key_in < 380)  return btnDOWN;
  if (adc_key_in < 555)  return btnLEFT;
  if (adc_key_in < 790)  return btnSELECT;
  
  return btnNONE;
}

void background(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  #   #      #  "); //Y=0, X=3,7,14
  lcd.setCursor(0, 1);
  lcd.print("#   #     #    #"); //Y=1, X=1,5,11,16
}

void check(){
  if (y == 0 && (x == 2 || x== 6 || x == 13)){
    delay(500);
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    lcd.setCursor(0, 1);
    lcd.print("Press reset");
    delay(500);
    lcd.clear();
    delay(500);
    //lcd.setCursor(0, 0);
    //lcd.print("Press reset");
  }

  if (y == 1 && (x == 0 || x== 4 || x == 10 || x == 15)){
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("GAME OVER!");
    delay(1000);
    lcd.clear();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Press reset");
  }

  
}

void placeX(){
  lcd.setCursor(x, y);
  lcd.print("X");
  delay(500);
}

void setup()
{
  lcd.begin(16, 2);              
  lcd.setCursor(x, y);
  lcd.print("Lets play a game");
  delay(3000);
  lcd.clear();
  delay(500);
  
  background();
  placeX();

  //const int forbiddenCount = 7;
  //int forbiddenX[forbiddenCount] = {3, 7, 14, 1, 5, 11, 16};
  //int forbiddenY[forbiddenCount] = {0, 0, 0, 1, 1, 1, 1};
  
}

void loop()
{ 
  //if (x = forbidden value and y = forbidden value) {te bus break}

  if (x > 15) {
            delay(1000);
            lcd.clear(); 
            lcd.setCursor(0,0);
            lcd.print("YOU WON!");
            delay(1000);
          }
  
  else {
          
    lcd_key = read_LCD_buttons();  // read the buttons

    check();

    switch (lcd_key){
      
      case btnRIGHT:
        {
          //delay(500);
          lcd.clear();
          x++;
          background();
          placeX();
          break;
          
        }
      case btnLEFT:
        {
          //delay(500);
          
          if (x<=0) {break;}
          else {
          lcd.clear();
          x--;
          background();
          placeX();
          break;
          }
        }
      case btnUP:
        {
          if (y < 0 || y > 1){break;}
          else {
          lcd.clear();
          y--;
          background();
          placeX();
          break;
          }
        }
      case btnDOWN:
        {
          if (y < 0 || y > 1){break;}
          else {
          lcd.clear();
          y++;
          background();
          placeX();
          break;
          }
        }
      case btnSELECT:
        {
          lcd.print("Restarting!");
          delay(500);
          lcd.clear();
          x = 0;
          y = 0;
          background();
          placeX();
          break;
        }
      case btnNONE:
        {
          break;
        }
    }

  }
}
