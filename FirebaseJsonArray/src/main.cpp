#include <Arduino.h>
//Step 1. Include WiFi.h
#include <WiFi.h>
//Step 2. Include Firebase ESP32 library (this library)
#include <FirebaseESP32.h>
#include <FirebaseJson.h>

#define FIREBASE_HOST "https://braille-2d53c.firebaseio.com/"
#define FIREBASE_AUTH "uUaUJ7acCrajKdp1bRjLN9CKeedor5E3ISlQ8Bkd"
#define WIFI_SSID "anuja1"
#define WIFI_PASSWORD "ar3k57u4"

//Step 3. Declare the Firebase Data object in the global scope
FirebaseData firebaseData;
FirebaseJson jsonArray1;
FirebaseJson jsonArray2;
int randomNumber;
int randomNumber2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  //Step 4. Setup Firebase credential in setup()
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Step 5. Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  randomNumber = random(300);
  randomNumber2 = random(500);
  Serial.print("random Number: ");
  Serial.println(randomNumber);
  delay(1000);
  jsonArray1.set("FirstRandomNumber", randomNumber);
  jsonArray2.set("SecondRandomNumber", randomNumber2);
  Firebase.pushJSON(firebaseData, "test1", jsonArray1);
  Firebase.pushJSON(firebaseData, "test2", jsonArray2);
}