/*Line Following code 3*/
//LOW---->wit
//HIGH--->zwart
//Last edit 9/12/2020

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
const int vNormaal = 75; //75
const int vDraaien = 100; //100
const int v90Graden = 80; //100

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

//Loop, blijven doorlopen
void loop() {

  ReadSensorAndButton();

  if (Active == true ) {
    if ((SensorLLValue == LOW && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == LOW)         //Middelste, rechtse en linkse sensor zwart, andere wit
        || (SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) { //Alle sensoren zwart (nodig bij '8' in het parkour)
      vSnelheid(HIGH, vNormaal, vNormaal, "Forward");  //Voorwaarts
    }//End if forward

    else if (SensorLLValue == LOW && SensorLValue == LOW && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == LOW) { //Middelste en rechtse senor zwart, andere wit
      vSnelheid(HIGH, vDraaien, vNormaal, "Right"); //Naar rechts
    }//End else if TurnRight

    else if (SensorLLValue == LOW && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == LOW && SensorRRValue == LOW) { //Middelste en linkse senor zwart, andere wit
      vSnelheid(HIGH, vNormaal, vDraaien, "Left"); //Naar links
    }//End else if TurnLeft

    else if ((SensorLLValue == LOW && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH) || //Middelste, rechtse en uiterstrechtse sensor zwart (nodig bij 90° R), andere wit
             (SensorLLValue == LOW && SensorMValue == LOW && SensorRValue == HIGH && SensorRRValue == HIGH)) { //Rechtse en uiterstrechtse sensor zwart (nodig bij zigzag), andere wit
      Stop(); //Even stoppen om doordraaien motoren tegen te gaan, anders zou motor te ver kunnen doorrijden
      while (!(SensorRValue == HIGH && SensorRRValue == LOW ) && Active  //Doe zolang, rechtse sensor niet zwart is en uiterstrechtse sensor niet wit is, of drukknop niet wordt ingedrukt, -
             && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) { //of zolang alle sensoren niet zwart zijn (nodig voor binnen- en buitenrijden '8')
        vSnelheid(HIGH, v90Graden, 0, "SharpTurnRight"); //Scherp naar rechts
        ReadSensorAndButton();
      }// End While
    }//End else if SharpTurnRight

    else if ((SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRRValue == LOW) //Middelste, linkse en uiterstlinkse sensor zwart (nodig bij 90° L), andere wit
             || (SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == LOW && SensorRRValue == LOW)) { //Linkse en uiterstlinkse sensor zwart (nodig bij zigzag), andere wit
      Stop(); // Even stoppen om doordraaien motoren tegen te gaan, anders zou motor te ver kunnen doorrijden
      while (!(SensorLValue == HIGH && SensorLLValue == LOW) && Active //Doe zolang, linkse sensor niet zwart is en uiterstlinkse sensor niet wit is, of drukknop niet wordt ingedrukt, -
             && !(SensorLLValue == HIGH && SensorLValue == HIGH && SensorMValue == HIGH && SensorRValue == HIGH && SensorRRValue == HIGH)) { //of zolang alle sensoren niet zwart zijn (nodig voor binnen- en buitenrijden '8')
        vSnelheid(HIGH, 0, v90Graden, "SharpTurnLeft"); //Scherp naar links
        ReadSensorAndButton();
      }// End While
    }//End else if SharpTurnRight

    else {
      Stop();
    }//End else active
    delay(20); //Voor goede programma werking
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
      Active = ! Active; //Inverteren van de boolwaarde, zodat drukknop werkt als schakelaar
      Serial.println("Push on button ==> robot is active");
      delay(200); //Vertaging voor goede werking drukknop
    }//End if
  }//End void ReadSensorAndButton

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
