#include <esp_now.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <esp_wifi.h>

#define timeSeconds 2
#define FIREBASE_HOST "https://bailychat-10119.firebaseio.com/"
#define FIREBASE_AUTH "wczzrPh68mwLlKPuoM18EcaP68IKpGBiNkTTz52D"
#define WIFI_SSID "anuja1"
#define WIFI_PASSWORD "ar3k57u4"


// Timer: Auxiliary variables
unsigned long now = millis();
unsigned long lastTrigger = 0;
boolean startTimer = false;
FirebaseData firebaseData;
FirebaseJson json;
// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  String data;
  bool clickStatus;
} struct_message;

// Create a struct_message called myData
struct_message myData;
String right_hand_finger = "";
String combined_code = "";
String transmit_message = "";
String letter;
int transmit;int controller_pin[3] = {13, 12, 14};
int i, j;
String braille;
String msg_from_firebase;

String Brailleconverter(char letter){
  if(letter == 'A')
  {
    return "000";
  }
  else if(letter == 'B')
  {
    return "000";
  }
  else if(letter == 'C')
  {
    return "000";
  }else if(letter == 'D')
  {
    return "100";
  }else if(letter == 'E')
  {
    return "100";
  }else if(letter == 'F')
  {
    return "000";
  }else if(letter == 'G')
  {
    return "100";
  }else if(letter == 'H')
  {
    return "100";
  }else if(letter == 'I')
  {
    return "000";
  }else if(letter == 'J')
  {
    return "100";
  }else if(letter == 'K')
  {
    return "010";
  }else if(letter == 'L')
  {
    return "010";
  }else if(letter == 'M')
  {
    return "010";
  }else if(letter == 'N')
  {
    return "110";
  }else if(letter == 'O')
  {
    return "110";
  }else if(letter == 'P')
  {
    return "010";
  }else if(letter == 'Q')
  {
    return "110";
  }else if(letter == 'R')
  {
    return "110";
  }else if(letter == 'S')
  {
    return "010";
  }else if(letter == 'T')
  {
    return "110";
  }else if(letter == 'U')
  {
    return "011";
  }else if(letter == 'V')
  {
    return "011";
  }else if(letter == 'W')
  {
    return "101";
  }else if(letter == 'X')
  {
    return "011";
  }else if(letter == 'Y')
  {
    return "111";
  }else if (letter == 'Z')
  {
    return "111";
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

String ReverseConversion(String letter){
  if(letter == "100000")
  {
    return "A";
  }
  else if(letter == "101000")
  {
    return "B";
  }
  else if(letter == "110000")
  {
    return "C";
  }else if(letter == "110100")
  {
    return "D";
  }else if(letter == "100100")
  {
    return "E";
  }else if(letter == "111000")
  {
    return "F";
  }else if(letter == "111100")
  {
    return "G";
  }else if(letter == "101100")
  {
    return "H";
  }else if(letter == "011000")
  {
    return "I";
  }else if(letter == "011100")
  {
    return "J";
  }else if(letter == "100010")
  {
    return "K";
  }else if(letter == "101010")
  {
    return "L";
  }else if(letter == "110010")
  {
    return "M";
  }else if(letter == "110110")
  {
    return "N";
  }else if(letter == "100110")
  {
    return "O";
  }else if(letter == "111010")
  {
    return "P";
  }else if(letter == "111110")
  {
    return "Q";
  }else if(letter == "101110")
  {
    return "R";
  }else if(letter == "011010")
  {
    return "S";
  }else if(letter == "011110")
  {
    return "T";
  }else if(letter == "100011")
  {
    return "U";
  }else if(letter == "101011")
  {
    return "V";
  }else if(letter == "011101")
  {
    return "W";
  }else if(letter == "110011")
  {
    return "X";
  }else if(letter == "110111")
  {
    return "Y";
  }else if (letter == "100111")
  {
    return "Z";
  }
  else if (letter == "000000")
  {
    return " ";
  }
  else
  {
  return "CHNR";
  }
  
}

// Set GPIOs for LED and PIR Motion Sensor
const int send_FIREBASE_PIN = 18;
const int FINGER1 = 19;
const int FINGER2 = 21;
const int FINGER3 = 22; 
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("clickStatus: ");
  Serial.println(myData.clickStatus);
  Serial.print("data from left side: ");
  Serial.println(myData.data);
  if(myData.clickStatus == 1){
    right_hand_finger = "";
    right_hand_finger = right_hand_finger + String(digitalRead(FINGER1));
    right_hand_finger = right_hand_finger + String(digitalRead(FINGER2));
    right_hand_finger = right_hand_finger + String(digitalRead(FINGER3));
    Serial.print("Right Hand Finger: ");
    Serial.println(right_hand_finger);
  }
  if(myData.clickStatus == 0){
    combined_code = "";
    combined_code = myData.data + right_hand_finger;
    Serial.print("combined Code: ");
    Serial.println(combined_code);
    letter = ReverseConversion(combined_code);
    transmit_message = transmit_message + letter;
    Serial.print("Message For Transmission: ");
    Serial.println(transmit_message);
  }
}
void IRAM_ATTR send_to_FireBase(){
//  startTimer = true;
//  lastTrigger = millis();
//  if(transmit_message != ""){
//        //Firebase.setString(firebaseData, "/msgFromESP32", transmit_message);
//        //Serial.println("data Send successfully");
//        //delay(3000);
//        //transmit_message = "";
//        // Firebase.setString(firebaseData, "/msgReadStatus", "true");
//        //delay(3000);
//        json.set("message", transmit_message);
//        json.set("username", "ESP32");
//        if (Firebase.pushJSON(firebaseData, "/chat", json)) { 
//          Serial.println(firebaseData.dataPath());
//    
//          Serial.println(firebaseData.pushName());
//        
//          Serial.println(firebaseData.dataPath() + "/" + firebaseData.pushName());
//          transmit_message = "";
//          Firebase.setString(firebaseData, "/AndroidStatus", "true");
//        }
//        else {
//          Serial.println(firebaseData.errorReason());
//        }
//    }
}
void WiFiReset() {
  WiFi.persistent(false);
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

void setup() {
  WiFiReset();
  // put your setup code here, to run once:
  // Serial port for debugging purposes
  Serial.begin(9600);
  // PIR Motion Sensor mode INPUT_PULLUP
  myData.clickStatus = false;
  pinMode(send_FIREBASE_PIN, INPUT_PULLUP);
  pinMode(FINGER1, INPUT_PULLUP);
  pinMode(FINGER2, INPUT_PULLUP);
  pinMode(FINGER3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(send_FIREBASE_PIN), send_to_FireBase, FALLING);
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
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
    // put your main code here, to run repeatedly:
}


void loop() {
  if (digitalRead(send_FIREBASE_PIN) == HIGH){
    if(transmit_message != ""){
        //Firebase.setString(firebaseData, "/msgFromESP32", transmit_message);
        //Serial.println("data Send successfully");
        //delay(3000);
        //transmit_message = "";
        // Firebase.setString(firebaseData, "/msgReadStatus", "true");
        //delay(3000);
        json.set("message", transmit_message);
        json.set("username", "ESP32");
        if (Firebase.pushJSON(firebaseData, "/chat", json)) { 
          Serial.println(firebaseData.dataPath());
    
          Serial.println(firebaseData.pushName());
        
          Serial.println(firebaseData.dataPath() + "/" + firebaseData.pushName());
          transmit_message = "";
          Firebase.setString(firebaseData, "/AndroidStatus", "true");
        }
        else {
          Serial.println(firebaseData.errorReason());
        }
    }
  }
//  now = millis();
//  if(startTimer && (now - lastTrigger > (timeSeconds*1000))) {
//    Serial.println("Not Here");
//    startTimer = false;
//    startTimer = false;
//  }
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
