
const int Sensor1 = A1;
int Sensor1Value = 0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Sensor1Value = analogRead(Sensor1);
  Serial.println(Sensor1Value);
  delay(20);
}
