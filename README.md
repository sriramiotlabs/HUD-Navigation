📍 NaviHUD – Arduino Navigation Display using Android Notifications
🚀 Overview

NaviHUD is a smart navigation assistant that bridges an Android smartphone and an Arduino-based OLED display. It extracts real-time navigation directions from mobile notifications (e.g., Google Maps) and displays them visually on an OLED screen connected to the Arduino.

This creates a Heads-Up Display (HUD)-like system for navigation without constantly checking your phone.

💡 Concept

The system works by:

Capturing navigation notifications from an Android device using a Notification Listener Service.
Parsing direction-related text (e.g., “turn right”, “go straight”).
Sending the processed data via Bluetooth to Arduino.
Displaying direction arrows and text on an OLED display.

This reduces distractions and enables hands-free navigation assistance.

🧠 System Architecture
Mappls (Android)
        ↓
Notification Listener Service (Android App)
        ↓
Text Processing (Extract directions)
        ↓
Bluetooth Transmission
        ↓
Arduino (ESP32)
        ↓
OLED Display (Direction + Text + Icons)

🔧 Hardware Requirements
ESP32 (with Bluetooth support)
OLED Display (128x64, SH1106 / SSD1306)
Connecting wires
Optional:
Buzzer / LED (for alerts)

📱 Software Requirements
Android Side
Custom Android app with:
Notification Listener Service
Bluetooth communication module
Arduino Side
Libraries used:
BluetoothSerial
GyverOLED
Wire
Adafruit_GFX
Adafruit_SSD1306 (optional)

⚙️ Features

✔ Real-time navigation display
✔ Direction icons (Left, Right, Straight, U-turn)
✔ Incoming call detection
✔ Destination alert (LED blinking)
✔ Text wrapping for long instructions
✔ Bluetooth-based wireless communication

🖥️ How It Works (Code Explanation)
1. Bluetooth Communication

ESP32 acts as a Bluetooth device named:

navihud
Receives navigation text from Android.
2. Notification Parsing

The Arduino checks for keywords in received data:

Keyword	Action
"right onto"	Show right arrow
"left onto"	Show left arrow
"straight"	Show straight arrow
"u-turn"	Show U-turn icon
"destination"	Blink LED alert
"call"	Show call icon
3. OLED Display Handling
Uses bitmap arrays for icons:
Right arrow
Left arrow
Straight
U-turn
Call symbol
Displays text with line wrapping (max 21 chars per line)
4. Example Flow
User starts navigation on phone

Notification appears:

Turn right onto MG Road
Android app captures it
Sends via Bluetooth
Arduino receives and:
Displays text
Shows ➡️ arrow icon


🔌 Setup Instructions
Arduino
Install required libraries
Upload the code to ESP32
Connect OLED via I2C
Power the board
Android
Build/install your custom app
Enable:
Notification Access
Bluetooth permissions
Pair with device: navihud
📸 Output Example
"Turn left onto street" → ⬅️ icon + text
"Go straight" → ⬆️ icon
"U-turn ahead" → 🔄 icon
"Incoming call" → 📞 icon


steps to create bitmap images
1. search the image you want in black and white format
2. copy or save image
3. open the paint and load image
4. set the resolution to 128x64 /* here resolution depends on height and width of the display */
5. change the format to monochrome image format and save /* The display supports black and white format only */

steps to generate hex codes for the image
1. open lcd assistant software
2. load the image created before
3. Save the image
4. open the file in notepad and copy the hex codes and can be used in code

⚠️ Limitations
Depends on notification text format
Works best with consistent phrasing (e.g., Google Maps)
Bluetooth latency may cause slight delay
No GPS processing on Arduino (phone-dependent)

📚 Use Cases
Bike navigation HUD
Car dashboard assistant
Smart helmet systems
Accessibility for visually distracted users
