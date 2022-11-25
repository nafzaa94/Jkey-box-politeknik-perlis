#include <Adafruit_Fingerprint.h>
#include "Arduino.h"
#include "PCF8574.h"
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set i2c address
PCF8574 pcf8574(0x39);
unsigned long timeElapsed;

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

// Wifi network station credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5526673896:AAHMnqahDTIHZhZQZJlCdC01hHSiuGls4Js"

#define CHAT_ID "574706553"

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
  lcd.begin();
  lcd.backlight();
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

 lcd.setCursor(3, 0);
 lcd.print("SILA PILIH");
 lcd.setCursor(6, 1);
 lcd.print("KUNCI");
}

void loop() {
  valswitch1 = pcf8574.digitalRead(P0);
  valswitch2 = pcf8574.digitalRead(P1);
  valswitch3 = pcf8574.digitalRead(P2);
  valswitch4 = pcf8574.digitalRead(P3);
  valswitch5 = pcf8574.digitalRead(P4);

  if (valswitch1 == HIGH && state1 == 0){
    Serial.println("kunci 1 ambik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI SATU");
    lcd.setCursor(4, 1);
    lcd.print("DIAMBIL");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state1 = 1;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }
  if (valswitch1 == LOW && state1 == 1) {
    Serial.println("kunci 1 letak balik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI SATU");
    lcd.setCursor(2, 1);
    lcd.print("DIKEMBALIKAN");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state1 = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }

  if (valswitch2 == HIGH && state2 == 0){
    Serial.println("kunci 2 ambik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI DUA");
    lcd.setCursor(4, 1);
    lcd.print("DIAMBIL");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state2 = 1;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }
  if (valswitch2 == LOW && state2 == 1) {
    Serial.println("kunci 2 letak balik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI DUA");
    lcd.setCursor(2, 1);
    lcd.print("DIKEMBALIKAN");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state2 = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }

  if (valswitch3 == HIGH && state3 == 0){
    Serial.println("kunci 3 ambik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI TIGA");
    lcd.setCursor(4, 1);
    lcd.print("DIAMBIL");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state3 = 1;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }
  if (valswitch3 == LOW && state3 == 1) {
    Serial.println("kunci 3 letak balik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI TIGA");
    lcd.setCursor(2, 1);
    lcd.print("DIKEMBALIKAN");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state3 = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }

  if (valswitch4 == HIGH && state4 == 0){
    Serial.println("kunci 4 ambik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI EMPAT");
    lcd.setCursor(4, 1);
    lcd.print("DIAMBIL");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state4 = 1;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }
  if (valswitch4 == LOW && state4 == 1) {
    Serial.println("kunci 4 letak balik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI EMPAT");
    lcd.setCursor(2, 1);
    lcd.print("DIKEMBALIKAN");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state4 = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }

  if (valswitch5 == HIGH && state5 == 0){
    Serial.println("kunci 5 ambik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI LIMA");
    lcd.setCursor(4, 1);
    lcd.print("DIAMBIL");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state5 = 1;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
    }
  if (valswitch5 == LOW && state5 == 1) {
    Serial.println("kunci 5 letak balik");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("KUNCI LIMA");
    lcd.setCursor(2, 1);
    lcd.print("DIKEMBALIKAN");
    bot.sendMessage(CHAT_ID, "Bot started up", "");
    state5 = 0;
    delay(1000);
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("SILA PILIH");
    lcd.setCursor(6, 1);
    lcd.print("KUNCI");
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
