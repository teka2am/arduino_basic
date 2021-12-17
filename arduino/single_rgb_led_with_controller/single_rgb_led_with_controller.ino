/*
 *  Single RGB LED controller
 *  Arduino Rev 3
 *  Using 3 resistors (as Red-Green-Blue) to change LED color
 *  
 *  This script is using LCD with RGB background
 *  Need to import Grove - LCD RGB Backlight library
 *  https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight
 *  
 *  Created 17 Dec 2021 - by teka2am
 */
 
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

// Define LED Pins
#define LED_R 11
#define LED_G 10
#define LED_B 9

// Define Control Pins
#define CTRL_R A0
#define CTRL_G A1
#define CTRL_B A2

// Input variable
int read_CTRL_R;
int read_CTRL_G;
int read_CTRL_B;

int value_CTRL_R = 0;
int value_CTRL_G = 0;
int value_CTRL_B = 0;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  pinMode(CTRL_R, INPUT);
  pinMode(CTRL_G, INPUT);
  pinMode(CTRL_B, INPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);
}

// Set color for LEDs (Value 0 to 255) 
void setColorLED(int red, int green, int blue)
{
  analogWrite(LED_R, 255 - red);
  analogWrite(LED_G, 255 - green);
  analogWrite(LED_B, 255 - blue);
}

void loop() {
  //Read value from controller
  read_CTRL_R = analogRead(CTRL_R);
  read_CTRL_G = analogRead(CTRL_G);
  read_CTRL_B = analogRead(CTRL_B);

  // Convert analog value to 0 to 255 value
  int new_value_CTRL_R = map(read_CTRL_R, 0, 660, 0, 255);
  int new_value_CTRL_G = map(read_CTRL_G, 0, 660, 0, 255);
  int new_value_CTRL_B = map(read_CTRL_B, 0, 660, 0, 255);

  // Count changed range
  int changedValue_R = value_CTRL_R - new_value_CTRL_R;
  int changedValue_G = value_CTRL_G - new_value_CTRL_G;
  int changedValue_B = value_CTRL_B - new_value_CTRL_B;

  // Ensure all value is positive
  changedValue_R = changedValue_R < 0 ? changedValue_R * -1 : changedValue_R;
  changedValue_G = changedValue_G < 0 ? changedValue_G * -1 : changedValue_G;
  changedValue_B = changedValue_B < 0 ? changedValue_B * -1 : changedValue_B;

  // If changed value is greather than 2 then update LCD screen
  if ((changedValue_R > 2) || (changedValue_G > 2) || (changedValue_B > 2)) {
    value_CTRL_R = new_value_CTRL_R;
    value_CTRL_G = new_value_CTRL_G;
    value_CTRL_B = new_value_CTRL_B;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RGB Controler");
    
    lcd.setCursor(0, 1);
    lcd.print(value_CTRL_R);
    lcd.print(", ");
    lcd.print(value_CTRL_G);
    lcd.print(", ");
    lcd.print(value_CTRL_B);

    delay(50);
  }

  // Set color for LED and LCD
  lcd.setRGB(value_CTRL_R, value_CTRL_G, value_CTRL_B);
  setColorLED(value_CTRL_R, value_CTRL_G, value_CTRL_B);
}
