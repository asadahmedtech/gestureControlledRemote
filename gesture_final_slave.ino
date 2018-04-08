#include <LiquidCrystal.h>
#include <Wire.h>
#include<Time.h>


int x = 0;
char* menu[] = {"AC           ","FAN-1        ","FAN-2        ","SPEAKER      ","LIGHT-2      "};
char* menu1[] = {"AC","FAN-1","FAN-2","SPEAKER","LIGHT-2"};
int vol[] = {50,50,50,50,50};
int ti[] = {0,0,0,0,0};
char* m2[] = {"TEMP ","SPD  ","SPD  ","VOL  ","INT  "};
char* menu3[] = {"TEMPERATURE","SPEED","SPEED","VOLUME","INTENSITY"};
bool power[] = {false,false,false,false,false};
int pos=0;
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  
  Wire.begin(9); 
  // Attach a function to trigger when something is received.
  
}

void loop() {
  Wire.onReceive(receiveEvent);
  // set the cursor to column 0, line 1
  lcd.setCursor(0,0);
  lcd.print(menu[pos]);
  if(power[pos]){lcd.print(" ON");}
  else if(!power[pos]){lcd.print("OFF");}
//  // (note: line 1 is the second row, since counting begins with 0):
  
  lcd.setCursor(0,1);
  // print the number of seconds since reset:
  lcd.print(m2[pos]);
  lcd.print(" AT :");
  lcd.print(vol[pos]);
  lcd.print(" T");
  if(power[pos]){ti[pos]=second();}else{ti[pos]=00;}
  lcd.print(ti[pos]);
}

void receiveEvent(int bytes) {
  
  x = Wire.read();    // read one character from the I2C
  
  if(x!=-1){
  lcd.setCursor(0,0);
  lcd.print("                 ");
  lcd.setCursor(0,1);
  lcd.print("                 ");}
  if(x == 1){pos++;}
  if(x == 2){pos--;}
  if(pos<0){pos+=5;}
  if(pos>4){pos-=5;}
  if(x == 4){vol[pos]+=4;}
  if(x == 3){vol[pos]-=4;}
  if(vol[pos]<0){vol[pos]+=100;}
  if(vol[pos]>100){vol[pos]-=100;}
  if(x == 5){power[pos]= !power[pos];}
  if(x!=-1){
      Serial.print(menu1[pos]);
      if(power[pos]){Serial.print(" ON ");}else{Serial.print(" OFF ");}
      Serial.print(" AT ");
      Serial.print(vol[pos]);
      Serial.print(" ");
      Serial.print(menu3[pos]);
      Serial.println();
    }
}

