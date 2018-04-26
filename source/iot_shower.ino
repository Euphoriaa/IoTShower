#include <LiquidCrystal.h>
#include <Servo.h>


const int  d4 = 6, d5 = 5, d6 = 4, d7 = 3;
const int rs = 12, en = 11;  // for led disply pins defines
const int btnUP = 7, btnDWN = 8;
const int cold_valve=9,warm_valve=10;
const int tmpSensorPin = A0;

Servo cold_servo;
Servo warm_servo;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


bool btnUPclicked = false;
bool btnDWNclicked = false;

float wantedTemp = 40.0;
float currentTemp = 38;

bool move_valve(Servo valve, uint16_t deg);
void checkButtons();
void measureTemp();
void printWntTmp();
void printCrntTmp();
void FloatToString(char *str, float f, char size);

void FloatToString(char *str, float f, char size){
   char count;
  char* curr;
  int value;
  value = (int)f;
  itoa(value,str, 10);
  count = 0;
  curr = str;
  while(*curr != 0){
    ++count;
    ++curr;
  }
 
  if(count + 1 >= size){
    str[size - 1] = 0;
    return; 
  }
  
  str[count++] = '.';
  ++curr;
  f = f - (float)value;
  
  while(count + 1 < size){
    f *= 10;
    ++count;  
  }
  
  value = (int)f;
  itoa(value,curr, 10);
  str[size - 1] = 0;
  return;
 }

void setup() {
	Serial.begin(9600);
	pinMode(btnUP, INPUT_PULLUP);
	pinMode(btnDWN, INPUT_PULLUP);
	pinMode(tmpSensorPin, INPUT);

	lcd.begin(16, 2);

	printWntTmp();
	printCrntTmp();

	cold_servo.attach(cold_valve);
	warm_servo.attach(warm_valve);
}




void loop() {
	checkButtons();
	measureTemp();
	printCrntTmp();
	delay(10);
}



void printWntTmp(){
  lcd.setCursor(0, 0);
  char s[5];
  FloatToString(s, wantedTemp, 5);
  lcd.print(s);
  lcd.setCursor(4, 0);
  lcd.print((char)223);
}

void printCrntTmp(){
  lcd.setCursor(0, 1);
  lcd.print('(');
  char s[5];
  FloatToString(s, currentTemp, 5);
  lcd.print(s);
  lcd.setCursor(5, 1);
  lcd.print((char)223);
  lcd.print(')');
}


void checkButtons() {
	if (digitalRead(btnUP) == LOW) {
		if (!btnUPclicked) { //clicked
			wantedTemp++;
			printWntTmp();
			Serial.print("+");
			Serial.println(wantedTemp);
			btnUPclicked = true;
		}
	}
	else btnUPclicked = false;


	if (digitalRead(btnDWN) == LOW) {
		if (!btnDWNclicked) { //clicked
			wantedTemp--;
			printWntTmp();
			Serial.print("-");
			Serial.println(wantedTemp);
			btnDWNclicked = true;
		}
	}
	else btnDWNclicked = false;
}

bool move_valve(Servo valve, uint16_t deg)//WARNING when using dont call all the time if in a loop
{
	if (deg < 0 || deg>180)
		return false;
	else
	{
		valve.write(deg);
	}
	return true;
}

void measureTemp(){
   double val=analogRead(0);
  double fenya=(val/1023)*5;
  // Ohm Law r/100=fenya/(3.3-fenya)
  double r=fenya/(3.3-fenya)*100;
  currentTemp =  ( 1/(  log(r/10) /3000 + 1/(25+273.15)   )-273.15);
}
