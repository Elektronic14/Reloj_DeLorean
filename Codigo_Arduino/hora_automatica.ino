

//Ejemplo basico para la lectura de la hora y fecha

//del modulo DS1307


 

#include <Wire.h> //llamado de libreria

#include "RTClib.h" //llamado de libreria DS1307

 

RTC_DS1307 RTC;

 

void setup () {

    Serial.begin(57600);

    Wire.begin();

    RTC.begin();

 

  if (! RTC.isrunning()) {

    Serial.println("RTC is NOT running!");  

    RTC.adjust(DateTime(__DATE__, __TIME__));

  }

}

 

void loop () {

    DateTime now = RTC.now();

    
    
    Serial.print(now.day(), DEC);

    Serial.print('/');
    
    Serial.print(now.month(), DEC);

    Serial.print('/');

    Serial.print(now.year(), DEC);

    Serial.print(' ');

    Serial.print(now.hour(), DEC);

    Serial.print(':');

    Serial.print(now.minute(), DEC);

    Serial.print(':');

    Serial.print(now.second(), DEC);

    Serial.println();

   
    delay(950);

    

}

