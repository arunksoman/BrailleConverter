#include <Arduino.h>

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


char message[] = "HELLO WORLD"; 
String transmit[120] = {"101100", "100100", "101010", "101010", "100110", "000000"};
int controller_pin[6] = {20, 21, 22, 23, 24, 25};
String braile;
String get_reverse;
int i, j;
void setup() {
	Serial.begin(9600);
	// put your setup code here, to run once:
	for(i=0;message[i]!='\0';i++){
		Serial.println(message[i]);
		braile = Brailleconverter(message[i]);
		Serial.println(braile);
		for(j=0;braile[j]!='\0';j++)
		{
		   if(braile[j]=='1'){
		   	 Serial.print(controller_pin[j]);
          Serial.println(" is high");
		   }
		   else{
		   	Serial.print(controller_pin[j]);
         Serial.println(" is low");
		   }
		}
		delay(1000); 

		Serial.println("----------------------------");
	}
	for(i=0;i<(sizeof(transmit)/sizeof(transmit[0]))-1;i++){
		// 
		Serial.println(transmit[i]);
		get_reverse = ReverseConversion(transmit[i]);
		if(get_reverse == "error"){
			break;
		}
		Serial.print(get_reverse);
	}
	Serial.println("");
}

void loop() {
  // put your main code here, to run repeatedly:
}