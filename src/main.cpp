#include <Arduino.h>
#include <Servo.h>
#include "ESP8266WiFi.h"
extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}
#include <WebSocketClient.h>

#include <Arduino.h>

//Private Config
#include "config.h"

//Pins
#define SERVO_PIN D0
#define LED_PIN D3

//Global variables
WebSocketClient webSocketClient;
WiFiClient client;
Servo contServo;
const int turnTime = 3000;

void wifiCheck(){
    if(WiFi.status() != WL_CONNECTED){
        Serial.print("Connecting to WiFi...");
    }
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        counter++;
        if(counter>=60){ //after 30 seconds timeout - reset board
            ESP.restart();
        }
    }
    Serial.println("");
}
void websocketLoad() {
    wifiCheck();
    if (client.connect(WEBSOCKET_URL, 80)) {
        Serial.println("Connected");
    } else {
        Serial.println("Connection failed.");
    }
    
    webSocketClient.path = "/";
    webSocketClient.host = strdup(WEBSOCKET_URL);
    if (webSocketClient.handshake(client)) {
        Serial.println("Handshake successful");
    } else {
        Serial.println("Handshake failed.");
    }
}

void turnServo(int speed, int duration){
    contServo.attach(SERVO_PIN);
    contServo.write(speed);
    delay(duration);
    contServo.write(90);
    contServo.detach();
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    //Setup wifi
    wifi_set_opmode(0x01);
    struct station_config wifi_config;
    memset(&wifi_config, 0, sizeof(wifi_config));
    strcpy((char*)wifi_config.ssid, AP_SSID);
    wifi_station_set_config(&wifi_config);
    wifi_station_clear_cert_key();
    wifi_station_clear_enterprise_ca_cert();
    wifi_station_set_wpa2_enterprise_auth(1);
    wifi_station_set_enterprise_username((uint8*)EAP_IDENTITY, strlen(EAP_IDENTITY));
    wifi_station_set_enterprise_password((uint8*)EAP_PASSWORD, strlen(EAP_PASSWORD));
    wifi_station_connect();
    websocketLoad();
    digitalWrite(LED_PIN, LOW);
}

std::vector<String> splitStringToVector(String msg, char delim){
  std::vector<String> subStrings;
  int j=0;
  for(int i =0; i < msg.length(); i++){
    if(msg.charAt(i) == delim){
      subStrings.push_back(msg.substring(j,i));
      j = i+1;
    }
  }
  subStrings.push_back(msg.substring(j,msg.length())); //to grab the last value of the string
  return subStrings;
}

void openWindow(){
    Serial.println("Opening Window!");
    turnServo(180, turnTime);
}

void closeWindow(){
    Serial.println("Closing Window!");
    turnServo(0, turnTime);
}

String data;
void loop() {
    if (client.connected()) {
        webSocketClient.getData(data);
        if (data.length() > 0) {
            Serial.print("Received data: ");
            Serial.println(data);
            std::vector<String> split_string = splitStringToVector(data.c_str(), ':');
            String msgType = split_string[0];
            String deviceName = split_string[1];
            String fname = split_string[2];
            String command = split_string[3];
            if(deviceName == "window" && fname == "power"){
                if(command == "off"){
                    closeWindow();
                }
                if(command == "on"){
                    openWindow();
                }
            }
            if(deviceName == "window" && fname == "color"){
                if(command == "dim"){
                    closeWindow();
                }
                if(command == "bright"){
                    openWindow();
                }
            }
        }
        data = "";
    } else {
        Serial.println("Client disconnected.");
        websocketLoad();
    }
}