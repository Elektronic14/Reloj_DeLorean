#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup(){
  Serial.begin(9600);
  rtc.begin();   //inicializamos el RTC
  Serial.println("Actualizando la hora y fecha...");
  rtc.adjust(DataTime(F (__ DATE__), F (__ TIME__)));
  Serial.println("Actualizada la hora y fecha con la que se compiló este programa: ");
  Serial.println("Fecha= ");
  Serial.println(__ DATE__);
  Serial.println(" Hora= ");
  Serial.println(__ TIME__);
  
}

Void loop(){
  
}
