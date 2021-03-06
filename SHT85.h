#include "SHTSensor.h"
#include "config.h"
//#include "TFT.h"
//#include "SDcard.h"
SHTSensor sht(SHTSensor::SHT3X);

uint32_t lastReadSHT = 0;
//float temp_calib = 0;
//float humi_calib = 0;
float TFT_temp = 0;
float TFT_temp_F = 0;
float TFT_humi = 0;
void getSHTdata(){
  if ( (millis() - lastReadSHT > 5000) || (millis() < lastReadSHT))
  {
    float SHT_temp = 0;
    float SHT_humi = 0;
      Serial.print("teeeemp: ");
      Serial.println(tempCalibInt);
      Serial.print("humiiiii: ");
      Serial.println(humiCalibInt);
    if (sht.readSample()) {

      SHT_temp = sht.getTemperature()+ tempCalibInt;
      SHT_humi = sht.getHumidity() + humiCalibInt;
      //Serial.println("T = "+String(SHT_temp)+"  "+"H = "+String(SHT_humi));
    } else {
      //Serial.print("SHT85 Error in readSample()\n");   
    }
    if(SHT_temp>0 && SHT_humi>0 && SHT_temp<100 && SHT_humi<100){
      TFT_temp = SHT_temp ;
      TFT_humi = SHT_humi ;
      TFT_temp_F = SHT_temp + 273;
    }else{
      TFT_temp = 0;
      TFT_humi = 0;     
    }
    lastReadSHT = millis(); 
  }
}
void SHT85_init(){
  if (sht.init()) {
    Serial.print("SHT init(): success\n");
  } else Serial.print("SHT init(): failed\n");
}
