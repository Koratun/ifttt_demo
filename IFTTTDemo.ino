#include<Arduino.h>
#include<WiFi.h>
#include<HTTPClient.h>
#include "secrets.h"

const char* resource = "/trigger/m5buttonPress/with/key/dkCtOfWB9-QK3nswzlW3-r";
const char* server = "maker.ifttt.com";

#ifndef ESP32
#define ESP32
#endif

#include<M5StickCPlus.h>

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    M5.begin();
    delay(1000);

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("IFTTT Demo");

    WiFi.begin(SSID, pass);
    Serial.print("Connecting to " + String(SSID));
    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
    }
    Serial.println("\nConnected!");
  

}

void loop() {
  // put your main code here, to run repeatedly:
    M5.update();
    if(M5.BtnA.wasPressed()){
        makeIFTTTRequest();
        M5.Lcd.println("Main button pressed.");
    }

}

void makeIFTTTRequest(){
    Serial.println("Connecting to " + String(server));

    HTTPClient http;
    http.begin(String("https://")+server+resource);

    int response = http.GET();

    if(response > 0){
        Serial.println("Response: " + String(response));
        Serial.println("Response body: " + http.getString());
    }
    else{
        Serial.println("Request failed");
    }

    http.end();

    // int retries = 5;
    // while(!client.connect(server, 80) && (retries-- > 0)){
    //     Serial.print(".");
    // }
    // if(!client.connected()){
    //     Serial.println("Did not connect");
    // }
    // Serial.println("Request resource: " + String(resource));

    // client.print(String("GET https://") + resource + " HTTP/1.1\r\n" + "Host: " + server 
    // + "\r\nAccept: */*\r\nConnection: close\r\n\r\n");

    // int timeout = 50;
    // while(!client.available() && timeout-- > 0){
    //     delay(100);
    // }

    // if(!client.available()){
    //     Serial.print("Did not connect to resource");
    // }

    // while(client.available()){
    //     Serial.write(client.read());
    // }

    // Serial.println("Closing connection.");
    // client.stop();
  
}