/*Line Following code 1.0 */

//Analoge
const int Drukknop = A0;
const int Sensor1 = A1;
const int Sensor2 = A2;
const int Sensor3 = A3;
const int Sensor4 = A4;
const int Sensor5 = A5;

//Digitale
Const int Enable = 13;
Const int Motor1CW = 5; // Draaizin motoren nog niet zeker
Const int Motor1CCW = 10;
Const int Motor2CW = 6;
Const int Motor2CCW = 11;

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
 Serial.Begin(9600);
 
 // Drukknop als input
 pinMode(Drukknop, INPUT);
 
 // Digitale pinnen als output
 pinMode(Enable, OUTPUT);
 pinMode(Motor1CW, OUTPUT);
 pinMode(Motor1CCW, OUTPUT);
 pinMode(Motor2CW, OUTPUT);
 pinMode(Motor2CCW, OUTPUT);
   

} //End Setup


void loop() {
  // Read the sensors and button een overzichterlijke weergave door meerdere voids te gebruiken
  ReadSensorAndButton();
  // Doorloop het programma
  if Active{
    // Hier de werkelijke code
  } // End if active
}//End Void loop


#######################################################################################################################################
// Read the sensors and button 
Void ReadSensorsAndButton(){
   //Lees de drukknop
  DrukknopValue = digitalRead(Drukknop);
  
  // Lees de analoge ingangen en schrijf de data weg
  Sensor1Value = analogRead(Sensor1);
  // Geef even tijd om te lezen en weg te schrijven
  Delay(5);
  Sensor2Value = analogRead(Sensor2);
  Delay(5);
  Sensor3Value = analogRead(Sensor3);
  Delay(5);
  Sensor4Value = analogRead(Sensor4);
  Delay(5);
  Sensor5Value = analogRead(Sensor5);
  Delay(5);
  
  // Drukknop gedrukt start programma
  if (DrukknopValue == HIGH){
    Active =! Active;    
  } // End if DrukknopValue
} //End Void ReadSensorAndButton
#######################################################################################################################################


