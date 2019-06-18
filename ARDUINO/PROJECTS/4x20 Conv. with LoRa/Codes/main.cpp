#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <LoRa.h>

#define SDA 21
#define SCL 14

Adafruit_ADS1115 ads(0x48);

String LoRaData;
double amp[2]={0.0};
double voltaje[2]={0.0};
double amp1=0.0;
double voltaje1=0.0;
double promamp = 0.0;
double promvolt = 0.0;
double lectura3=0.0;
double sumavolt = 0.0;
double sumaamp = 0.0;
unsigned long interval = 2000; //interval that replace the delay comand
unsigned long previousMillis; //GPIO 22 SCL Y 21 SDA PARA EL CONVERSOR ADC EXTERNO 
int i;

byte localAddress = 0xBB;     // address of this device
byte destination = 0xA7;      // destination to send to

double mapfloat(double x, double in_min, double in_max, double out_min, double out_max)
{
  return (((x - in_min) * (out_max - out_min)) / (in_max - in_min)) + out_min;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin(SDA,SCL);
  ads.setGain(GAIN_ONE);
  ads.begin();
  LoRa.setPins(4, 22, 5);
  Serial.println("pines configurados...");
  
  if (!LoRa.begin(915E6))
  {
    Serial.println("Fallo Iniciando Modulo!");
    while (1)
      ;
  }
  LoRa.setSignalBandwidth(41.7E3);
  LoRa.setSpreadingFactor(9);
  //LoRa.setCodingRate4(8);
  LoRa.setTxPower(20);
  Serial.println("LoRa OK!");
}

void loop()
{
  unsigned long currentMillis = millis();
  if ((unsigned long)(currentMillis - previousMillis) >= interval)
  {
      lectura3=ads.readADC_SingleEnded(0);      
      Serial.println("");  
      Serial.print(lectura3,6);
      voltaje1 = mapfloat((double)lectura3, 0.0, 32678.0, 0.0, 3.3);
      amp1 = mapfloat((double)lectura3, 0.0, 32678.0, 4.0, 20.0);

      Serial.println("");
      Serial.println("");
      Serial.print(voltaje1,6);
      Serial.print("  ");
      Serial.println("");
      Serial.print(amp1,6);
      Serial.print("  ");
      previousMillis = millis();
      LoRa.beginPacket();
      LoRa.write(destination);              // add destination address
      LoRa.println("");
      LoRa.print(voltaje1);
      LoRa.print(" V");
      LoRa.println("");
      LoRa.print(amp1);
      LoRa.print(" mA");
      LoRa.println("");
      LoRa.flush();
      LoRa.endPacket();
      Serial.println("dato enviado");
      Serial.println("");
      sumavolt = 0.0;
      sumaamp = 0.0;
      promamp=0.0;
      promvolt=0.0;
      lectura3=0.0;
  }
}