/*
  SHT2x - Digitaler Feuchte- & Temperatursensor (RH/T)
  http://www.sensirion.com/de/produkte/feuchte-und-temperatur/feuchte-temperatursensor-sht2x/
 
  SHT21 - Standard Ausführung, +/-2% RH Genauigkeit 
    Grösse:				3 x 3 x 1.1 mm
    Schnittstelle:		I²C digital, PWM, SDM
    Betriebsspannung:	2.1 bis 3.6 V
    Energieverbrauch:	3.2µW (bei 8 bit, 1 Messung / s)
    Messbereich (RH):	0 - 100% relative Feuchte
    Messbereich (T):	-40 bis +125°C (-40 bis +257°F)
    Ansprechzeit (RH):	8 Sekunden (tau63%)

	~4€
	breakout ~13€ 	http://shop.emsystech.de/themes/kategorie/detail.php?artikelid=9&kategorieid=5&source=1&refertype=9
*/
#include "Arduino.h"
#include <Wire.h>


#include "i2c_sht21.h"


i2c_sht21::i2c_sht21()
{
	 //
	 /*
		pin 2  gpio2  SDA (data)
		pin 0  gpio1  SCL (clock)
	 */
 // Wire.begin(_devid);
	// Wire.pins(0, 2); //0=SDA, 2=SCL
}

void i2c_sht21::init(int i2c_devid=sht21_DEVID)
{
  _devid=i2c_devid; 
  Softreset();

}


//SHT21
void i2c_sht21::Softreset(void)
{
  Wire.beginTransmission(_devid); 		//begin transmitting
  Wire.write(0xFE); 					//Softreset
  Wire.endTransmission(); 
  delay(100); 
}

int i2c_sht21::readData(int befehl){
  Wire.beginTransmission(_devid);     //begin transmitting
  Wire.write(befehl); 
  Wire.endTransmission(); 
  delay(100);//(500) min 20u
  Wire.requestFrom(_devid, 3); 
  while(Wire.available() < 3) {
      ; //wait
   }   
  byte msb,lsb,Checksum;//data(MSB),data(LSB), Checksum 
  //LSB 1&2 bit=Stat
  msb= Wire.read();
  lsb = Wire.read();
  //lsb &= ~((1<<0)|(1<<1)));//bit 0 und 1 löschen
  lsb &= ~(0b00000011);//bit 0 und 1 löschen
  Checksum= Wire.read();
  Wire.endTransmission();  
  return (msb<<8)+lsb;
}


float i2c_sht21::readTemp(void)
{//-40..+125°C
  int re=readData(0xF3);  //TRIGGER_TEMPERATURE_NO_HOLD
  temperatur= ( ( (175.72/65536.0) * (float)re)  - 46.85 );    
  return temperatur;
}

float i2c_sht21::readHumidity(void)
{//0..100% Luftfeuchte % 
  int re=readData(0xF5);//TRIGGER_HUMIDITY_NO_HOLD
  humidity=( ((125.0/65536.0) * (float)re) - 6.0);  
  return humidity;
}
