/* LCD Screen */
#include <LiquidCrystal.h>
const int rs = 12, en  = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/*  Temperature humidity sensor */
#include <DHT.h>
#define datapin 7     // Digital  pin we're connected to
#define DHTTYPE DHT22
DHT dht(datapin, DHTTYPE);


void  setup() {
  dht.begin(); 
  lcd.begin(16, 2);
}

void loop() {

  /* Find Temperature & Humidity */
  float air_temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  
  /* Print Output on LCD Screen  */
  lcd.setCursor(0,0);
  lcd.print(String("Temp. ") + String(air_temp));
  lcd.setCursor(0,1);
  lcd.print(String("Humedad ") + String(humidity));

  delay(2000);

}
