#include <esp_now.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <esp_wifi.h>

#define FIREBASE_HOST "https://bailychat-10119.firebaseio.com/"
#define FIREBASE_AUTH "wczzrPh68mwLlKPuoM18EcaP68IKpGBiNkTTz52D"
#define WIFI_SSID "anuja1"
#define WIFI_PASSWORD "ar3k57u4"


FirebaseData firebaseData;

#define timeSeconds 5
// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0xAE, 0xCE, 0x38};
typedef struct struct_message {
  String data;
  bool clickStatus;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// Set GPIOs for LED and PIR Motion Sensor
const int send_PIN = 18;
const int FINGER1 = 19;
const int FINGER2 = 21;
const int FINGER3 = 22; 
String left_hand_fingers = "";
int controller_pin[3] = {13, 12, 14};
int i, j;
String braille;

// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
String msg_from_firebase;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void IRAM_ATTR sendClick() {
  Serial.println("I am Here!!!");
  startTimer = true;
  lastTrigger = millis();
  left_hand_fingers = "";
  left_hand_fingers = left_hand_fingers + String(digitalRead(FINGER1));
  left_hand_fingers = left_hand_fingers + String(digitalRead(FINGER2));
  left_hand_fingers = left_hand_fingers + String(digitalRead(FINGER3));
  myData.data = left_hand_fingers;
  myData.clickStatus = startTimer;
  Serial.printf("Readed fingers = %s", left_hand_fingers);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); 
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}
void WiFiReset() {
  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}


String Brailleconverter(char letter){
  if(letter == 'A')
  {
    return "100";
  }
  else if(letter == 'B')
  {
    return "101";
  }
  else if(letter == 'C')
  {
    return "110";
  }else if(letter == 'D')
  {
    return "110";
  }else if(letter == 'E')
  {
    return "100";
  }else if(letter == 'F')
  {
    return "111";
  }else if(letter == 'G')
  {
    return "111";
  }else if(letter == 'H')
  {
    return "101";
  }else if(letter == 'I')
  {
    return "011";
  }else if(letter == 'J')
  {
    return "011";
  }else if(letter == 'K')
  {
    return "100";
  }else if(letter == 'L')
  {
    return "101";
  }else if(letter == 'M')
  {
    return "110";
  }else if(letter == 'N')
  {
    return "110";
  }else if(letter == 'O')
  {
    return "100";
  }else if(letter == 'P')
  {
    return "111";
  }else if(letter == 'Q')
  {
    return "111";
  }else if(letter == 'R')
  {
    return "101";
  }else if(letter == 'S')
  {
    return "011";
  }else if(letter == 'T')
  {
    return "011";
  }else if(letter == 'U')
  {
    return "100";
  }else if(letter == 'V')
  {
    return "101";
  }else if(letter == 'W')
  {
    return "011";
  }else if(letter == 'X')
  {
    return "110";
  }else if(letter == 'Y')
  {
    return "110";
  }else if (letter == 'Z')
  {
    return "100";
  }
  else if (letter == ' ')
  {
    return "000";
  }
  else
  {
  return "error";
  }
  
}

void setup() {
  WiFiReset();
  // Serial port for debugging purposes
  Serial.begin(9600);
  
  // PIR Motion Sensor mode INPUT_PULLUP
  pinMode(send_PIN, INPUT_PULLUP);
  pinMode(FINGER1, INPUT_PULLUP);
  pinMode(FINGER2, INPUT_PULLUP);
  pinMode(FINGER3, INPUT_PULLUP);
   for(i=0; i<3
   ;i++){
    pinMode(controller_pin[i], OUTPUT);
  }
  // Set motionSensor pin as interrupt, assign interrupt function and set RISING mode
  attachInterrupt(digitalPinToInterrupt(send_PIN), sendClick, FALLING);
   // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  delay(1000);
  uint8_t primaryChan = 0;
  wifi_second_chan_t secondChan = WIFI_SECOND_CHAN_NONE;
  ESP_ERROR_CHECK(esp_wifi_start());
  ESP_ERROR_CHECK(esp_wifi_set_promiscuous(true));
  esp_wifi_set_channel(primaryChan, secondChan);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, 0);
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
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  // Firebase.reconnectWiFi(true);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Current time
  now = millis();
  // Turn off the LED after the number of seconds defined in the timeSeconds variable
  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
    Serial.println("Not Here");
    startTimer = false;
    myData.data = left_hand_fingers;
    myData.clickStatus = startTimer;
    esp_err_t result1 = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
    if (result1 == ESP_OK) {
      Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }
    //limit_consecutive_trigger = false;
  }
  if (Firebase.getString(firebaseData, "/AndroidStatus")) {
    Serial.println(firebaseData.stringData());
    String readStatus = firebaseData.stringData();
    if (readStatus == "false" && Firebase.getString(firebaseData, "/AndroidMessage")) {
        Serial.println(firebaseData.stringData());
        msg_from_firebase = firebaseData.stringData();
    for(i=0;msg_from_firebase[i]!='\0';i++){
          Serial.println(msg_from_firebase[i]);
          braille = Brailleconverter(msg_from_firebase[i]);
          Serial.println(braille);
          for(j=0;braille[j]!='\0';j++)
          {
             if(braille[j]=='1'){
               Serial.print(controller_pin[j]);
               Serial.println(" is high");
               digitalWrite(controller_pin[j], HIGH);
             }
             else{
              Serial.print(controller_pin[j]);
              Serial.println(" is low");
              digitalWrite(controller_pin[j], LOW);
             }
          }
          delay(4000);
          Serial.println("-----------------");
        }
        Serial.println("Conversion Successful");
        delay(2000);
        Firebase.setString(firebaseData, "/AndroidStatus", "true");
    }
  }
}
