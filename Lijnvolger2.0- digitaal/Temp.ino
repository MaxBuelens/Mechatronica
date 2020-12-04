/*Line Following code 3 */
//LOW---->wit
//HIGH--->zwart
//Last edit 29/11/2020

//Analoge ingangen
const int Drukknop = A0;
const int SensorLL = A1;  //Sensor uiterst links
const int SensorL = A2;   //Sensor links
const int SensorM = A3;   //Sensor midden
const int SensorR = A4;   //Sensor rechts
const int SensorRR = A5;  //Sensor uiterst rechts

//Digitale ingangen
const int Enable = 13;              //Motoren inschakelen
const int MotorLeftForward = 6;     //Linkse motor voorwaarts
const int MotorLeftBackward = 11;   //Linkse motor achterwaarts
const int MotorRightForward = 5;    //Rechtse motor voorwaarts
const int MotorRightBackward = 10;  //Rechtse motor achterwaarts

//Drukknop variabelen
int DrukknopValue = 0;
bool Active = false;

//Sensoren variabelen
int SensorLLValue = 0;
int SensorLValue = 0;
int SensorMValue = 0;
int SensorRValue = 0;
int SensorRRValue = 0;

//Constanten voor snelheid
const int vNormaal = 70;
const int vDraaien = 100;
const int v90Graden = 80;

//Setup code, 1 keer doorlopen
void setup() {
  //Om de serial poort te kunnen gebruiken
  Serial.begin(9600);

  //Drukknop als input
  pinMode(Drukknop, INPUT);

  //Digitale pinnen als output
  pinMode(Enable, OUTPUT);
  pinMode(MotorLeftForward, OUTPUT);
  pinMode(MotorLeftBackward, OUTPUT);
  pinMode(MotorRightForward, OUTPUT);
  pinMode(MotorRightBackward, OUTPUT);
} //End void setup

//Loop
void loop() {

  ReadSensorAndButton();

  if (Active = true) {
    if ((SensorLLValue == LOW && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == LOW) ||
        (SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) {
      vSnelheid(HIGH, vNormaal, vNormaal, "Forward");  //Voorwaarts
    }//End if forward

    else if (SensorLLValue == LOW && SensorLValue == LOW && SensorRValue == HIGH && SensorRRValue == LOW) {
      vSnelheid(HIGH, vDraaien, vNormaal, "Right"); //Naar rechts
    }//End else if TurnRight

    else if (SensorLLValue == LOW && SensorLValue == HIGH && SensorRValue == LOW && SensorRRValue == LOW) {
      vSnelheid(HIGH, vNormaal, vDraaien, "Left"); //Naar links
    }//End else if TurnLeft

    else if ((SensorLLValue == LOW && SensorMValue == HIGH && SensorRRValue == HIGH && SensorRValue == HIGH) ||
             (SensorLLValue == LOW &&  SensorMValue == LOW && SensorRRValue == HIGH && SensorRValue == HIGH))   {
      //Stop();
      while (!(SensorRValue == HIGH && SensorRRValue == LOW ) && Active && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) {
        vSnelheid(HIGH, v90Graden, 0, "SharpTurnRight"); //Scherp naar rechts
        ReadSensorAndButton();
      }// End While
      //Stop();
    }//End else if SharpTurnRight

    else if ((SensorLLValue == HIGH && SensorLValue == HIGH && SensorRRValue == LOW) || (SensorLLValue == HIGH && SensorMValue == LOW && SensorRRValue == LOW)) {   //Middelste, linkse en uiterste linkse sensor wit, andere zwart
      //Stop();
      //Doe dit tot robot weer op recht op lijn zit anders blijven draaien
      while (!(SensorLValue == HIGH && SensorLLValue == LOW) && Active && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) {
        vSnelheid(HIGH, 0, v90Graden, "SharpTurnLeft"); //Scherp naar links
        ReadSensorAndButton();
      }// End While
      //Stop();
    }//End else if SharpTurnRight

    else if (SensorLLValue == LOW && SensorLValue == LOW && SensorMValue == LOW && SensorRValue == LOW && SensorRRValue == LOW) {  //Alle sensoren zwart, onderbreking in het parcour
      Stop(); //Stop
      Active = false; //Stop
    }//End else if Stop
  }//End if active

  else {
    digitalWrite(Enable, LOW);
  } //End else active

  delay(20); // Voor goede programma werking
}//End void loop

// Lees sensoren en drukknop
void ReadSensorAndButton() {

  //Lees de drukknop
  DrukknopValue = digitalRead(Drukknop);

  //Lees de analoge ingangen en schrijf de data weg
  SensorLLValue = digitalRead(SensorLL);
  //Geef even tijd om te lezen en weg te schrijven
  delay(5);
  SensorLValue = digitalRead(SensorL);
  delay(5);
  SensorMValue = digitalRead(SensorM);
  delay(5);
  SensorRValue = digitalRead(SensorR);
  delay(5);
  SensorRRValue = digitalRead(SensorRR);
  delay(5);

  Serial.print("SensorLL:");
  Serial.print(SensorLLValue);
  Serial.print("\t");
  Serial.print("SensorL:");
  Serial.print(SensorLValue);
  Serial.print("\t");
  Serial.print("SensorM:");
  Serial.print(SensorMValue);
  Serial.print("\t");
  Serial.print("SensorR:");
  Serial.print(SensorRValue);
  Serial.print("\t");
  Serial.print("SensorRR:");
  Serial.println(SensorRRValue);

  if (DrukknopValue == LOW) {   //Drukknop leest '0' bij indrukken
    Active = ! Active;
    Serial.println("Push on button ==> robot is active");
    delay(200); //Vertaging voor goede werking drukknop
  } //End if
} //End void ReadSensorAndButton

void vSnelheid(bool EnableWaarde, int LeftFront, int RightFront, String strRichting) {
  digitalWrite(Enable, EnableWaarde);
  analogWrite(MotorLeftForward, LeftFront);
  analogWrite(MotorLeftBackward, 0);
  analogWrite(MotorRightForward, RightFront);
  analogWrite(MotorRightBackward, 0);
  Serial.println(strRichting);
} //End void vSnelheid


void Stop() {
  digitalWrite(Enable, LOW);
  analogWrite(MotorLeftForward, 0);
  analogWrite(MotorLeftBackward, 0);
  analogWrite(MotorRightForward, 0);
  analogWrite(MotorRightBackward, 0);
  Serial.println("Stop");
}//End void Stop
