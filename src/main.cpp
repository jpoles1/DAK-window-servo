#include <Arduino.h>
#include <Servo.h>
#include <WiFi.h>
#include "esp_wpa2.h"
#include <ArduinoWebsockets.h>
using namespace websockets;

//Private Config
#include "config.h"

//Pins
#define SERVO_PIN 13
#define LED_PIN 4

//Global variables
WebsocketsClient wsClient;
Servo contServo;
const int turnTime = 3000;

void turnServo(int speed, int duration){
    contServo.attach(SERVO_PIN);
    contServo.write(speed);
    delay(duration);
    contServo.write(90);
    contServo.detach();
}

void openWindow(){
    Serial.println("Opening Window!");
    turnServo(180, turnTime);
}

void closeWindow(){
    Serial.println("Closing Window!");
    turnServo(0, turnTime);
}

//Wifi Util Functions
void wifiCheck(){
    if(WiFi.status() != WL_CONNECTED){
        Serial.println("Connecting to WiFi...");
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

void onMessage(WebsocketsMessage msg) {
    if (msg.data() == "ping") {
        //webSocketClient.sendData("pong");
    } else {
        std::vector<String> split_string = splitStringToVector(msg.data().c_str(), ':');
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
}
void websocketLoad() {
    wifiCheck();
    String wsURL = String("/sync?room=") + SERVER_ROOMNAME + String("&key=") + SERVER_KEY;
    if (wsClient.connect(WEBSOCKET_URL, 80, wsURL)) {
        Serial.println("WS connected!");
    } else {
        Serial.println("WS connection failed!");
    }
    wsClient.onMessage(onMessage);
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);
    //Setup wifi
        //Setup wifi
	delay(10);
    //uint8_t new_mac[8] = {0x39,0xAE,0xA4,0x16,0x1F,0x08};
    //esp_base_mac_addr_set(new_mac);
    WiFi.disconnect(true);  //disconnect form wifi to set new wifi connection
    WiFi.mode(WIFI_STA); //init wifi mode
    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide identity
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY)); //provide username --> identity and username is same
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD)); //provide password
    esp_wpa2_config_t config = WPA2_CONFIG_INIT_DEFAULT(); //set config settings to default
    esp_wifi_sta_wpa2_ent_enable(&config); //set config settings to enable function
    WiFi.begin(AP_SSID);
    //WiFi.setHostname("ESPDAK");
    websocketLoad();

    digitalWrite(LED_PIN, LOW);
}

String data;
void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        if (wsClient.available()) {
            wsClient.poll();
        } else {
            websocketLoad();
        }
    } else {
        Serial.println("WiFi disconnected!");
        wifiCheck();
    }
    delay(500);
}