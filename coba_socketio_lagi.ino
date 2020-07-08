#include <ESP8266WiFi.h>
#include <SocketIoClient.h>
//DHT SETTINGS
#include "DHT.h"
#define DHTTYPE DHT11
// DHT SensorPIN SETTING
#define DHTPin D4  
// WIFI SETTINGS
const char *ssid = "Koen_DILAN!";
const char *password = "";
//SCKETIO SETTINGS
const char *socketServer = "192.168.43.154";
const int port = 4000;

SocketIoClient socket;

  
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                
float Temperature;
float Humidity;
//////////////////////////

void setup() {
  Serial.begin(115200); //SERIAL PORT INICIALIZATION
  dht.begin();    // DHT11 SENSOR INICIALIZATION 
  //WIFI CONFIG/RESET
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  WiFi.begin(ssid, password);//CONNECT TO WIFI

  while (WiFi.status() != WL_CONNECTED) //WAITING FOR CONNECTED
  {
    delay(100);
    Serial.print(".");
  }  
  
///CONNECT WITH SERVER
  socket.begin(socketServer,port);
}


void loop() {
    socket.loop();
    
        Temperature = dht.readTemperature(); // Gets the values of the temperature
        Humidity = dht.readHumidity(); // Gets the values of the humidity
        
        char temperatureBuffer[20];
        char *dataTemperature;
        dataTemperature = dtostrf(Temperature, 6, 2, temperatureBuffer);

        String dataTemp = String(Temperature,2);
        
//        char humidityBuffer[20];
//        char *dataHumidity;
//        dataHumidity = dtostrf(Humidity, 6, 2, humidityBuffer);
        
        socket.emit("new user", "\"P1471984882\"");
        socket.emit("chat", dataTemperature);
         
//        socket.emit("new user", "\"P1471984882\"");
//        socket.emit("chat", "\"hallo\"");

  delay(1000);
}
