#include <Adafruit_Fingerprint.h>
#include "Arduino.h"
#include "PCF8574.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Set i2c address
PCF8574 pcf8574(0x39);
unsigned long timeElapsed;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

// Wifi network station credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "XXXXXXXXX:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"

#define CHAT_ID "175753388"

WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

int relayPin = 21;
uint8_t valswitch1 = 0;
uint8_t valswitch2 = 0;
uint8_t valswitch3 = 0;
uint8_t valswitch4 = 0;
uint8_t valswitch5 = 0;
int state1 = 0;
int state2 = 0;
int state3 = 0;
int state4 = 0;
int state5 = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(relayPin, OUTPUT);
  pcf8574.pinMode(P0, INPUT);
  pcf8574.pinMode(P1, INPUT);
  pcf8574.pinMode(P2, INPUT);
  pcf8574.pinMode(P3, INPUT);
  pcf8574.pinMode(P4, INPUT);

  if (pcf8574.begin()){
    Serial.println("OK");
  }else{
    Serial.println("KO");
  }

  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

   // set the data rate for the sensor serial port
 finger.begin(57600);
 
 if (finger.verifyPassword()) 
 {
   Serial.println("Fingerprint Sensor Connected");
 }
}

void loop() {
  valswitch1 = pcf8574.digitalRead(P0);
  valswitch2 = pcf8574.digitalRead(P1);
  valswitch3 = pcf8574.digitalRead(P2);
  valswitch4 = pcf8574.digitalRead(P3);
  valswitch5 = pcf8574.digitalRead(P4);

  if (valswitch1 == HIGH && state1 == 0){
    Serial.println("kunci 1 ambik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state1 = 1;
    delay(2000);
    }
  else {
    Serial.println("kunci 1 letak balik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state1 = 0;
    delay(2000);
    }

  if (valswitch2 == HIGH && state2 == 0){
    Serial.println("kunci 2 ambik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state2 = 1;
    delay(2000);
    }
  else {
    Serial.println("kunci 2 letak balik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state2 = 0;
    delay(2000);
    }

  if (valswitch3 == HIGH && state3 == 0){
    Serial.println("kunci 3 ambik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state3 = 1;
    delay(2000);
    }
  else {
    Serial.println("kunci 3 letak balik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state3 = 0;
    delay(2000);
    }

  if (valswitch4 == HIGH && state4 == 0){
    Serial.println("kunci 4 ambik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state4 = 1;
    delay(2000);
    }
  else {
    Serial.println("kunci 4 letak balik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state4 = 0;
    delay(2000);
    }

  if (valswitch5 == HIGH && state5 == 0){
    Serial.println("kunci 5 ambik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state5 = 1;
    delay(2000);
    }
  else {
    Serial.println("kunci 5 letak balik");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state5 = 0;
    delay(2000);
    }
  
  getFingerprintIDez();
  delay(50);
}

int getFingerprintIDez() 
{
 uint8_t p = finger.getImage();
 if (p != FINGERPRINT_OK)  
 {
   return -1;
 }
 
 p = finger.image2Tz();
 if (p != FINGERPRINT_OK)  
 {
   Serial.println("Error Try Again");
   return -1;
 }
 
   p = finger.fingerFastSearch();
   if (p != FINGERPRINT_OK)  {
     Serial.println("Door Unlocked Welcome");
     digitalWrite(relayPin, HIGH);
     delay(5000);
     digitalWrite(relayPin, LOW);
     return finger.fingerID;
  }
}
