#include "TM1636.h"
#include "EEPROM.h"
TM1636 tm1636(7, 8);
int8_t disp[4];
int count = 0000;
int temp;
int keymenu = 11;
int keyup = 10;
int keydown = 9;
int loud = 6;

void setup()
{
  Serial.begin(9600);
  tm1636.init();
  pinMode(keymenu, INPUT_PULLUP);
  pinMode(keyup, INPUT_PULLUP);
  pinMode(keydown, INPUT_PULLUP);
  pinMode(loud, OUTPUT);
}

void loop()
{
  read_eeprom();
  convertArraytoInt();
  tm1636.display(disp);

  if (digitalRead(keymenu) == 0) {
    count = 0000;
    temp = count;
    calculate_LED(temp);
    write_eeprom();
    print_LED();
  }

  if (digitalRead(keyup) == 0) {
    count++;
    temp = count;
    calculate_LED(temp);
    write_eeprom();
    print_LED();
  }

  if (digitalRead(keydown) == 0) {
    count--;
    temp = count;
    calculate_LED(temp);
    write_eeprom();
    print_LED();
  }
}




void convertArraytoInt() {
  count = 0;
  count = count + (disp[0] * 1000);
  count = count + (disp[1] * 100);
  count = count + (disp[2] * 10);
  count = count + (disp[3] * 1);
}


void read_eeprom() {
  for (int i = 0; i < 4; i++) {
    disp[i] = EEPROM.read(i);
  }
}


void write_eeprom() {
  for (int i = 0; i < 4; i++) {
    EEPROM.write(i, disp[i]);
  }
}


void print_LED() {
  delay(20);
  digitalWrite(loud, HIGH);
  delay(30);
  tm1636.display(disp);
  digitalWrite(loud, LOW);
  Serial.print("Count = ");
  Serial.println(count);
  delay(100);
}


void calculate_LED(int temp) {
  disp[0] = temp / 1000;
  temp = temp % 1000;

  disp[1] = temp / 100;
  temp = temp % 100;

  disp[2] = temp / 10;
  temp = temp % 10;

  disp[3] = temp;
}

