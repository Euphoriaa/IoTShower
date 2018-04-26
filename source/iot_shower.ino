#include <LiquidCrystal.h>
#include <Servo.h>

//pin layout
const uint16_t  d4 = 6, d5 = 5, d6 = 4, d7 = 3;
const uint16_t btn_temp_UP = 7, btn_temp_DWN = 8;
const uint16_t cold_valve = 9, warm_valve = 10;
const uint16_t rs = 12, en = 11;
const uint16_t btn_flow_up = A1;
const uint16_t btn_flow_dn = A2;
const int tmpSensorPin = A0;


Servo cold_servo;
Servo warm_servo;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


bool btnUPclicked = false;
bool btnDWNclicked = false;

float wantedTemp = 38;
float currentTemp = 38;
float p_correction = 1;//value to correct of error in p feedback
double waterflow = 0;// goes from 0-1





bool move_valve(Servo valve, uint16_t deg);
void checkButtons();
void measureTemp();//todo
void printWntTmp();
void printCrntTmp();
void p_feedback(int T, double waterflow);
void updateTmpFromSerial();

void setup() {
  Serial.begin(9600);
  pinMode(btn_temp_UP, INPUT_PULLUP);
  pinMode(btn_temp_DWN, INPUT_PULLUP);
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
  updateTmpFromSerial();
  delay(10);
}



void p_feedback(int T, double flow)
{//in_progress
  int cold_angle = cold_servo.read();
  int warm_angle = warm_servo.read();
  if (warm_angle < 180)
  {
    warm_angle += p_correction;//in_progress
  }
}

void measureTemp() {
  double val = analogRead(0);
  double fenya = (val / 1023) * 5;
  // Ohm Law r/100=fenya/(3.3-fenya)
  double r = fenya / (3.3 - fenya) * 100;
  currentTemp = (1 / (log(r / 10) / 3000 + 1 / (25 + 273.15)) - 273.15);
}

void updateTmpFromSerial() {
  while (Serial.available()) {
    char c = Serial.read();
    if (c & 0x80 == 0)// preset temp
      wantedTemp = c;
    else {
      if (c & 0x40 != 0)//neg
        wantedTemp += (c | 0x80);
      else
        wantedTemp += c & 0x7F;
    }
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

void checkButtons() {//todo:add check for flow buttons
  if (digitalRead(btn_temp_UP) == LOW) {
    if (!btnUPclicked) { //clicked
      wantedTemp++;
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
