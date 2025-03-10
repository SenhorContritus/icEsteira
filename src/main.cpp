#include <Arduino.h> // Biblioteca necessária para executar no vscode
#include <LiquidCrystal_I2C.h> // Biblioteca do display LCD I2C
#include <Adafruit_TCS34725.h> // Biblioteca do sensor de cor

#define ftr 0 // Variavel de status do fotoresistor

// Pinos para envio das cores para o esp32
#define espRed 13 
#define espGreen 12
#define espBlue 11

int qnt = 0; // Variavel que recebe a quantidade de objetos

LiquidCrystal_I2C lcd(0x27,20,4); //Declara o objeto da biblioteca LiquidCrystal como lcd
Adafruit_TCS34725 tcs(0x29); //Declara o objeto da biblioteca TCS como tcs

// Função para tela inicial do lcd
void initLcd(){
  lcd.init();
  lcd.backlight();

  lcd.setCursor(3,0);
  lcd.print("Gugu <3");

  delay(1500);

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Quantidade:");
  lcd.setCursor(0,1);
  lcd.print("Cor:");

}
 
// Função que faz a verificação da cor do objeto detectado no ftr
String verifyColor(int d){

  delay(d);// Tempo necessário para o objeto chegar no sensor de cor

  float red, green, blue;

  tcs.getRGB(&red, &green, &blue);// Obtem a quantidade que cada espectro de cor reflete ao sensor

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

// Função para envio das informações ao ESP32
void sendData(String c){
  if(c == "Vermeho"){
    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(13,HIGH);

  }else if (c == "Verde")
  {
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
    digitalWrite(12,HIGH);

  }else if (c == "Azul")
  {
    digitalWrite(13, LOW);
    digitalWrite(12, LOW);
    digitalWrite(11,HIGH);

  }else{
    // Caso a cor do objeto seja indefinida
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    digitalWrite(11,HIGH);
  }
}

// Função que mostra os dados no display
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

  pinMode(espRed, OUTPUT);
  pinMode(espGreen, OUTPUT);
  pinMode(espBlue, OUTPUT);

}

void loop()
{
  int ldr = analogRead(ftr);

  if(ldr> 80){
    //Detecta quando um objeto passa na frente do sensor
    qnt++;//Soma 1 a quantidade de objetos

    showData(qnt, 658);//envia a quantidade de objetos a ser mostrada e o delay de chegada ao sensor de cor
    sendData(verifyColor(1));//envia as informações ao Esp e tem como parametro um delay minimo exigido pela função

    while(ldr > 80){
      //Entra em um loop enquanto o objeto não sai da frente do sensor, impedindo a multipla soma de objetos
      ldr = analogRead(ftr);//Verifica o estado do sensor
    }
  }	
}