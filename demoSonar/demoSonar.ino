#define trig 8
#define echo 9

float frontDistances;

void setup() {
  Serial.begin(9600);
    // put your setup code here, to run once:
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  updatedSonarDistance();
  TestingDistanceAndAccuracy();
}
void triggerPulse(){
  // updating sonar hardware
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  // Sets the trig on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
}

//calculation to convert the reading from the sonar sensor into centimeter. 
float calcDistance(unsigned long pulse, int echoPin){
  return (pulseIn(echoPin, HIGH) * 0.034)/2;
}

void updatedSonarDistance(){
  triggerPulse();
  frontDistances = calcDistance(pulseIn(echo, HIGH, 4), echo);
}

void TestingDistanceAndAccuracy(){
  Serial.println(frontDistances);
}