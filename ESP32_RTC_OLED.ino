 #include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>

#define SCREEN_WIDTH 128 // OLED width, in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

RTC_DS1307 rtc;

// Create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Bitmap of arduino-icon image
const unsigned char arduino_icon [] PROGMEM = {
  // Your bitmap data here...
};

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);  // SDA on GPIO 21, SCL on GPIO 22

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 // rtc.adjust(DateTime(2024, 5, 24, 17,36, 0));
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  Serial.println(F("Initializing SSD1306 OLED..."));
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000); // Wait two seconds for initializing
  oled.setCursor(0, 0);
}

void loop() {
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  oled.clearDisplay(); // Clear display

  oled.setTextSize(2);         // Set text size
  oled.setTextColor(WHITE);    // Set text color
  oled.setCursor(20, 10);      // Set position to display
  oled.print(now.hour(), DEC); // Set text
  oled.print(":");             // Set text
  oled.print(now.minute(), DEC); // Set text
  oled.print(":");             // Set text
  oled.println(now.second(), DEC); // Set text

  oled.display(); // Display on OLED

  delay(1000); // Wait one second before updating
}

void displayBitmap() {
  oled.clearDisplay();
  oled.drawBitmap(0, 0, arduino_icon, 128, 64, WHITE);
  oled.display();
  delay(1000);
}
