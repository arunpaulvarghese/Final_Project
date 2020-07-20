#include <Firebase.h>  
#include <FirebaseArduino.h>  
#include <FirebaseCloudMessaging.h>  
#include <FirebaseError.h>  
#include <FirebaseHttpClient.h>  
#include <FirebaseObject.h>  
#include <ESP8266WiFi.h>  
#include <FirebaseArduino.h>  
  
// Set these to run example.  
#define FIREBASE_HOST "project-e58e9.firebaseio.com"  // database realtime database key
#define FIREBASE_AUTH "cI4y97HeouPM48AdhhNA92K1yFqdMdGZUno8jNxI"  //Server account,Database secrets key in firebase
#define WIFI_SSID "batman"  
#define WIFI_PASSWORD "batman123" 
int sensor = D7;
unsigned long start_time = 0;
unsigned long end_time = 0;
int steps=0;
float steps_old=0;
float temp=0;
float rps=0;
uint8_t Crashpin = D6;
bool CrashStatus = HIGH;
int n=0;
void setup() {  
  Serial.begin(9600);  
  delay(100);
  pinMode(Crashpin, INPUT);
    pinMode(sensor,INPUT);

  // connect to wifi.  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  
  Serial.print("connecting");  
  while (WiFi.status() != WL_CONNECTED) {  
    Serial.print(".");  
    delay(500);  
  }  
  Serial.println();  
  Serial.print("connected: ");  
  Serial.println(WiFi.localIP());//registered ip in serial monitor  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); 
  Serial.begin(9600);
  Serial.println(" STEPS - 0");
  Serial.println(" RPS   - 0.00"); 
}  



void loop()
{

 if(digitalRead (Crashpin)==LOW)
 {
  Serial.println("crashed");
  
  if(digitalRead(sensor))
  {
    steps=steps+1; 
    while(digitalRead(sensor));
    }
   Firebase.setFloat("Spped", steps); 
   delay(10000);
   if (Firebase.failed()) {  
      Serial.print("setting /number failed:");  
      Serial.println(Firebase.error());    
      return;  
  }  
  delay(1000); 

    temp=steps-steps_old;
    steps_old=steps;
    rps=(temp/20);
    delay(2000);
    Firebase.setFloat("Rotation", rps);

  Serial.print("Speed");  
  Serial.println(Firebase.getFloat("Spped"));  //getting value from firebase to serial monitor
  delay(1000);
    
  Serial.print("Rotation");  
  Serial.println(Firebase.getFloat("Rotation"));  //getting value from firebase to serial monitor
  delay(1000);

  String name = Firebase.pushInt("logs", n++);  //n=0 initialised gives the no of pushes to firebase
  // handle error  
  if (Firebase.failed()) {  
      Serial.print("pushing /logs failed:");  
      Serial.println(Firebase.error());    
      return;  
  }  
  Serial.print("pushed: /logs/");  
  Serial.println(name);  
  delay(1000);  
}
}
