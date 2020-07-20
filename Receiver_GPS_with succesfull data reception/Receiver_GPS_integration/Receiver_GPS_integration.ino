#include <ESP8266WiFi.h>
WiFiServer server(80);
IPAddress IP(192,168,4,15);
IPAddress mask = (255, 255, 255, 0);
void setup() 
{
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
 WiFi.softAP("Wemos_AP", "Wemos_comm");
 WiFi.softAPConfig(IP, IP, mask);
 server.begin();
 Serial.println();
 Serial.println("accesspoint_bare_01.ino");
 Serial.println("Server started.");
 Serial.print("IP: "); Serial.println(WiFi.softAPIP());
 Serial.print("MAC:"); Serial.println(WiFi.softAPmacAddress());
}

void loop()
{
 WiFiClient client = server.available();
 if (!client) 
 {
  return;
 }

 String request1 = client.readStringUntil('\r');
 String request2 = client.readStringUntil('\n');
 Serial.print("Byte sent to the station: ");
 Serial.println(client.println(request1));
 Serial.println(request1);
 Serial.println(client.println(request2));
  Serial.println(request2);

 client.flush();


}
