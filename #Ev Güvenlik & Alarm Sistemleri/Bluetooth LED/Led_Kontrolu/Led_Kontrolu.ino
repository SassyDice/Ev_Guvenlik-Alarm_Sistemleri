int data;
int led=7;
void setup() {
  pinMode(led,OUTPUT);  
  Serial.begin(9600);
}
void loop() { 
  {
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
  }}}
