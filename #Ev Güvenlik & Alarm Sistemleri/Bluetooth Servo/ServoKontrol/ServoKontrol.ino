#include <SoftwareSerial.h>

#include <Servo.h> 
Servo myservo;

int bluetoothTx = 10;
int bluetoothRx = 11;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  myservo.attach(9);
  //Setup usb serial connection to computer
  Serial.begin(9600);

  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()> 0 )
  {
    int servopos = bluetooth.read();
    Serial.println(servopos); 
    myservo.write(servopos);
  }


}
