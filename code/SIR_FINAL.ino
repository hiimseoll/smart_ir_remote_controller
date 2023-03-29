#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <EEPROM.h>
#include <IRremote.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include <Adafruit_MLX90614.h>

#define OLED_RESET 13
#define IR_get 2

//=======BUTTONS======
int sig[]={11, 5, 4, 12, 8, 6};
#define shiftCursorBtn 7
#define add 9
#define del 10
//====================

IRrecv ir(IR_get);
decode_results result;
IRsend irsend;

Adafruit_SSD1306 display(OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

unsigned long codeSig[5][7];
int sign[3][3]={
  {11, 5, 4},
  {12, 8, 6},
  {10, 9, 7}
  };
int IRget();
int IRPutNec();
//int IRputRaw();
void ledOn();
void presetDel();
void SigDetected();
void shiftCursor();
void LetsStart();
void DisplayPreset();
void WriteData(int, String);
void ReadData();

int CURSOR=0;
int pressTime=0;
int presetCount=5;
int dataCount=0;
int checker=0;
int loc=1;

void setup() {
  Serial.begin(9600);
  for(int i=0; i<3; i++){
    for(int n=0; n<3; n++){
      pinMode(sign[i][n], INPUT_PULLUP);
    }
  }
  Serial.println("Adafruit MLX90614 test");
  mlx.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  LetsStart();
  ir.enableIRIn();
}

void loop() {
  DisplayPreset();
  if(digitalRead(shiftCursorBtn)==LOW){
    Serial.println("1");
    shiftCursor();
  }
  if (CURSOR < 3 && digitalRead(add) == LOW) {
    Serial.println("5");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("  ADD MODE");
    display.display();
    IRget();
  }
  else if(CURSOR>=3 && digitalRead(add) == LOW){
    Serial.println("2");
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("  FULL");
    display.display();
    delay(500);
  }
  if (CURSOR >= 1 && digitalRead(del) == LOW) {
    Serial.println("3");
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("  DEL MODE");
    display.display();
    presetDel();
  }
  else if(CURSOR < 1 && digitalRead(del) == LOW){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("  NO DATA");
    display.display();
    delay(500);
  }
}

int IRget() {


  for(int i=0; i<9; i++){
    display.clearDisplay();
    display.setCursor(0,0);
    display.print(" PRESS BTN");
    display.display();
    if(digitalRead(del)==LOW){
      if(checker!=0){
        dataCount++;
        checker==0;
      }
      break;
    }
    for(int n=0; n<6; n++){
      switch(digitalRead(sig[n])){
        case LOW:
        while(true){
          if(ir.decode(&result)){
            codeSig[dataCount][n]=result.value;
            WriteData(loc, result.value); //here
            checker++;
          }
        }
        ir.resume();
        break;
        default:
        break;
      }
    }
  }

  /*
  for (int i = 0; i < 3; i++) {
    while (true) {
      if (ir.decode(&result)) {
        codeSig[i] = result.value;
        EEPROM.write(CURSOR*10, codeSig[i]);
        sig[i][1] = result.decode_type;
        sig[i][2] = result.rawlen;
        sig[i][3] = result.bits;
        Serial.println(result.bits);
        Serial.println(result.value, HEX);
        for (int n = 0; n < 4; n++) {
          Serial.println(sig[i][n]);
        }
        SigDetected();
        ir.resume();
        break;
      }
    }
  }*/
  CURSOR++;
}
int IRPutNec() {
  /*
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("  SEND");
  display.display();
  Serial.println("Nec mode");
  for (int i = 0; i < 3; i++) {
    bits[i] = sig[i][3];
  }
  while (true) {
    if (digitalRead(sig1) == LOW) {
      SigDetected();
      irsend.sendNEC(codeSig[0], 32);
      Serial.println(codeSig[0]);
      delay(500);
    }
    if (digitalRead(sig2) == LOW) {
      SigDetected();
      irsend.sendNEC(codeSig[1], 32);
      delay(500);
    }
    if (digitalRead(sig3) == LOW) {
      SigDetected();
      irsend.sendNEC(codeSig[2], 32);
      delay(500);
    }
    if(digitalRead(del)==LOW){
      break;
    }
  }*/
}

void LetsStart() {
  delay(500);
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 5);
  display.print("  SIR");
  display.display();
  delay(1500);
  display.clearDisplay();
  display.setTextSize(1);
  display.startscrolldiagright(0x00, 0x07);
  display.setCursor(10, 0);
  display.print("be useful");
  display.display();
  delay(2000);
  display.stopscroll();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(2);
  ReadData();
}

void SigDetected(){
  display.clearDisplay();
  display.print("   ! ! !");
  display.display();
  delay(800);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("  ADD MODE");
  display.display();
}

void presetDel(){
  delay(500);
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("  SURE ?");
  display.display();
  delay(500);
  while(true){
    if(digitalRead(del)==LOW){
      --CURSOR;
      --dataCount;
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(" SUCCESS");
      delay(500);
      display.display();
      break;
    }
    delay(10);
  }
}

void shiftCursor(){
  switch(dataCount){
    case 0:
    CURSOR++;
    break;
    case 1:
    CURSOR++;
    break;
    case 2:
    CURSOR++;
    break;
    case 3:
    CURSOR++;
    break;
    case 4:
    CURSOR=0;
    break;
    default:
    break;
  }
  delay(500);
}

void DisplayPreset(){
  switch(CURSOR){
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("  PRESET ");
    display.print(CURSOR); //*
    display.display();
    break;
    default:
    break;
  }
}

void ReadData(){
  int checkedDataCount=0, n=1;
  dataCount=int(EEPROM.read(0));
  char data[100];

  for(int i=1; checkedDataCount<dataCount; i++){
    data[i-1]=EEPROM.read(i);
    if(data[i-1]=='\0'){
      checkedDataCount++;
      codeSig[dataCount][n]
    }
  }
}

void WriteData(int loc, String sig){
  int dataSize=sig.length();
  for(int i=0; i<dataSize; i++){
    EEPROM.write(loc, sig[i]);
    loc++;
  }
  EEPROM.write(loc+dataSize, '\0');
  EEPROM.write(0, dataCount++);
}
