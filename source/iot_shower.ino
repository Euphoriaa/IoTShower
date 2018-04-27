#include <LiquidCrystal.h>
#include <Servo.h>

#define flow_support false
#define servo//motor
#define potentiameter

//pin layout
const uint16_t  d4 = 6, d5 = 5, d6 = 4, d7 = 3;
const uint16_t btn_temp_UP = 7, btn_temp_DWN = 8;
const uint16_t cold_valve = 9, warm_valve = 10;
const uint16_t rs = 12, en = 11;
#if flow_support==true
const uint16_t btn_flow_up = A1;
const uint16_t btn_flow_dn = A2;
double waterflow = 0;// goes from 0-1
#endif
const int tmpSensorPin = A0;


Servo cold_servo;
Servo warm_servo;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


bool btnUPclicked = false;
bool btnDWNclicked = false;

bool water_on;

const uint16_t default_temp = 38;
const uint16_t default_degree = 0;//the value that water is off
float wantedTemp = default_temp;
float currentTemp = default_temp;//default also in frontend






#ifdef servo
bool move_valve(Servo valve, uint16_t deg);
void update_servo();
#endif
void checkButtons();
void measureTemp();//todo
void printWntTmp();
void printCrntTmp();
void updateTmpFromSerial();
void print_to_serial(uint16_t command);
#ifdef potentiameter
void led_show(int);
void p_feedback();
int p_error = 0;
#endif



void setup() {
	Serial.begin(115200);
	pinMode(btn_temp_UP, INPUT_PULLUP);
	pinMode(btn_temp_DWN, INPUT_PULLUP);
	pinMode(tmpSensorPin, INPUT);

	lcd.begin(16, 2);

	water_on = false;

	printWntTmp();
	printCrntTmp();
#ifdef servo
	cold_servo.attach(cold_valve);
	warm_servo.attach(warm_valve);
#endif
}




void loop() {
	while (1)
	{
		checkButtons();
		measureTemp();
		printCrntTmp();
		updateTmpFromSerial();
		update_servo();
		delay(5);
	}
}



#ifdef potentiameter
void measureTemp() {
	double val = analogRead(0);
	double fenya = (val / 1023) * 5;
	// Ohm Law r/100=fenya/(3.3-fenya)
	double r = fenya / (3.3 - fenya) * 100;
	currentTemp = (1 / (log(r / 10) / 3000 + 1 / (25 + 273.15)) - 273.15);
}
#endif // 

#ifndef potentiameter
void measureTemp() {
	double val = analogRead(0);
	double fenya = (val / 1023) * 5;
	// Ohm Law r/100=fenya/(3.3-fenya)
	double r = fenya / (3.3 - fenya) * 100;
	currentTemp = (1 / (log(r / 10) / 3000 + 1 / (25 + 273.15)) - 273.15);
}
#endif // !poentiameter



void print_to_serial(uint16_t command)
{
	while (Serial.available())
		updateTmpFromSerial();
	//if (command<2 && command>-1)
	if (command == 1 || command == -1)
		Serial.println(command);
}

void updateTmpFromSerial() {
	while (Serial.available()) {
		char c = Serial.read();
		if (c == 0xFF) {
			water_on = false;
		}
		else if (c == 0xFE) {
			water_on = true;
			wantedTemp = default_temp;
		}
		else {
			wantedTemp = c;
		}

		printWntTmp();//not sure
	}
	char c = Serial.read();
	Serial.println((unsigned char)c);
}

void printWntTmp() {
	lcd.setCursor(0, 0);
	char s[5];
	FloatToString(s, wantedTemp, 5);
	lcd.print(s);
	lcd.setCursor(4, 0);
	lcd.print((char)223);
}

void printCrntTmp() {
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
	if (digitalRead(btn_temp_UP) == LOW) {
		if (!btnUPclicked) { //clicked
			wantedTemp++;
			//todo
			//need for two way com
			//print_to_serial(1);
			printWntTmp();
			Serial.print("+");
			Serial.println(wantedTemp);
			btnUPclicked = true;
		}
	}
	else btnUPclicked = false;


	if (digitalRead(btn_temp_DWN) == LOW) {
		if (!btnDWNclicked) { //clicked
			wantedTemp--;
			//todo
			//need for two way com
			//print_to_serial(-1);
			printWntTmp();
			Serial.print("-");
			Serial.println(wantedTemp);
			btnDWNclicked = true;
		}
	}
	else btnDWNclicked = false;
}


#ifdef servo
bool move_valve(Servo valve, uint16_t deg)//WARNING when using dont call all the time if in a loop
{
	if (deg < 0 || deg>180)
		return false;
	else
	{
#ifdef potentiameter
		if (abs(deg - valve.read()) > 5)
		led_show(abs(deg - valve.read()));
#endif

		valve.write(deg);
	}
	return true;
}
#endif

void FloatToString(char *str, float f, char size) {
	char count;
	char* curr;
	int value;
	value = (int)f;
	itoa(value, str, 10);
	count = 0;
	curr = str;
	while (*curr != 0) {
		++count;
		++curr;
	}

	if (count + 1 >= size) {
		str[size - 1] = 0;
		return;
	}

	str[count++] = '.';
	++curr;
	f = f - (float)value;

	while (count + 1 < size) {
		f *= 10;
		++count;
	}

	value = (int)f;
	itoa(value, curr, 10);
	str[size - 1] = 0;
	return;
}

#ifdef potentiameter
void update_servo()
{
	if (water_on == false)
	{
		move_valve(warm_servo,default_degree);
	}
	else
	{
		p_feedback();
	}
}


void p_feedback()
{
	if (currentTemp > wantedTemp)
		p_error--;//need tom move down
	if (currentTemp < wantedTemp)
		p_error++;;//need to move up
	if (p_error > 0)
	{
		warm_servo.write(warm_servo.read() + p_error);
	}
}

void led_show(int)
{
	//todo
}
#endif
