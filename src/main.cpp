#include <Arduino.h>
#include <Keypad.h>
#include <Joystick.h>

Joystick_ Joystick;

const int sensorPinRoll = A0;
const int sensorPinPitch = A1;
const int joystickXPin = A3;
const int joystickYPin = A2;

const int joystickBtnPin = 10;

const byte ROWS = 3;
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1', '2'},
    {'3', '4', '5'},
    {'6', '7', '8'},
};

byte rowPins[ROWS] = {8, 9, 7};
byte colPins[COLS] = {5, 6, 4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

char lastKey = '0';

void setup()
{
  pinMode(joystickBtnPin, INPUT_PULLUP);

  Joystick.begin();
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
}
void loop()
{
  int valueRoll = analogRead(sensorPinRoll);
  int valuePitch = analogRead(sensorPinPitch);

  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);

  int joystickBtnValue = digitalRead(joystickBtnPin);

  char key = keypad.getKey();
  int state = keypad.getState();

  if (key)
  {
    lastKey = key;
  }

  if (lastKey != '0' && (state == PRESSED || state == HOLD))
  {
    Joystick.setButton(lastKey - '1', 1);
  }
  else
  {
    Joystick.setButton(lastKey - '1', 0);
    lastKey = '0';
  }

  Joystick.setButton(10, (joystickBtnValue == 0) ? 1 : 0);

  Joystick.setRxAxis(joystickXValue);
  Joystick.setRyAxis(joystickYValue);

  Joystick.setXAxis(valueRoll);
  Joystick.setYAxis(valuePitch);

  Joystick.sendState();
}
