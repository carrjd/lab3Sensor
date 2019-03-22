#include <NewPing.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <string.h>
 
const char* ssid = "";
const char* password = "";
/*
* Ultrasonic Sensor HC-SR04 and Arduino Tutorial
* Modified by James Carr for WIMOS D1 Mini
* by Dejan Nedelkovski,
* www.HowToMechatronics.com
*
*/
// defines pins numbers
const int trigPin = 4;
const int echoPin = 5;
const int maxDist = 200;
String ipAddr =""; //ip address of the light board
// defines variables
long duration;
int distance;
/*void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
}*/
NewPing sonar(trigPin, echoPin, maxDist); // NewPing setup of pins and maximum distance.
WiFiServer server(80);
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
}

void loop() {

 // HTTPClient http;
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  distance = sonar.ping_cm();
  Serial.print(distance); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  
  if (distance >=23 || distance ==0){
    Serial.print("green");
    stopLoop();
    killLight("yellow");
    killLight("red");
    lightOn("green");
    //lightOnTest();
    }
  if (distance < 23 && distance >=17){
    Serial.print("yellow");
    stopLoop();
    killLight("green");
    killLight("red");
    lightOn("yellow");
    }
  if (distance < 17 && distance >=7){
    Serial.print("red");
    stopLoop();
    killLight("green");
    killLight("yellow");
    lightOn("red");
    } 
  if (distance < 7 && distance > 0){
    Serial.print("loop");
    //startLoop();
    lightOn("red");
    lightOn("green");
    lightOn("yellow");
    }
  
}

void stopLoop(){
  Serial.println("Stop loop called");
   WiFiClient client = server.available();
  client.setTimeout(1000); 
  delay(300);
  if(client.connect(ipAddr,80)){
  Serial.println("Stop ");
//  Serial.print(LED);
  client.println("GET /timerLoop/stop");
  }  
  
  }
void startLoop(){
   WiFiClient client = server.available();
  client.setTimeout(1000); 
 // delay(300);
  if(client.connect(ipAddr,80)){
  Serial.println("Loop on!");
//  Serial.print(LED);
  client.println("GET /timerLoop/start");
  }  
  
  }
void killLight(String LED){
   WiFiClient client = server.available();
  client.setTimeout(1000); 
  //delay(300);
  if(client.connect(ipAddr,80)){
  Serial.println("Light off!");
  Serial.print(LED);
  client.println("GET /"+LED+"/off");
  }
  }
void lightOn(String LED){
//  bool gron=0;
  WiFiClient client = server.available();
  client.setTimeout(1000); 
 // delay(300);
  if(client.connect(ipAddr,80)){
  Serial.println("Light on!");
  Serial.print(LED);
//  Serial.println(gron);
//    HTTPClient http;

        
//        if(!gron){
       // client.println("GET /timerLoop/stop");
       // delay(10);
       // client.println();

       // gron=1;
       // delay(10);
       // client.println();
       // client.println("GET /yellow/off");
        //delay(10);
       // client.println();
       // client.println("GET /red/off");
        //delay(10);
       // client.println();
       client.println("GET /"+LED+"/on");
       // client.println();
        
        //client.println("GET /timerLoop/start");
        
  //  }

  }
  }

  void lightOnTest(){
    HTTPClient http;
        http.begin(String(ipAddr+"/green/on"));
        http.GET();
        delay(10);
        http.end();
  }

 /*  Old, not working get request code
  *   if (LED == "loop"){
        http.begin(String(ipAddr+"/timerLoop/start"));
        http.GET();
        http.end();
    }
    else{
        http.begin(String(ipAddr+"/timerLoop/stop"));
        http.GET();
        Serial.println(String(ipAddr+"/timerLoop/stop"));
       // delay(10);
        http.end();
        http.begin(String(ipAddr+"/green/on"));
        http.GET();
       // delay(10);
        http.end();
        http.begin(String(ipAddr+"yellow/off"));
        http.GET();
       // delay(10);
        http.end();
        http.begin(String(ipAddr+"red/off"));
        http.GET();
       // delay(10);
        http.end();
        http.begin(String(ipAddr+"/"+LED+"/on"));
        http.GET();
       // delay(10);
        http.end();
    }
  }*/
