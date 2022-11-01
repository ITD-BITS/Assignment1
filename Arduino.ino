int led = 13;
int pin = 3;

int value = 0;
int pirState = LOW;
#include <SoftwareSerial.h>
SoftwareSerial espSerial (7,6); //GPIO Pin 7 RX and Pin 6 TX
void setup(){
  pinMode(led, OUTPUT);
  pinMode(pin, INPUT);
  Serial.begin(115200);
  espSerial.begin(115200);
  delay(2000);
}

void loop(){
  value = digitalRead(pin);
  if(value == HIGH){
    digitalWrite(led, HIGH);

    if(pirState == LOW){
      Serial.println("Motion Detected");
      pirState = HIGH;
      int sd = 1;
      espSerial.write(sd);
    }
  }else{
    digitalWrite(led, LOW);
    if(pirState == HIGH){
      Serial.println("Motion Ended");
      pirState = LOW;
      int sd = 0;
      espSerial.write(sd);
        }
    }
  }
