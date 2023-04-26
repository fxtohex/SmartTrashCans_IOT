#include "Arduino.h"
#include "ultrasonic_sensor.h"

int echoPin;
int trigPin;
int redPin;
int bluePin;
int greenPin;

long duration;
float distance;
int trashCanHeight = 8;      // Height of the trash can in inches
const float threshold = 3.9; // From this thresold trashcan is considered full
int percentageFull = 0;
bool isFull = false;

int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

void ultrasonic_sensor_setup(int _echoPin, int _trigPin, int _ultRedPin, int _ultBluePin, int _ultGreenPin)
{
  redPin = _ultRedPin;
  bluePin = _ultBluePin;
  greenPin = _ultGreenPin;
  echoPin = _echoPin;
  trigPin = _trigPin;

  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

ultrasonic_sensor_status handle_ult_sensor()
{
  ultrasonic_sensor_status status;

  // Clear trig pin
  digitalWrite(trigPin, LOW);
  delay(2);

  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);

  // Read the reflected pulse duration
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance from the reflected pulse duration
  distance = duration * 0.0344 / 2.0;

  percentageFull = map(distance, trashCanHeight, 0, 0, 100);

  if (distance <= threshold)
  {
    greenBrightness = 0;
    redBrightness = 255;
    isFull = true;
  }
  else
  {
    isFull = false;
    Serial.print("\n Trash is at ");
    Serial.print(percentageFull);
    Serial.print("%");

    if (percentageFull < 50)
    {
      redBrightness = 0;
      greenBrightness = 255;
    }

    if (percentageFull >= 50)
    {
      greenBrightness = 55.5;
      redBrightness = 255;
    }
  }

  // Write the PWM values to the corresponding pins
  analogWrite(redPin, redBrightness);
  analogWrite(greenPin, greenBrightness);
  analogWrite(bluePin, blueBrightness);

  Serial.print("\n Duration:");
  Serial.print(duration);
  Serial.print("\n Distance:");
  Serial.print(distance);
  Serial.print(percentageFull);

  status.isFull = isFull;
  status.percentageFull = percentageFull;

  return status;
}
