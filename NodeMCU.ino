#include <ESP8266WiFi.h>
#include <Arduino.h> 
String apiKey = "U0E594NYGMDKU48F";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "Haris5g";  // name of your wifi
const char *pass =  "Haris137";  // password of your wifi
const char* server = "api.thingspeak.com";

 
WiFiClient client;
#include <SoftwareSerial.h>
SoftwareSerial esp (D5,D6);
 
void setup() 
{
       esp.begin(115200);
       Serial.begin(115200);
       delay(10);
       pinMode(pir_sensor,INPUT);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{

   if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
    {  
      if (esp.available()>0){
        int pir = esp.read();
        Serial.println("receiving");

        if (int pir = 1){
       String postStr = apiKey;
       postStr +="&field1=";
       postStr += String(pir);
       postStr += "\r\n\r\n";
       
       for (int j = 15; j > 0; j--){
       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(postStr.length());
       client.print("\n\n");
       client.print(postStr);
       delay(1000);
       Serial.print(j);
       }
      
       Serial.print("motion : ");
       Serial.print(pir);
       Serial.println(" , Send to Thingspeak.");
       delay(1000);
        }
    }
    else{
      int pir = 0;
      String postStr = apiKey;
       postStr +="&field1=";
       postStr += String(pir);
       postStr += "\r\n\r\n";

       client.print("POST /update HTTP/1.1\n");
       client.print("Host: api.thingspeak.com\n");
       client.print("Connection: close\n");
       client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
       client.print("Content-Type: application/x-www-form-urlencoded\n");
       client.print("Content-Length: ");
       client.print(postStr.length());
       client.print("\n\n");
       client.print(postStr);

       Serial.print("motion : ");
       Serial.print(pir);
       Serial.println(" , Send to Thingspeak.");
      }
    
    }
   client.stop();

  // thingspeak needs minimum 15 sec delay between updates
}
