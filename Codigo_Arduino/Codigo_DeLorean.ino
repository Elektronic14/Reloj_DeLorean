#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
#include "RTClib.h"

// Salida reloj Rojo
const byte PIN_CLK_Red = A0;   // define CLK pin  
// Salida reloj Verde
const byte PIN_CLK_Green = A1;   // define CLK pin 
// Salida reloj Naranja
const byte PIN_CLK_Orange = A2;   // define CLK pin 

//Displays Rojos
const byte PIN_DIO_R1 = 3;
SevenSegmentExtended      red1(PIN_CLK_Red, PIN_DIO_R1);
const byte PIN_DIO_R2 = 4;
SevenSegmentTM1637       red2(PIN_CLK_Red, PIN_DIO_R2);
const byte PIN_DIO_R3 = 5;
SevenSegmentExtended     red3(PIN_CLK_Red, PIN_DIO_R3);

//Displays Verdes
const byte PIN_DIO_G1 = 6;
SevenSegmentExtended      green1(PIN_CLK_Green, PIN_DIO_G1);
const byte PIN_DIO_G2 = 7;
SevenSegmentTM1637       green2(PIN_CLK_Green, PIN_DIO_G2);
const byte PIN_DIO_G3 = 8;
SevenSegmentExtended     green3(PIN_CLK_Green, PIN_DIO_G3);

//se pueden conectar los leds del medio a los pines 12 y 13
int greenAM = 12;
int greenPM = 13;

// Displays Naranjas
const byte PIN_DIO_O1 = 9;   // define DIO pin (any digital pin)
SevenSegmentExtended      orange1(PIN_CLK_Orange, PIN_DIO_O1); // SegmentExtended pour utiliser la methode "PrintTime"
const byte PIN_DIO_O2 = 10;   
SevenSegmentTM1637        orange2(PIN_CLK_Orange, PIN_DIO_O2); //SegmentTM1637 pour utiliser la methode "print" permet d'enlever les ":" entre les chiffres
const byte PIN_DIO_O3 = 11;   
SevenSegmentExtended       orange3(PIN_CLK_Orange, PIN_DIO_O3); 

bool parse=false;
bool config=false;
int Hour=0;
RTC_DS3231 rtc;
int backlight = 50;
int year_red = 2028;
int year_orange = 2018;

void setup() {

  pinMode(PIN_CLK_Red, OUTPUT);
  pinMode(PIN_CLK_Green, OUTPUT);
  pinMode(PIN_CLK_Orange, OUTPUT);
  pinMode(PIN_DIO_O1, OUTPUT);
  pinMode(PIN_DIO_O2, OUTPUT);
  pinMode(PIN_DIO_O3, OUTPUT);
  pinMode(PIN_DIO_G1, OUTPUT); 
  pinMode(PIN_DIO_G2, OUTPUT);
  pinMode(PIN_DIO_G3, OUTPUT); 
  pinMode(PIN_DIO_R1, OUTPUT);
  pinMode(PIN_DIO_R2, OUTPUT);
  pinMode(PIN_DIO_R3, OUTPUT);
  pinMode(greenAM, OUTPUT);
  pinMode(greenPM, OUTPUT);

  Serial.begin(9600);       // inicializa la conexión del Seriañ a  @9600 baudios
  orange1.begin();          // inicializa el display
  orange2.begin();
  orange3.begin();              
  green1.begin();
  green2.begin();
  green3.begin();            
  red1.begin();
  red2.begin();
  red3.begin();            
  orange1.setBacklight(backlight);  //establece el brillo al 100 %
  orange2.setBacklight(backlight);
  orange2.setColonOn(0); // Switch off ":" for orange "year"
  orange3.setBacklight(backlight);  
  green1.setBacklight(backlight); 
  green2.setBacklight(backlight);
  green3.setBacklight(backlight); 
  red1.setBacklight(backlight);
  red2.setBacklight(backlight);
  red3.setBacklight(backlight);  
  red2.setColonOn(0); // Switch off ":" for red "year"
  
#ifndef ESP8266
  while (!Serial); 
#endif

  Serial.begin(9600);

  delay(3000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // cuando se va la alimentación, el reloj vuelve a la hora de compilación del programa
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

}

void loop() {
  
    DateTime now = rtc.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

//Descomentar dependiendo si estamos en el horario de verano o en el de invierno
//Hour=now.hour(); // Horario de verano
//Hour=now.hour()-1; // Horario de invierno

if(now.hour()>=13){
   Hour=now.hour();
  digitalWrite(greenAM,0);
  digitalWrite(greenPM,1);}
  
else if(now.hour()==12)
  {Hour=now.hour();
   digitalWrite(greenAM,0);
  digitalWrite(greenPM,1);}


else{
  Hour=now.hour();
  digitalWrite(greenAM,1);
  digitalWrite(greenPM,0);
  }

//Displays Rojos -  HORA del pasado: 11.09 2028 10:07
red1.printTime(11, 9, true);
red2.print(year_red, true);
red3.printTime(10, 07, true); 

//Green Displays - HORa del presente - Heora actual
green1.printTime(now.month(), now.day(), true);  
green2.print(now.year());
green3.printTime(Hour, now.minute(), true);

// Orange Displays - HORA del futuro 10.09 2018 01:24                      
orange1.printTime(11, 9, true);                     
orange2.print(year_orange, true);
orange3.printTime(01, 24, true);
                     
}
