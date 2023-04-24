const int echoPin = 12;
const int trigPin = 13;
const int redPin = 4;
const int bluePin = 2;
const int greenPin= 3;

long duration;
float distance;
const float threshold = 2.5; //From this thresold trashcan is considered full
int percentageFull = 0;
bool isFull = false;

int redBrightness = 0;
int greenBrightness = 0;  
int blueBrightness = 0;

void setup() {
  // put your setup code here, to run once:
   pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  Serial.begin(9600);

}

void loop() {
    // Set the brightness values for each color (0 to 255)

  

  //Clear trig pin
  digitalWrite(trigPin, LOW);
  delay(2);

  //Trigger the ultrasonic pulse
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin,LOW);
  

  //Read the reflected pulse duration
  duration = pulseIn(echoPin, HIGH);
  
  //Calculate the distance from the reflected pulse duration
  distance = duration * 0.0344 / 2.0;
  
  percentageFull = map(distance,10,0,0,100);


  

  if(distance <= threshold){
    Serial.println("\n Trash is full");
     greenBrightness = 0;
      redBrightness = 255;
    isFull = true;
  }else{
    isFull = false;
    Serial.print("\n Trash is at ");
    Serial.print(percentageFull);
    Serial.print("%");

    if(percentageFull < 50){
      redBrightness = 0;
      greenBrightness = 255;
    }

    if(percentageFull >= 50 ){
      greenBrightness= 55.5;
      redBrightness = 255;
    }
  }

  // Write the PWM values to the corresponding pins
  analogWrite(redPin, redBrightness);
  analogWrite(greenPin, greenBrightness);
  analogWrite(bluePin, blueBrightness);

delay(1000);
  Serial.print("\n Duration:");
  Serial.print(duration);
  Serial.print("\n Distance:");
  Serial.print(distance);
}
