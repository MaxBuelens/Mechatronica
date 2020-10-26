/*Line Following code 1.1 */
// Last edit 26/10/2020
//Analoog genomen zodat sensoren niet individueel moeten aangepast worden met de potentiometer

//Analoge
const int Drukknop = A0;
const int Sensor1 = A1;
const int Sensor2 = A2;
const int Sensor3 = A3;
const int Sensor4 = A4;
const int Sensor5 = A5;

//Digitale
const int Enable = 13;
const int Motor1Forward = 5; // Draaizin motoren nog niet zeker
const int Motor1Backward = 10;
const int Motor2Forward = 6;
const int Motor2Backward = 11;

//Drukknop variabele
int DrukknopValue = 0;
bool Active = false;

//Sensoren variabele
int Sensor1Value = 0;
int Sensor2Value = 0;
int Sensor3Value = 50;
int Sensor4Value = 0;
int Sensor5Value = 0;


void setup() {
  // Voor de serial poort te kunnen gebruiken
  Serial.begin(9600);

  // Drukknop als input
  pinMode(Drukknop, INPUT);

  // Digitale pinnen als output
  pinMode(Enable, OUTPUT);
  pinMode(Motor1Forward, OUTPUT);
  pinMode(Motor1Backward, OUTPUT);
  pinMode(Motor2Forward, OUTPUT);
  pinMode(Motor2Backward, OUTPUT);


} //End Setup


void loop() {
  ReadSensorAndButton();

  if (Active) {
    //Wit / Wit / Zwart / Wit / Wit
    if (Sensor1Value > 500 && Sensor2Value > 500 && Sensor3Value < 100 && Sensor4Value > 500 && Sensor5Value > 500) {
      Forward();
    }
    //Wit / zwart / Zwart / Wit / Wit
    if (Sensor1Value > 500 && Sensor2Value < 100 && Sensor3Value < 100 && Sensor4Value > 500 && Sensor5Value > 500) {
      TrunLeft();
    }
    //Wit / wit / Zwart / zwart / wit
    if (Sensor1Value > 500 && Sensor2Value > 500 && Sensor3Value < 100 && Sensor4Value < 100 && Sensor5Value > 500) {
      TrunRight();
    }
    //zwart / zwart / Zwart / wit / wit
    if (Sensor1Value < 100 && Sensor2Value < 100 && Sensor3Value < 100 && Sensor4Value > 500 && Sensor5Value > 500) {
      // Doe dit tot robot weer op recht op lijn zit anders blijven draaien
      //Nog een test
      while (!(Sensor2Value > 500 && Sensor3Value < 100 && Sensor4Value > 500) || !Active) {
        ReadSensorAndButton();
        SharpTrunLeft();
      }
    }
    // wit / wit / Zwart / zwart / zwart
    if (Sensor1Value > 500 && Sensor2Value > 500 && Sensor3Value < 100 && Sensor4Value < 100 && Sensor5Value < 100) {
      while (!(Sensor2Value > 500 && Sensor3Value < 100 && Sensor4Value > 500) || !Active) {
        ReadSensorAndButton();
        SharpTrunRight();
      }
    }
    // zwart / zwart / Zwart / zwart / zwart
    if (Sensor1Value < 100 && Sensor2Value < 100 && Sensor3Value < 100 && Sensor4Value < 100 && Sensor5Value < 100) {
      Stop();
    }
  }//If active

  else {
    digitalWrite(Enable, LOW);
  }

}//End Void loop


//#######################################################################################################################################
// Read the sensors and button
void ReadSensorAndButton() {

  //Lees de drukknop
  DrukknopValue = digitalRead(Drukknop);

  // Lees de analoge ingangen en schrijf de data weg
  Sensor1Value = analogRead(Sensor1);
  // Geef even tijd om te lezen en weg te schrijven
  delay(5);
  Sensor2Value = analogRead(Sensor2);
  delay(5);
  //Sensor3Value = analogRead(Sensor3);
  // delay(5);
  Sensor4Value = analogRead(Sensor4);
  delay(5);
  Sensor5Value = analogRead(Sensor5);
  delay(5);

  Serial.print("Sensor1:");
  Serial.print(Sensor1Value);
  Serial.print("\t");
  Serial.print("Sensor2:");
  Serial.print(Sensor2Value);
  Serial.print("\t");
  Serial.print("Sensor3:");
  Serial.print(Sensor3Value);
  Serial.print("\t");
  Serial.print("Sensor4:");
  Serial.print(Sensor4Value);
  Serial.print("\t");
  Serial.print("Sensor5:");
  Serial.println(Sensor5Value);

  if (DrukknopValue == LOW) {
    Active = ! Active;
    Serial.println("Push on button ==> robot is active");
    delay(200);
  } // If drukknop

} //End Void ReadSensorAndButton
//#######################################################################################################################################
// Go forward
void Forward() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 200);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 200);
  analogWrite(Motor2Backward, 0);
  Serial.println("Forward");
}//Void Forward
//#######################################################################################################################################
//Go left
void TrunLeft() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 150);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 200);
  analogWrite(Motor2Backward, 0);
  Serial.println("Left");
}//Void TrunLeft
//#######################################################################################################################################
// Go right
void TrunRight() {
  /*digitalWrite(Enable, HIGH);
    analogWrite(Motor1Forward, 200);
    analogWrite(Motor1Backward, 0);
    analogWrite(Motor2Forward, 150);
    analogWrite(Motor2Backward, 0);*/
  Serial.println("Right");
} //Void TrunRight
//#######################################################################################################################################

void SharpTrunLeft() {
  /* digitalWrite(Enable, HIGH);
    analogWrite(Motor1Forward, 0);
    analogWrite(Motor1Backward, 0);
    analogWrite(Motor2Forward, 200);
    analogWrite(Motor2Backward, 0);*/
  Serial.println("SharpTurnLeft");
}

void SharpTrunRight() {
  /*digitalWrite(Enable, HIGH);
    analogWrite(Motor1Forward, 200);
    analogWrite(Motor1Backward, 0);
    analogWrite(Motor2Forward, 0);
    analogWrite(Motor2Backward, 0);*/
  Serial.println("SharpTurnRight");
}

//#######################################################################################################################################
void Stop() {
  digitalWrite(Enable, LOW);
  analogWrite(Motor1Forward, 0);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 0);
  analogWrite(Motor2Backward, 0);
  Serial.println("Stop");
}
