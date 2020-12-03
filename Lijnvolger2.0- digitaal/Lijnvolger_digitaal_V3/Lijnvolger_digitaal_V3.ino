/*Line Following code 3 */
// Last edit 29/11/2020

//Analoog
const int Drukknop = A0;
const int SensorLL = A1;  //Sensor uiterst links
const int SensorL = A2;   //Sensor links
const int SensorM = A3;   //Sensor midden
const int SensorR = A4;   //Sensor rechts
const int SensorRR = A5;  //Sensor uitersT rechts

//Digitaal
const int Enable = 13;              //Motor inschakelen
const int MotorLeftForward = 6;     //Linkse motor voorwaarts
const int MotorLeftBackward = 11;   //Linkse motor achterwaarts
const int MotorRightForward = 5;    //Rechtse motor voorwaarts
const int MotorRightBackward = 10;  //Rechtse motor achterwaarts

//Drukknop variabele
int DrukknopValue = 0;
bool Active = false;

//Sensoren variabele
int SensorLLValue = 0;
int SensorLValue = 0;
int SensorMValue = 0;
int SensorRValue = 0;
int SensorRRValue = 0;

//Constante voor snelheid
const int vNormaal = 80;
const int vDraaien = 110;//110
const int v90Graden = 95;//75


//Setup code, 1 keer doorlopen
void setup() {
  // Om de serial poort te kunnen gebruiken
  Serial.begin(9600);

  // Drukknop als input
  pinMode(Drukknop, INPUT);

  // Digitale pinnen als output
  pinMode(Enable, OUTPUT);
  pinMode(MotorLeftForward, OUTPUT);
  pinMode(MotorLeftBackward, OUTPUT);
  pinMode(MotorRightForward, OUTPUT);
  pinMode(MotorRightBackward, OUTPUT);
} //End void setup



//Loop
void loop() {

  ReadSensorAndButton();

  if (Active) {
    if ((SensorLLValue == LOW && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == LOW) || (SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) { //Middelste sensor wit, andere zwart
      Forward();//Voorwaarts                                                                                                               
    }// End If forward

    else if (SensorLLValue == LOW && SensorLValue == LOW && SensorRValue == HIGH && SensorRRValue == LOW) {   //Middelste en rechtse sensor wit, andere zwart
      TurnRight(); //Naar rechts
    }//End else if turnright

    else if (SensorLLValue == LOW && SensorLValue == HIGH && SensorRValue == LOW && SensorRRValue == LOW) {   //Middelste en linkse sensor wit, andere zwart
      TurnLeft(); //Naar links
    }//End Else if TurlLeft

    else if (( SensorLLValue == LOW && SensorMValue == HIGH && SensorRRValue == HIGH && SensorRValue == HIGH) || ( SensorLLValue == LOW &&  SensorMValue == LOW && SensorRRValue == HIGH && SensorRValue == HIGH))   {
      //Stop();
      while (!(SensorRValue == HIGH && SensorRRValue == LOW ) && Active && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) {
        SharpTurnRight();
        ReadSensorAndButton();
      }// End While
      //Stop();
    }//End else if SharpTurnRight

    else if ((SensorLLValue == HIGH && SensorLValue == HIGH && SensorRRValue == LOW) || (SensorLLValue == HIGH && SensorMValue == LOW && SensorRRValue == LOW)) {   //Middelste, linkse en uiterste linkse sensor wit, andere zwart
      //Stop();
      // Doe dit tot robot weer op recht op lijn zit anders blijven draaien
      while (!(SensorLValue == HIGH && SensorLLValue == LOW) && Active && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) {
        ReadSensorAndButton();
        SharpTurnLeft(); //Scherp naar links
      }// End While
      //Stop();
    }//End Else if SharpTurnRight
    
    else if (SensorLLValue == LOW && SensorLValue == LOW && SensorMValue == LOW && SensorRValue == LOW && SensorRRValue == LOW) {  //Alle sensoren zwart, onderbreking in het parcour
      Stop();
      Active = false; //Stop
    }//End else if stop
  }//End if active

  else {
    digitalWrite(Enable, LOW);
    } // end else active

  delay(20); // Voor goede programma werking
  }//End void loop

  // Lees sensoren en drukknop
  void ReadSensorAndButton() {

    //Lees de drukknop
    DrukknopValue = digitalRead(Drukknop);

    // Lees de analoge ingangen en schrijf de data weg
    SensorLLValue = digitalRead(SensorLL);
    // Geef even tijd om te lezen en weg te schrijven
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
    } // End if
  } //End void ReadSensorAndButton

  //Voorwaarts
  void Forward() {
    digitalWrite(Enable, HIGH);
    analogWrite(MotorLeftForward, vNormaal); //120
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, vNormaal); //120
    analogWrite(MotorRightBackward, 0);
    Serial.println("Forward");
  } //End void Forward

  //Naar links
  void TurnLeft() {
    digitalWrite(Enable, HIGH);
    analogWrite(MotorLeftForward, vNormaal); //70
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, vDraaien); //120
    analogWrite(MotorRightBackward, 0);
    Serial.println("Left");
  }//End void TurnLeft

  //Naar rechts
  void TurnRight() {
    digitalWrite(Enable, HIGH);
    analogWrite(MotorLeftForward, vDraaien);// 120
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, vNormaal); //70
    analogWrite(MotorRightBackward, 0);
    Serial.println("Right");
  } //End void TurnRight

  //Scherp naar links
  void SharpTurnLeft() {
    digitalWrite(Enable, HIGH);
    analogWrite(MotorLeftForward, 0); //0
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, v90Graden); //100
    analogWrite(MotorRightBackward, 0);
    Serial.println("SharpTurnLeft");
  }//End void SharpTurnLeft

  //Scherp naar rechts
  void SharpTurnRight() {
    digitalWrite(Enable, HIGH);
    analogWrite(MotorLeftForward, v90Graden);//100  v90Graden
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, 0);//0
    analogWrite(MotorRightBackward, 0 );
    Serial.println("SharpTurnRight");

  }//End void SharpTurnRight

  //Stop
  void Stop() {
    digitalWrite(Enable, LOW);
    analogWrite(MotorLeftForward, 0);
    analogWrite(MotorLeftBackward, 0);
    analogWrite(MotorRightForward, 0);
    analogWrite(MotorRightBackward, 0);
    Serial.println("Stop");
  }//End void Stop
