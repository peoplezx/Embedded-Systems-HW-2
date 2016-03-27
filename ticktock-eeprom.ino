
#include <EEPROM.h>
#include "TM1636.h"
TM1636 tm1636(7,8);
int8_t disp[4];
int count = 1639;
int count1 = count;
int temp;
int keymenu = 11;
int keyup = 10;
int keydown = 9;
int soundd = 6;


void EEPROMWriteInt(int p_address, int p_value)
     {
     byte lowByte = p_value;
     
     Serial.println(lowByte);
     EEPROM.write(p_address, lowByte);
    
     }


unsigned int EEPROMReadInt(int p_address)
     {
     byte lowByte = EEPROM.read(p_address);
     
     return lowByte;
     }

     

void setup()
{
     Serial.begin(9600);
     
     
     Serial.print("Read the following int at the eeprom address 0: ");
     Serial.println(EEPROMReadInt(0), HEX);
  tm1636.init();
  pinMode(keymenu, INPUT_PULLUP);
  pinMode(keyup, INPUT_PULLUP);
  pinMode(keydown, INPUT_PULLUP);
  pinMode(soundd,OUTPUT);
}
void loop()
{
    
  
  disp[0]=EEPROMReadInt(0);
  disp[1]=EEPROMReadInt(1);
  disp[2]=EEPROMReadInt(2);
  disp[3]=EEPROMReadInt(3);
  tm1636.display(disp);
  
 if(digitalRead(keymenu) == 0){
  count =count1;
  temp=count;
  disp[0] = temp/1000;
  temp = temp%1000;
  
  disp[1] = temp/100;
  temp = temp%100;
  
  disp[2] = temp/10;
  temp =temp%10;

  disp[3] = temp;

   delay(10);
   digitalWrite(soundd,HIGH);
   while(digitalRead(keymenu)==0){
    
   }
    delay(10);
    digitalWrite(soundd,LOW);
  EEPROMWriteInt(0, disp[0]);
  EEPROMWriteInt(1, disp[1]);
  EEPROMWriteInt(2, disp[2]);
  EEPROMWriteInt(3, disp[3]);
  tm1636.display(disp);
  delay(100);
 }
 
 if(digitalRead(keyup) == 0){
  count = 0;
  
  count=count+(disp[0]*1000);
  count=count+(disp[1]*100);
  count=count+(disp[2]*10);
  count=count+(disp[3]*1);
  
  count++;
  temp=count;
  disp[0] = temp/1000;
  temp = temp%1000;
  
  disp[1] = temp/100;
  temp = temp%100;
  
  disp[2] = temp/10;
  temp =temp%10;

  disp[3] = temp;

   delay(10);
   digitalWrite(soundd,HIGH);
   while(digitalRead(keyup)==0){
    
   }
    delay(10);
    digitalWrite(soundd,LOW);

  EEPROMWriteInt(0, disp[0]);
  EEPROMWriteInt(1, disp[1]);
  EEPROMWriteInt(2, disp[2]);
  EEPROMWriteInt(3, disp[3]);
  tm1636.display(disp);
  delay(100);

  
 }
  if(digitalRead(keydown) == 0){
  count = 0;
  count=count+(disp[0]*1000);
  count=count+(disp[1]*100);
  count=count+(disp[2]*10);
  count=count+(disp[3]*1);
  count--;
  temp=count;
  disp[0] = temp/1000;
  temp = temp%1000;
  
  disp[1] = temp/100;
  temp = temp%100;
  
  disp[2] = temp/10;
  temp =temp%10;

  disp[3] = temp;

   delay(10);
   digitalWrite(soundd,HIGH);
   while(digitalRead(keydown)==0){
    
   }
    delay(10);
   digitalWrite(soundd,LOW);
  
  EEPROMWriteInt(0, disp[0]);
  EEPROMWriteInt(1, disp[1]);
  EEPROMWriteInt(2, disp[2]);
  EEPROMWriteInt(3, disp[3]);
  tm1636.display(disp);
  delay(100);

  
 }
  
}




