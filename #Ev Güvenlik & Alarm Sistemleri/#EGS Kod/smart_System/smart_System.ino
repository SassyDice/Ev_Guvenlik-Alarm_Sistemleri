#include <SoftwareSerial.h>
#include <Servo.h>
 
Servo myservo;

int bluetoothTx = 10;
int bluetoothRx = 11;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

int sensor=1; //Sensör arduinonun analog 1 pinine bağlandı.
int sensor1=0;
int led1=8; // LED 8. dijital çıkış pinine bağlandı.
int led2=7; // LED 7. dijital çıkış pinine bağlandı.
int buzzer=4; // Buzzer 4. dijital çıkış pinine bağlandı.
int gas_limite; // Gaz limiti değişkeni tanımlandı.

int data;
int led=13;

float sicaklik; //Analog değeri dönüştüreceğimiz sıcaklık 
float analoggerilim; //Ölçeceğimiz analog değer

int yesil_led=2;                //8 numaralı pine yeşil led bağladık
int kirmizi_led=3;             // 9 numaralı pine kırmızı led bağladık 
int lm_35=A2;                  //  A2 numaralı pine sensörün base ucunu bağladık

void setup() {
  
  //USB Seri Bağlantısını Bilgisayara Kurma.
  myservo.attach(9);
  //Bluetooth Seri Bağlantısını Android'e Kurma.
  bluetooth.begin(9600);
  
  Serial.begin(9600); // Seri haberleşme ekranına bağlanma kodu.

  //Gaz Sensörü
  pinMode(sensor, INPUT); // Sensör giriş yapıldı.
  pinMode(led1, OUTPUT); // LED çıkış yapıldı.
  pinMode(led2, OUTPUT); // LED çıkış yapıldı.
  pinMode(buzzer, OUTPUT); // Buzzer çıkış yapıldı.

  pinMode(led, OUTPUT);

  //SICAKLIK
  pinMode(yesil_led,OUTPUT);            //  yeşil led çıkış olarak seçildi
  pinMode(kirmizi_led,OUTPUT);           // kırmızı led çıkış olarak seçildi
  pinMode(lm_35,INPUT);                // sensörden bilgi alınacağı için giriş olarak şeçildi

}

void loop() {

  // Gaz Sensörü
  gas_limite=analogRead(sensor); // Sensörden değer okunuyor.
  Serial.print("Gaz Durumu: "); // Seri haberleşme ekranında Gaz Durumu yazısı yazdırıldı.
  Serial.print(gas_limite); // Seri haberleşme ekranında gaz limiti değeri gösteriliyor.
  Serial.println(" Limit"); // Seri haberleşme ekranında okunan değerin yanına Limit yazdırıldı.
  delay(1000); // 1 saniye aralıklarla değer gösterilecek.
  if (gas_limite>400){ // Gaz limiti ayarı yapıldı. İstediğiniz değeri yapabilirsiniz. Gaz limiti 270'den büyükse...
  Serial.print("Gaz Limiti Asildi!!!  "); // Seri haberleşme ekranında Gaz Limiti Aşıldı yazısı yazdırıldı.
  digitalWrite(led1, LOW); // Mavi LED lojik 0 yapıldı.
  digitalWrite(led2, HIGH); // Kırmızı LED lojik 1 yapıldı.
  digitalWrite(buzzer, HIGH); // Buzzer çalıştırıldı.
   } 
  else{ // Eğer gaz limiti 270'den düşükse...
  Serial.println("Gaz Limiti Normal"); // Seri haberleşme ekranında Gaz Limiti Normal yazısı yazdırıldı.
  digitalWrite(led1, HIGH); // Mavi LED lojik 1 yapıldı.
  digitalWrite(led2, LOW); // Kırmızı LED lojik 0 yapıldı.
  digitalWrite(buzzer, LOW); // Buzzer kapatıldı.
}
  // ISI - NEM
  analoggerilim = analogRead(sensor1); //A0'den değeri ölç
  analoggerilim = (analoggerilim/1023)*5000;//değeri mV'a dönüştr 
  sicaklik = analoggerilim /10,0; // mV'u sicakliğa dönüştür
  Serial.print("Isı Nem Ölçer:  ");
  Serial.println(sicaklik);
  Serial.println("\n");
  delay(1000);

  // SICAKLIK
  float lm35_okunan_deger= analogRead(lm_35);     //analog değeri değişkene atadık
  float analog_sicaklik=(lm35_okunan_deger/1023)*5000;  //okunan değeri analog sıcaklık bilgisine atadık
  float digital_sicaklik= analog_sicaklik/10.0;     //analog sıcaklığı Digital sıcak çevirdik
 
  if(digital_sicaklik>45){
  digitalWrite(kirmizi_led,HIGH);
  digitalWrite(yesil_led,LOW);}          //sıcaklık 30 derece üstünde ise kırmızı led yansın
 
  else{
  digitalWrite(yesil_led,HIGH);          // diğer durumda yeşil led yansın kırmızı led sönsün
  digitalWrite(kirmizi_led,LOW);}

  //Bluetooth (LED)
  if (Serial.available()){
   int data = Serial.read();
   delay(100);
   if(data=='1'){
     digitalWrite(led,1);
   }
      if(data=='0'){
     digitalWrite(led,0);
   }
   delay(100);
  }

  //Bluetooth'dan Okuma ve USB Seriye Yazma (Servo)
  if(bluetooth.available()> 0 )
  {
    int servopos = bluetooth.read();
    Serial.println(servopos); 
    myservo.write(servopos);
  }

}
