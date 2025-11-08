#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

const char* ssid = "SHOIB";
const char* password = "#Shoib777";

AsyncWebServer server(80);

#define led1 12
#define led2 13
#define led3 14

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }


  WiFi.begin(ssid, password);


  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "/index.html", "text/html");

  });


  server.on("/led", HTTP_GET, [](AsyncWebServerRequest *request){
    String PinNo = request->getParam("id")->value();
    String state = request->getParam("state")->value();
    int ledPin = PinNo.toInt();
    int ledState = state.toInt();
    digitalWrite(ledPin, ledState);
    request->send(200, "text/plain", "OK");
  });


  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
}
