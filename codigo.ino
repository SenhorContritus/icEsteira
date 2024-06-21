#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Adafruit_TCS34725.h>
#include <Ultrasonic.h>

Adafruit_TCS34725 tcs = Adafruit_TCS34725(0x29);
SoftwareSerial Esp = SoftwareSerial(3,2);
LiquidCrystal_I2C lcd(0x27, 16, 2);  

HC_SR04 sensor(12,13);

String cor = " ";  
int objectCount = 0;
int ver =0;
char colorSend = 'o';
long duration, distance;
uint16_t r, g, b, c;
const int rele = 9;


void setup() {

  lcd.init();
  lcd.backlight();
  tcs.getRawData(&r, &g, &b, &c);
  
  pinMode(rele, OUTPUT);

  digitalWrite(rele, HIGH);

  if(tcs.begin()){
    Serial.println("Sensor encontrado");
  }else{
    Serial.println("Sensor não encontrado");
    while(1);
  }


  Serial.begin(9600);
  Esp.begin(9600);
  
}
 
void loop() {

  int distancia = sensor.distance();

  digitalWrite(rele, HIGH);

  lcd.setCursor(0, 0);
  lcd.print("Contagem: ");

  char colorSend = "N";

  if((bool)(sensor.distance() < 6)){
    objectCount++;
    delay(1000);
    tcs.getRawData(&r, &g, &b, &c);

    if(b > g && b > r){

      cor = "blue";
      colorSend = 'b';

    }if(g > r && g > b){
      
      cor = "green";
      colorSend = 'g';

    }if(r > g && r > b){

      cor = "red";
      colorSend = 'r';
      

    }



    lcd.clear();
    lcd.setCursor(10, 0); 
    lcd.print(objectCount);
    lcd.setCursor(0,1); 
    lcd.print("Cor:");
    lcd.setCursor(4,1);
    lcd.print(cor);
    Esp.write(objectCount + colorSend);

    }



}