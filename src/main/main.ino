#include <LCD_I2C.h>
#include <RtcDS1302.h>

// Code based on the following tutorial:
// https://www.youtube.com/watch?v=MfmK55TREuQ&ab_channel=EnjoyMechatronics

// I2C Display Configs
#define address 0x27 // MAY CHANGE, ADAPT ACCORDINGLY
#define columns 16
#define rows 2


// RTC DS1302 Module Configs
#define pinRST 2
#define pinDAT 4
#define pinCLK 5

// Instanciate the Display and RTC
LCD_I2C lcd(0x27, columns, rows);

ThreeWire myWire(pinDAT, pinCLK, pinRST);
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(9600);
  // Start Display Module
  lcd.begin();
  lcd.backlight();

  Serial.println("compiled: ");
  Serial.print(__DATE__);
  Serial.print(" | ");
  Serial.println(__TIME__);

  // Start RTC Module
  Rtc.Begin();
  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetIsWriteProtected(false);
  Rtc.SetIsRunning(true);
  Rtc.SetDateTime(currentTime);
}

void loop() {
  // Get date/time from RTC Module
  RtcDateTime now = Rtc.GetDateTime();
  
  // Update Display Module
  // First Row (Date)
  lcd.clear();
  lcd.print("Date: ");
  lcd.print(now.Day());
  lcd.print("/");
  lcd.print(now.Month());
  lcd.print("/");
  lcd.print(now.Year());

  // Second Row (Time)
  
  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(now.Hour());
  lcd.print("h");
  lcd.print(now.Minute());
  lcd.print("m");
  lcd.print(now.Second());
  lcd.print("s");

  delay(1000);
}
