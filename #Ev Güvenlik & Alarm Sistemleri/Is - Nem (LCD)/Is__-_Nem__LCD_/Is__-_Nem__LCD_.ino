#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 1
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
dht.begin();
lcd.begin(16, 2);
}
void loop() {
float nem = dht.readHumidity();

float sicaklik = dht.readTemperature();// ‘C cinsinden.
if (sicaklik<30)
lcd.print(“Ohh Miiss!”);
else{
if (sicaklik>30)
lcd.print(“Ohh Firin Gibi”);
if (sicaklik>40)
lcd.print(“Yaniyorum Usta”);
if (sicaklik>50)
lcd.print(“Atesim Var!”);}

lcd.setCursor(0, 1);
lcd.print(“Sicaklik: “);
lcd.print(sicaklik);
delay(500);
lcd.setCursor(0,0);

}
