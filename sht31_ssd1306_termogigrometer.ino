#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_SHT31.h"
Adafruit_SHT31 sht31 = Adafruit_SHT31();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
int start_coor = 0;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  delay(10);
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64)
                     // this value is obtained by calibrating the scale with known weights; see the README for details
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(10, 8);
  display.print("111111");
  delay(500);
  display.display();
  display.display();
  sht31.begin(0x44);
}

void loop() {
  
  float t = sht31.readTemperature();
  int h = sht31.readHumidity();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
    //display.setCursor(0, 0);
  //display.print("T: ");

  if (! isnan(t)) {  // check if 'is not a number'
      display.setCursor(start_coor, start_coor);
      display.print(t); 
  } else { 
      display.setCursor(start_coor, start_coor);
      display.print("Err"); 
  }
  display.setTextSize(3);
  display.setCursor(start_coor + 100, start_coor);
  display.print("C");
  display.display();
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);                       // wait for a second
  t = sht31.readTemperature();
  h = sht31.readHumidity();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
    //display.setCursor(0, 0);
  //display.print("T: ");

  display.setTextSize(3);
  if (! isnan(h)) {  // check if 'is not a number'
      display.setCursor(start_coor + 30, start_coor);
      display.print(h);
  } else { 
      display.setCursor(start_coor + 30, start_coor);
      display.print("rr");
  }
    display.setCursor(start_coor + 80, start_coor);
  display.print(" %");
  //display.setCursor(40, 24);
  //display.print("Banya1");
  display.display();
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(2000); 
    if(start_coor == 0){
    start_coor++;
    } else if(start_coor == 1) {
      start_coor++; 
    }else if (start_coor == 2){
    start_coor++;
    }else if (start_coor == 3){
    start_coor = 0;
    }else {
      start_coor = 0;
    }
}
