# 4-20 mA Conversor + LoRa SX1276 on ESP32

For this program it is necessary to read a (4-20) mA sensor and send the data through the LoRa protocol.
This problem has different stages:
- Voltage converter for the Sensor.
- Data capture.
- Sent the data for LoRa.

## Voltage converter for the sensor:
In this case, a module that is ready to perform this work was used, it is commercially available and it is easy to calibrate its output voltage to avoid damage to the other electronic components.
The voltage output of this regulator was set at approximately 4.1 V to have the full range of operation of the ADS1115 at its first attenuation (For more information go to the manufacturer's Datasheet) The module that was used was a Current loop converter 4-20 mA at voltage, of reference like [this](https://www.electronicaembajadores.com/en/Productos/Detalle/LCINV20/electronic-module/instrumentation-modules/current-loop -converter-4-20-ma-to-voltage)

## Voltage capture:
Because the application of this code required high resolution, an external ADC ADS1115 of 16 bits was implemented per I2C connection connected to the ESP32, because the internal ADC of the ESP was not sufficient and 0.01 mA precision was required and using the Adafruit ADS1015 library.
After the data capture with the ADS1115, the conversion of bits was carried out by means of a mapping to have the necessary operation interval using the MapFloat function.

## Sent Data by LoRa:
The sending was made through the SX1276 module at 915MHz, connected to the ESP32 via SPI connection.

### Note: 
All devices are powered by a regulated voltage source configured at 4.9V like [this](https://www.jaycar.com.au/arduino-compatible-dc-voltage-regulator/p/XC4514)
