/* include this for i2c caling i2c functions */
#include <Wire.h>
/* include this for recieving incoming data from smartphone */
#include "BluetoothSerial.h"
/* initialize bluetooth class handle */
BluetoothSerial btSerial; 
/* include for using bigger version of 128x64 oled display */
#include <GyverOLED.h>
/* include these libraries for graphics related functions */
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
/*select the oled display resolution based on your oled model*/
//GyverOLED<SSD1306_128x32, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x32, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
//GyverOLED<SSD1306_128x64, OLED_BUFFER, OLED_SPI, 8, 7, 6> oled;
GyverOLED<SSH1106_128x64> display;
// можно передать адрес: GyverOLED oled(0x3C);
// Pins


/* set screen width*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
String callline;
String currentData = "";
String inputString="";
/* bitmap images of various functions in hex format as display expects in hex format */
/* Refer readme for more info in generating hex based images */
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
/* initialize the display */
  display.init();
  Serial.begin(9600); /* Set baud rate */
  // Set interrupt pin as input
  /* initialize i2c functions for display */
  Wire.begin();
  pinMode(2,OUTPUT);
/* Clear initial contents */
  display.clear();
  /* Initialize bluetooth name to be indentified in your android app you can change the discovery name */
  btSerial.begin("navihud");
  /* set the cursor to be printed */
  display.setCursor(30,0);
  display.print("connect to app");
  display.setCursor(0,2);
  display.print("to start your journey");
  display.update();
}

void loop() {
  // put your main code here, to run repeatedly:
  String receivedData;
  const int maxCharsPerLine = 21;
  if (btSerial.available()>0) {
    int currentLine = 0;
    display.clear();
    inputString = btSerial.readStringUntil('\n');
    if(inputString.startsWith("HUD")){
      int hIndex = inputString.indexOf("HUD");

      if (hIndex != -1) {
        // "null" is found, so print the part before "null"
        String hNull = inputString.substring(0, hIndex); 
        display.clear();
        display.setCursor(0,0);
        display.print("");
        display.setCursor(30,4);
        display.print("connected!");
      }
    }
    // Display the received data with word wrapping
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
    } 
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
      for (int i = 0; i < callLength; i += maxCharsPerLine) {
        String callline = callNull.substring(i, min(i + maxCharsPerLine, callLength));
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
    /* built in function that updates the display used along with print udated commony here */
    display.update();
  } 
   currentData = receivedData;
   




}
