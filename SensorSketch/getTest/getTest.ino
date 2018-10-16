#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <string.h>
 
const char* ssid = "UnimatrixZero";
const char* password = "novi145$";

String ipAddr ="192.168.43.179"; //ip address of the light board
WiFiServer server(80);
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
   server.begin();
  Serial.println("Server started");
 
  }
}

void loop() {
        WiFiClient client = server.available();
    client.setTimeout(1000); 
    if(client.connect(ipAddr,80)){
  /*HTTPClient http;
        http.begin("192.168.43.179/green/on");
        Serial.println("getting 192.168.43.179/green/on");
       int httpCode= http.GET();
        delay(10);
        http.end();*/
        client.println("GET /green/on");
        client.println();
    }
    delay(500);
  
}
