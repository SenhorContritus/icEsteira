#include<Arduino.h>
#include <LiquidCrystal_I2C.h>
#define ftr 0
#define cSens 2


int qnt = 0;

LiquidCrystal_I2C lcd(0x27,20,4);

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
  if(cSens == 1){
  	return  "Vermelho";
  }
  if(cSens == 2){
  	return "Verde";
  }
  if(cSens == 3){
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
}

void loop()
{
  int ldr = analogRead(ftr);
  if(ldr< 160){
    qnt++;
    showData(qnt, 200);
    while(ldr < 160){
      ldr = analogRead(ftr);
    }
  }	
  
}