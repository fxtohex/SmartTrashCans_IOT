const int ledPin = 13;// we will turn the Pin 13 light on
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(2,INPUT);
  digitalWrite(2, HIGH);
}
/******************************************/
void loop()
{
  int digitalVal = digitalRead(2);
  if(HIGH == digitalVal)
  {
    Serial.println(digitalVal);
    digitalWrite(ledPin,LOW);//turn the led off
  }
  else
  {
    Serial.println(digitalVal);
    digitalWrite(ledPin,HIGH);//turn the led on
  }
  delay(1000);
}
