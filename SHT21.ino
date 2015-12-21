#include <i2c_sht21.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// SHT21 Settings
i2c_sht21 mySHT21;
#define SHT_address  0x40
float temperatur=0.0;
float humy=0.0;

// LCD Settings
LiquidCrystal_I2C lcd(0x3F,20,4);


void setup() {
  Serial.begin(115200);
  Wire.begin(2,4);
  mySHT21.init(SHT_address);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Temperatur: ");
  lcd.setCursor(0,1);
  lcd.print("Luftfeuchte: ");

}

void loop() {
  temperatur=mySHT21.readTemp();
  humy=mySHT21.readHumidity();

  Serial.print("Temperatur: ");
  Serial.println(temperatur);

  lcd.setCursor(12,0);
  lcd.print(temperatur);
  lcd.setCursor(18,0);
  lcd.print("C");
  
  Serial.print("Luftfeuchte: ");
  Serial.println(humy);

  lcd.setCursor(13,1);
  lcd.print(humy);
  lcd.setCursor(19,1);
  lcd.print("%");

  delay(1000);
  

}
