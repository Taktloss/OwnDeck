#include <Arduino.h>

/* @file 
|| @version 1.0
|| @author 
|| @contact 
||
|| @description
|| Simple Keypad with Mode Switching. Using a Pro Micro Controller.
|| #
*/

#include <Keypad.h>
#include <Keyboard.h>

const byte ROWS = 3; //three rows
const byte COLS = 4; //three columns

char systemKeys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'7','8','9','0'}
};

char gamingKeys[ROWS][COLS] = {
    {'1','2','3','4'},
    {'q','w','e','r'},
    {'z','x','9','0'}
};

byte rowPins[ROWS] = {2, 3, 4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 6, 7, 8}; //connect to the column pinouts of the keypad

Keypad systemKeypad = Keypad( makeKeymap(systemKeys), rowPins, colPins, ROWS, COLS );
Keypad gamingKeypad = Keypad( makeKeymap(gamingKeys), rowPins, colPins, ROWS, COLS );

String modes[] = {"gaming","system"};


void setup(){
  Serial.begin(115200);
  delay(100);
  Serial.print("Starte");
  delay(100);
  Keyboard.begin();
}

// Keyboard Switch
bool KeyboardMode = true;
String sKeyboardMode = modes[0];
char key;
  
void loop(){

  if(KeyboardMode)
    key = systemKeypad.getKey();
  else
    key = gamingKeypad.getKey();
  
  if (key){
    Serial.println(key);
  }

  switch(key){
    case '9': /* Keyboard.press(KEY_LEFT_ALT);
              Keyboard.press(' ');
              Keyboard.releaseAll(); */
              Keyboard.press(KEY_RETURN);
              Keyboard.releaseAll();
              break;
    case '0': if(KeyboardMode == true) {
                Serial.println("Gaming Keypad");
                KeyboardMode = false;
                sKeyboardMode = modes[0];
                Serial.println(sKeyboardMode);
              }
              else {
                Serial.println("System Keypad");
                KeyboardMode = true;
                sKeyboardMode = modes[1];
                Serial.println(sKeyboardMode);
              }
              break;
              
    default:  Keyboard.write(key);  
              break;
  }
}