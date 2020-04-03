#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  String data;
  bool touchStatus;
} struct_message;




String Brailleconverter(char letter){
	if(letter == 'A')
	{
		return "100000";
	}
	else if(letter == 'B')
	{
		return "101000";
	}
	else if(letter == 'C')
	{
		return "110000";
	}else if(letter == 'D')
	{
		return "110100";
	}else if(letter == 'E')
	{
		return "100100";
	}else if(letter == 'F')
	{
		return "111000";
	}else if(letter == 'G')
	{
		return "111100";
	}else if(letter == 'H')
	{
		return "101100";
	}else if(letter == 'I')
	{
		return "011000";
	}else if(letter == 'J')
	{
		return "011100";
	}else if(letter == 'K')
	{
		return "100010";
	}else if(letter == 'L')
	{
		return "101010";
	}else if(letter == 'M')
	{
		return "110010";
	}else if(letter == 'N')
	{
		return "110110";
	}else if(letter == 'O')
	{
		return "100110";
	}else if(letter == 'P')
	{
		return "111010";
	}else if(letter == 'Q')
	{
		return "111110";
	}else if(letter == 'R')
	{
		return "101110";
	}else if(letter == 'S')
	{
		return "011010";
	}else if(letter == 'T')
	{
		return "011110";
	}else if(letter == 'U')
	{
		return "100011";
	}else if(letter == 'V')
	{
		return "101011";
	}else if(letter == 'W')
	{
		return "011101";
	}else if(letter == 'X')
	{
		return "110011";
	}else if(letter == 'Y')
	{
		return "110111";
	}else if (letter == 'Z')
	{
		return "100111";
	}
	else if (letter == ' ')
	{
		return "000000";
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
	else if (letter == " ")
	{
		return "000000";
	}
	else
	{
	return "error";
	}
	
}



// Create a struct_message called myData
struct_message myData;

static volatile uint8_t touch_count1, touch_count2, touch_count3; 

// touch_count3 = 0;
// touch_count1 = 0;
// touch_count2 = 0;

const int touch_pin_13 = 13;
const int touch_pin_12 = 12;
const int touch_pin_14 = 14;
const int touch_pin_27 = 27;
int reading1, reading2, reading3, reading4;
String finger4, finger5, finger6, Alphabet_code;
// String transmit[128] = {};
String transmit = "";
String reverse_convert;

int cnt_tx_array = 0;
// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("touchStatus: ");
  Serial.println(myData.touchStatus);
}
 
void setup() {
  // Initialize Serial Monitor
  pinMode(touch_pin_13, INPUT);
  pinMode(touch_pin_12, INPUT);
  pinMode(touch_pin_14, INPUT);
  pinMode(touch_pin_27, INPUT);
  Serial.begin(9600);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  if(myData.touchStatus == 1){
    Serial.println("Touch Read Started: ");
    reading1 = touchRead(touch_pin_13);
    reading2 = touchRead(touch_pin_12);
    reading3 = touchRead(touch_pin_14);
    Serial.print("Reading1 : ");
    Serial.println(reading1);
    Serial.print("Reading2 : ");
    Serial.println(reading2);
    Serial.print("Reading3 : ");
    Serial.println(reading3);
    delay(250);
    if(reading1 < 30){
      touch_count1 = touch_count1 + 1;
      Serial.print("touch_count1: ");
      Serial.println(touch_count1);
    }
    if(reading2 < 30){
      touch_count2 = touch_count2 + 1;
    }
    if(reading3 < 30){
      touch_count3 = touch_count3 + 1;
    }
    if(touch_count1 > 3){
      finger4 = "1";
    }
    else{
      finger4 = "0";
    }
    if(touch_count2 > 3){
      finger5 = "1";
    }
    else{
      finger5 = "0";
    }
    if(touch_count3 > 3){
      finger6 = "1";
    }
    else{
      finger6 = "0";
    }
  }
  if(myData.touchStatus == 0){
    if((finger4 != "") && (finger5 != "") && (finger6 != "")){
      Alphabet_code = finger4 + finger5 + finger6;
    }
    touch_count3 = 0;
    touch_count1 = 0;
    touch_count2 = 0;
    Serial.print("Alphabet code: ");
    Serial.println(Alphabet_code);
    String Combined_code = myData.data + Alphabet_code;
    Serial.print("Combined code: ");
    Serial.println(Combined_code);
    if(Alphabet_code != ""){
      Serial.print("Alphabet code: ");
      Serial.println(Alphabet_code);
      reverse_convert = ReverseConversion(Combined_code);
      transmit = transmit + reverse_convert;
      Serial.print("Data for transmission: ");
      Serial.println(transmit);
      Alphabet_code = "";
      finger4 = "";
      finger5 = "";
      finger6 = "";
    }
    reading1 = 70;
    reading2 = 70;
    reading3 = 70;
    delay(1000);
  }
  
}