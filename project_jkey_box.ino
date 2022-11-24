#include <Adafruit_Fingerprint.h>

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

int relayPin = 23;

void setup() {
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(relayPin, OUTPUT);

   // set the data rate for the sensor serial port
 finger.begin(57600);
 
 if (finger.verifyPassword()) 
 {
   Serial.println("Fingerprint Sensor Connected");
 }
  digitalWrite(relayPin, LOW);
}

void loop() {
  getFingerprintIDez();
  delay(50);
}

int getFingerprintIDez() 
{
 uint8_t p = finger.getImage();
 if (p != FINGERPRINT_OK)  
 {
   Serial.println("Waiting For Valid Finger");
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
     return finger.fingerID;
  }
}
