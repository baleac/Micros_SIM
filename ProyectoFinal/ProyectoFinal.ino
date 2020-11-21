#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"
const char* ssid = "MicrosLunes";
const char* password = "hola1234";
const int ledPin = 2;
const int ledPin2 = 12;
const int ledPin3 = 13;
const int ledPin4 = 14;
const int ledPin5 = 15;
String ledState;
String ledState2;
String ledState3;
String ledState4;
String ledState5;
AsyncWebServer server(80);
// Replaces placeholder with LED state value
String processor(const String& var){
  Serial.println(var);
  if(var == "STATE"){
    if(digitalRead(ledPin)){
      ledState = "ON";
    }
    else{
      ledState = "OFF";
    }
    Serial.print(ledState);
    return ledState;
  }
  return String();
}
String processor2(const String& var){
  Serial.println(var);
  if(var == "STATE2"){
    if(digitalRead(ledPin2)){
      ledState2 = "ON";
    }
    else{
      ledState2 = "OFF";
    }
    Serial.print(ledState2);
    return ledState2;
  }
  return String();
}

String processor3(const String& var){
  Serial.println(var);
  if(var == "STATE3"){
    if(digitalRead(ledPin3)){
      ledState3 = "ON";
    }
    else{
      ledState3 = "OFF";
    }
    Serial.print(ledState3);
    return ledState3;
  }
  return String();
}

String processor4(const String& var){
  Serial.println(var);
  if(var == "STATE4"){
    if(digitalRead(ledPin4)){
      ledState4 = "ON";
    }
    else{
      ledState4 = "OFF";
    }
    Serial.print(ledState4);
    return ledState4;
  }
  return String();
}

String processor5(const String& var){
  Serial.println(var);
  if(var == "STATE5"){
    if(digitalRead(ledPin5)){
      ledState5 = "ON";
    }
    else{
      ledState5 = "OFF";
    }
    Serial.print(ledState5);
    return ledState5;
  }
  return String();
}



void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  // Connect to Wi-Fi
 WiFi.softAP(ssid, password);
 IPAddress myIP = WiFi.softAPIP();
 Serial.print("AP IP address: ");
 Serial.println(myIP);
 server.begin();
 Serial.println("Server started");
  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/style.css", "text/css");
  });

  
  //Lights 

  
  // Route to set GPIO to HIGH
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  // Route to set GPIO to LOW
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  server.on("/on2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });
  // Route to set GPIO to LOW
  server.on("/off2", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin2, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor2);
  });

  server.on("/on3", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin3, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor3);
  });
  // Route to set GPIO to LOW
  server.on("/off3", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin3, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor3);
  });

    server.on("/on4", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin4, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor4);
  });
  // Route to set GPIO to LOW
  server.on("/off4", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin4, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor4);
  });

    server.on("/on5", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin5, HIGH);
    request->send(SPIFFS, "/index.html", String(), false, processor5);
  });
  // Route to set GPIO to LOW
  server.on("/off5", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin5, LOW);
    request->send(SPIFFS, "/index.html", String(), false, processor5);
  });
  // Start server
  server.begin();
}
void loop(){
}
