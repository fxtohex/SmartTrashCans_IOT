const int enablePin = 12;
const int outPin = 13;
int currentState = 0;
void setup() {
  pinMode(enablePin, OUTPUT);
  pinMode(outPin,INPUT);
  digitalWrite(enablePin,HIGH); //Enable the sensors
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  currentState = digitalRead(outPin);
  
  Serial.println(currentState);
  if(currentState == 0){
    Serial.println("Trash can is full");
  }
  if(currentState == 1){
    Serial.println("Trash can is not full");
  }

  delay(1000);
  // put your main code here, to run repeatedly:

}
