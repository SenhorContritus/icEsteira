#include<Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_TCS34725.h>
#define ftr 0
#define cSens 2

double r, g, b;
int qnt = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_TCS34725 tcs(0x29);

void initLcd(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("Gugu");
  delay(1500);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Quantidade:");
}

String verifyColor(int d){
  delay(d);
  float red, green, blue;
  tcs.getRGB(&red, &green, &blue);
  if(red > green && red > blue){
  	return  "Vermelho";
  }
  if(green > red && green > blue){
  	return "Verde";
  }
  if(blue > red && blue > green){
    return "Azul";
  }
  else{
  	return " undef.";
  }
}

void showData(int x, int d){
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Quantidade:");
  lcd.setCursor(11,0);
  lcd.print(x);

  lcd.setCursor(0,1);
  lcd.print("Cor:");
  lcd.setCursor(4,1);
  lcd.print(verifyColor(d));
}

void setup()
{
  initLcd();
  Serial.begin(9600);
  tcs.begin();

}

void loop()
{
  int ldr = analogRead(ftr);

  if(ldr> 80){
    qnt++;
    showData(qnt, 680);
    while(ldr > 80){
      ldr = analogRead(ftr);
    }
  }	
    
  
}