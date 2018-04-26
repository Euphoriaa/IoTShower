#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 3;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int tmpSensorPin = A0;

const int btnUP = 7, btnDWN = 8;
bool btnUPclicked = false;
bool btnDWNclicked = false;

float wantedTemp = 40.0;
float currentTemp = 59.453;

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

float measureTemp(){
   double val=analogRead(0);
  double fenya=(val/1023)*5;
  // Ohm Law r/100=fenya/(3.3-fenya)
  double r=fenya/(3.3-fenya)*100;
  currentTemp =  ( 1/(  log(r/10) /3000 + 1/(25+273.15)   )-273.15);
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
  lcd.print(")     ");
  Serial.println(currentTemp);
}



void setup() {
  Serial.begin(9600);
  pinMode(btnUP, INPUT_PULLUP);
  pinMode(btnDWN, INPUT_PULLUP);
  pinMode(tmpSensorPin, INPUT);
  
  lcd.begin(16, 2);

  
  printWntTmp();
  printCrntTmp();
}


void checkButtons(){
  if(digitalRead(btnUP) == LOW){
    if(!btnUPclicked){ //clicked
      wantedTemp++;
      printWntTmp();
      Serial.print("+");
      Serial.println(wantedTemp);
      btnUPclicked = true;
    }
  } else btnUPclicked = false;
    

  if(digitalRead(btnDWN) == LOW){
    if(!btnDWNclicked){ //clicked
      wantedTemp--;
      printWntTmp();
      Serial.print("-");
      Serial.println(wantedTemp);
      btnDWNclicked = true;
    }
  } else btnDWNclicked = false;
}

void loop() {
  checkButtons();
  measureTemp();
  printCrntTmp();
  delay(10);
}
