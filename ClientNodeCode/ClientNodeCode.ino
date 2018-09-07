#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
#include <string.h>

#define dev0 '0'
#define dev1 '1'

const char* ssid = "Lenovo K50a40";
const char* password = "88888888";

const char* host = "http://node-iot-smartclass.herokuapp.com";

int vcc=D1;
int pin = D3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
  delay(10);

//  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  digitalWrite(vcc,HIGH);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
//    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
//    digitalWrite(LED_BUILTIN, LOW);
    Serial.print(".");
       
  }
  Serial.println("");
  Serial.println("WiFi connected");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(3*1000);
  Serial.print("");
  Serial.println("Loop started");

  HTTPClient http;
  http.begin("http://node-iot-smartclass.herokuapp.com/getStatus/0");
  int httpCode = http.GET();
  String payload = http.getString();
  
  Serial.print("httpCode: ");
  Serial.println(httpCode);
  Serial.print("payload: ");
  Serial.println(payload);
  http.end();

  if(httpCode != 200){
    return;
  }
  if(payload == "0"){
//    Serial.print("value: ");
//    Serial.println(payload);
//     digitalWrite(LED_BUILTIN, LOW);
     digitalWrite(pin, LOW);
     delay(10);
  }
  else{
//    Serial.print("value: ");
//    Serial.println(payload); 
//    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(pin, HIGH);
    delay(10);
  }

}
