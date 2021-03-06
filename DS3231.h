#include "RTClib.h"
#include <ESP32Ping.h>
const char* remote_host = "www.google.com";
RTC_DS3231 rtc;
char  TFT_time[16];

void DS3231_init()
{
  rtc.begin();
  if (WiFi.status() == WL_CONNECTED){
    if (Ping.ping(remote_host)){
      timeClient.update();
      uint32_t epochTime = timeClient.getEpochTime();
      rtc.adjust(DateTime(epochTime));
      Serial.println("updatetimeDS3231");
    }
  }
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
}

void getDS3231data(){
    DateTime now = rtc.now();
    if(now.hour()<10 && now.minute()<10){
      sprintf(TFT_time,"0%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    }
    if(now.hour()>=10 && now.minute()<10){
      sprintf(TFT_time,"%d:0%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()<10 && now.minute()>=10){
      sprintf(TFT_time,"0%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    if(now.hour()>=10 && now.minute()>=10){
      sprintf(TFT_time,"%d:%d  %d/%d/%d",int(now.hour()),int(now.minute()),int(now.day()),int(now.month()),int(now.year()%2000));
    } 
    
}
