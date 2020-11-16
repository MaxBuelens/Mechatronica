/*Line Following code 1.1 */
// Last edit 23/10/2020

//Analoge
const int Drukknop = A0;
const int Sensor1 = A5;
const int Sensor2 = A4;
const int Sensor3 = A3;
const int Sensor4 = A2;
const int Sensor5 = A1;

//Digitale
const int Enable = 13;
const int Motor1Forward = 6;
const int Motor1Backward = 11;
const int Motor2Forward = 5;
const int Motor2Backward = 10;

//Drukknop variabele
int DrukknopValue = 0;
bool Active = false;

//Sensoren variabele
int Sensor1Value = 0;
int Sensor2Value = 0;
int Sensor3Value = 0;
int Sensor4Value = 0;
int Sensor5Value = 0;


void setup() {
  // Voor de serial poort te kunnen gebruiken
  Serial.begin(9600);

  // Drukknop als input
  pinMode(Drukknop, INPUT);
  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Sensor3, INPUT);
  pinMode(Sensor4, INPUT);
  pinMode(Sensor5, INPUT);


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
    if (Sensor1Value == HIGH && Sensor2Value == HIGH && Sensor3Value == LOW && Sensor4Value == HIGH && Sensor5Value == HIGH) {
      Forward();
    }
    //Wit / zwart / Zwart / Wit / Wit
    if (Sensor1Value == HIGH && Sensor2Value == LOW && Sensor3Value == LOW && Sensor4Value == HIGH  && Sensor5Value == HIGH) {
      TrunRight();
    }
    //Wit / wit / Zwart / zwart / wit
    if (Sensor1Value == HIGH && Sensor2Value == HIGH && Sensor3Value == LOW && Sensor4Value == LOW && Sensor5Value == HIGH) {
      TrunLeft();
    }

    //zwart / zwart / Zwart / wit / wit
    if (Sensor1Value == LOW && Sensor2Value == LOW && Sensor3Value == LOW && Sensor4Value == HIGH && Sensor5Value == HIGH) {
      // Doe dit tot robot weer op recht op lijn zit anders blijven draaien
      while (!(Sensor2Value == HIGH && Sensor3Value == LOW && Sensor4Value == HIGH) && Active) {
        ReadSensorAndButton();
        SharpTrunLeft();
      }
    }
    // wit / wit / Zwart / zwart / zwart
    if (Sensor1Value ==  HIGH && Sensor2Value == HIGH && Sensor3Value == LOW && Sensor4Value == LOW && Sensor5Value == LOW) {
      while (!(Sensor2Value == HIGH && Sensor3Value == LOW && Sensor4Value == HIGH) && Active) {
        ReadSensorAndButton();
        SharpTrunRight();
      }
    }
    //Zwart / zwart / zwart / zwart / zwart
    if (Sensor1Value == LOW && Sensor2Value == LOW && Sensor3Value == LOW && Sensor4Value == LOW && Sensor5Value == LOW) {
      Stop();
    }
  }//If active

  else {
    digitalWrite(Enable, LOW);
  } // End else active

}//End Void loop


//#######################################################################################################################################
// Read the sensors and button
void ReadSensorAndButton() {

  //Lees de drukknop
  DrukknopValue = digitalRead(Drukknop);

  // Lees de analoge ingangen en schrijf de data weg
  Sensor1Value = digitalRead(Sensor1);
  // Geef even tijd om te lezen en weg te schrijven
  delay(5);
  Sensor2Value = digitalRead(Sensor2);
  delay(5);
  Sensor3Value = digitalRead(Sensor3);
  delay(5);
  Sensor4Value = digitalRead(Sensor4);
  delay(5);
  Sensor5Value = digitalRead(Sensor5);
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

  if (DrukknopValue == LOW) {   //Drukknop leest '0' bij indrukken
    Active = ! Active;
    Serial.println("Push on button ==> robot is active");
    delay(200);
  }

} //End Void ReadSensorAndButton
//#######################################################################################################################################
// Go forward
void Forward() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 95);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 95);
  analogWrite(Motor2Backward, 0);
  Serial.println("Forward");
}//Void Forward
//#######################################################################################################################################
//Go left
void TrunLeft() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 0);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 95);
  analogWrite(Motor2Backward, 0);
  Serial.println("Left");
}//Void TrunLeft
//#######################################################################################################################################
// Go right
void TrunRight() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 95);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 0);
  analogWrite(Motor2Backward, 0);
  Serial.println("Right");
} //Void TrunRight
//#######################################################################################################################################

void SharpTrunLeft() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 0);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 175);
  analogWrite(Motor2Backward, 0);
  Serial.println("SharpTurnLeft");
}

void SharpTrunRight() {
  digitalWrite(Enable, HIGH);
  analogWrite(Motor1Forward, 175);
  analogWrite(Motor1Backward, 0);
  analogWrite(Motor2Forward, 0);
  analogWrite(Motor2Backward, 0);
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
