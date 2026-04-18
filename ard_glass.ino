#include <Wire.h>
#include "BluetoothSerial.h"
BluetoothSerial btSerial;
#include <GyverOLED.h>
//#include <U8g2lib.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
#include <Wire.h>
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER, OLED_SPI, 8, 7, 6> oled;
GyverOLED<SSH1106_128x64> display;
// можно передать адрес: GyverOLED oled(0x3C);
// Pins

//#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const uint8_t set [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x70, 0xD8, 0x8C, 0x0C, 0x18, 0x10, 0x1E, 0x0F, 0x01, 0x01, 0x03, 0x1E,
0x10, 0x18, 0x0C, 0x8C, 0xD8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x66, 0x42, 0xC3, 0x81, 0x00,
0x00, 0x3C, 0x66, 0xC3, 0x81, 0x81, 0x81, 0x66, 0x3C, 0x00, 0x00, 0x81, 0xC3, 0x42, 0x62, 0x7E,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x1B, 0x31, 0x30, 0x18, 0x08, 0x78, 0xF0, 0x80, 0x80, 0xC0, 0x78,
0x08, 0x18, 0x30, 0x31, 0x1B, 0x0E, 0x00, 0x00,
};
const uint8_t right [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x98, 0xBC, 0xFC,
0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x03,
0x03, 0x03, 0x03, 0x03, 0x03, 0x23, 0x73, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t left [] PROGMEM = {
0x00, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xE0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F,
0x07, 0x07, 0x07, 0x07, 0x07, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F,
0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  
};
const uint8_t straight [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0xFC, 0xF8, 0xE0,
0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x01,
0x01, 0x00, 0x01, 0xFF, 0xFF, 0x01, 0x00, 0x01, 0x01, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t uturn [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF,
0xFF, 0xFF, 0x01, 0x01, 0x20, 0xE1, 0xFF, 0xFF, 0xFF, 0xFE, 0xE0, 0x20, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x0F, 0x0F, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07,
0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
const uint8_t call [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0xE0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFC, 0x70, 0x00, 0x00, 0x00, 0xA0, 0xA0,
0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0F, 0x3F, 0xFF,
0xFF, 0xF8, 0xE0, 0xC0, 0x00, 0x0D, 0x02, 0x08, 0x0F, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x1F, 0x1F, 0x1F,
0x3F, 0x1F, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 
};
String notification;
void setup() {
  // put your setup code here, to run once:
// oled.init();
// display.setWrap(true); // Enable word wrap
  display.init();
//setTime(12,19,0,5,8,22); 
  Serial.begin(9600);
  // Set interrupt pin as input
 Wire.begin();
 pinMode(2,OUTPUT);
//  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clear();
// display.drawBitmap(50, 33, right,24, 24);
  
 // display.clear();
 // display.drawBitmap(60, 60, right, 64, 64);
  btSerial.begin("navihud");
 
  display.setCursor(30,0);
  display.print("connect to app");
  display.setCursor(0,2);
  display.print("to start your journey");
  display.update();
}
String callline;
String currentData = "";
String inputString="";
void loop() {
  // put your main code here, to run repeatedly:
   
   String receivedData;
   const int maxCharsPerLine = 21;
//display.clear();

//  display.drawBitmap(50, 24, right, 128, 64);
  //oled.drawBitmap(50, 24, bitmap_32x32, 32, 32)
 /* if(Serial.available()){
  receivedData=Serial.readStringUntil('\n');

  }*/
if (btSerial.available()>0) {
    //char incomingChar = btSerial.read();
   // String recchar=btSerial.readString();
 //  inputString="";
   
    // receivedData = btSerial.readStringUntil('\n');
   // Serial.println(receivedData);
   // inputString=receivedData;
  
   /*// Serial.println(receivedData);
    delay(1000);
    //int textLength = inputString.length();
 int textLength = inputString.length();
  int currentLine = 0;

   for (int i = 0; i < textLength; i += maxCharsPerLine) {
    String line = inputString.substring(i, i + maxCharsPerLine);
    display.print(line);
    display.update();
    delay(1000); // Adjust the delay time for scrolling speed

    if (i + maxCharsPerLine < textLength) {
      display.clear();
      delay(1000); // Delay to show a new line
    }
  }*/
  
  //display.print(inputString);
//  display.update();

display.clear();
inputString = btSerial.readStringUntil('\n');
//display.setCursor(30,4);
    //display.print(inputString);
    
   if(inputString.startsWith("HUD")){
   // display.clear();
    //display.setCursor(30,4);
   // display.print("connected!");
    int hIndex = inputString.indexOf("HUD");

    if (hIndex != -1) {
      // "null" is found, so print the part before "null"
      String hNull = inputString.substring(0, hIndex);
    //display.update();
    display.clear();
    
    display.setCursor(0,0);
    display.print("");
    display.setCursor(30,4);
    display.print("connected!");
    
   }
   }
    
   // 
    //delay(6000);
    // Display the received data with word wrapping
    //int textLength = inputString.length();
    int nullIndex = inputString.indexOf("null");

    if (nullIndex != -1) {
      // "null" is found, so print the part before "null"
      String partBeforeNull = inputString.substring(0, nullIndex);
      
      Serial.println("Received: " + partBeforeNull);
      int textLength = partBeforeNull.length();
      display.setCursor(0,0);
    for (int i = 0; i < textLength; i += maxCharsPerLine) {
      String line = partBeforeNull.substring(i, min(i + maxCharsPerLine, textLength));
      display.println(line);
    }
    } else {
      // "null" is not found, so print the entire received string
     // Serial.println("Received: " + inputString);
    /* int textLength = inputString.length();
      display.setCursor(0,0);
    for (int i = 0; i < textLength; i += maxCharsPerLine) {
      String line = inputString.substring(i, min(i + maxCharsPerLine, textLength));
      display.println(line);
    }*/
    }
  
   /* display.setCursor(0,0);
    for (int i = 0; i < textLength; i += maxCharsPerLine) {
      String line = inputString.substring(i, min(i + maxCharsPerLine, textLength));
      display.println(line);
    }*/
     if (inputString.indexOf("right onto") != -1) {
      // Perform an action for "turn right"
      // For example, you can control a motor or an LED.
      Serial.println("Turning right");
      display.drawBitmap(50, 33, right,24, 24);
    }
    
    // Check if the received string contains "turn left"
    if (inputString.indexOf("left onto") != -1) {
      // Perform an action for "turn left"
      // For example, you can control a motor or an LED.
      Serial.println("left");
      display.drawBitmap(50, 33, left,24, 24);
    }
    if (inputString.indexOf("straight") != -1) {
      // Perform an action for "turn left"
      // For example, you can control a motor or an LED.
      Serial.println("Turning straight");
      display.drawBitmap(50, 33, straight,24, 24);
    }
   
    if (inputString.indexOf("u-turn") != -1 || inputString.indexOf("U-turn") != -1) {
      // Perform an action for "turn left"
      // For example, you can control a motor or an LED.
      Serial.println("Turning straight");
      display.drawBitmap(50, 33, uturn,24, 24);
    }
       if (inputString.indexOf("destination") != -1) {
      // Perform an action for "turn left"
      // For example, you can control a motor or an LED.
      Serial.println("destination arrived");
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
       delay(1000);
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
      delay(1000);
      digitalWrite(2,HIGH);

      delay(1000);

      digitalWrite(2,LOW);
     
    }
    int callIndex = inputString.indexOf("call");

    if (callIndex != -1) {
      // "null" is found, so print the part before "null"
      String callNull = inputString.substring(0, callIndex);
      
      Serial.println("Received: " +callNull);
      int callLength = callNull.length();
   //   display.setCursor(0,0);
    for (int i = 0; i < callLength; i += maxCharsPerLine) {
      String callline = callNull.substring(i, min(i + maxCharsPerLine, callLength));
     // display.println(line);
    }
    
     
    if (callline.indexOf("incoming")) {
      // Perform an action for "turn left"
      // For example, you can control a motor or an LED.
     display.clear();
      display.drawBitmap(50, 9, call,24, 24);
       display.setCursor(30,6);
      display.print("incoming call");
    }
    }
    display.update();
} 
   currentData = receivedData;
   



//display.clear();
}
