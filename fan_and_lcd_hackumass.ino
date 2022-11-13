#include <LiquidCrystal.h>
LiquidCrystal lcd (2,3,4,5,6,7);
int red_light_pin= 11;
int green_light_pin = 10;
int blue_light_pin = 9;
int motorPin = 8;

void setup() {
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
}
void loop() {
  int onTime = 30000;  // milliseconds to turn the motor on
  int offTime = 30000; // milliseconds to turn the motor off

  char * greenStr = "you can do this!";
  char * yellowStr = "hang in there...";
  char * redStr = "time to chill!  ";
  int textDelay = 100; // milliseconds between each character
  
  //Start work
  RGB_color(0, 255, 0); // Green
  analogWrite(motorPin, 0);
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(greenStr[i]);
    delay(textDelay);
  }
  load(offTime);               // delay for offTime milliseconds

  //Approaching break
  lcd.clear();
  RGB_color(255, 255, 0); // Yellow//
  analogWrite(motorPin, 128);  // turn the motor off
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(yellowStr[i]);
    delay(textDelay);
  }
  load(onTime);
 

  //Take a break
  lcd.clear();
  RGB_color(255, 0, 0); // Red
  analogWrite(motorPin, 255); // turn the motor on (full speed)
  lcd.print("You should take a break!");
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(redStr[i]);
    delay(textDelay);
  }
  load(onTime);               // delay for onTime milliseconds
  lcd.clear();
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
void speedUpandDown()
{
  int speed;
  int delayTime = 20; // milliseconds between each speed step

  // accelerate the motor
  for(speed = 0; speed <= 255; speed++)
  {
    analogWrite(motorPin,speed);  // set the new speed
    delay(delayTime);             // delay between speed steps
  }
  // decelerate the motor
  for(speed = 255; speed >= 0; speed--)
  {
    analogWrite(motorPin,speed);  // set the new speed
    delay(delayTime);             // delay between speed steps
  }
}


// Input a speed from 0-255 over the Serial port
void serialSpeed()
{
  int speed;

  Serial.println("Type a speed (0-255) into the box above,");
  Serial.println("then click [send] or press [return]");
  Serial.println();  // Print a blank line

  // In order to type out the above message only once,
  // we'll run the rest of this function in an infinite loop:

  while(true)  // "true" is always true, so this will loop forever.
  {
    // Check to see if incoming data is available:
    while (Serial.available() > 0)
    {
      speed = Serial.parseInt();  // parseInt() reads in the first integer value from the Serial Monitor.
      speed = constrain(speed, 0, 255); // constrains the speed between 0 and 255
                                        // because analogWrite() only works in this range.

      Serial.print("Setting speed to ");  // feedback and prints out the speed that you entered.
      Serial.println(speed);

      analogWrite(motorPin, speed);  // sets the speed of the motor.
    }
  }
}
void load(int tDelay) {
    delay(1000);
    for (int i = 0; i < 16; i++) {
      if (i != 0) {
      int j;
      char loadStr[16];
      for (j = 0; j < (16-i); j++) {
        loadStr[j] = '-';
      }
      for (; j < 16; j++) {
        loadStr[j] = ' ';
      }
     lcd.setCursor(0, 1);
     lcd.print(loadStr);
     Serial.println(loadStr);
      }
    delay(tDelay/16);
      
  }
}