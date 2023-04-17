/********************************************************************************
* Hastighet.ino: Arduinokod för att justera hastigheten på en självkörande bils 
*                motor. En signal från en sensor läses in och inverteras.
*                sensorvärdet styr bilens hastighet. Om sensorvärdet går under
*                ett bestämt gränsvärde ska backen läggas i.
********************************************************************************/

#define enA 9
#define in1 6
#define in2 7

void setup() 
{
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  // Set initial rotation direction
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void loop() 
{
  int potValue = analogRead(A0); // Read potentiometer value
  int pwmOutput = map(potValue, 0, 800, 255 , 0); // Map the potentiometer value from 0 to 255

  if (pwmOutput <= 80) // Om den inverterade signalen är för låg, betyder det att något är nära
  {
    digitalWrite(in1, HIGH);    // Slå i backen
    digitalWrite(in2, LOW);     // Slå i backen
    analogWrite(enA, 100);      // Backa med en hastighet mellan 0-255 (100)

    while (pwmOutput <= 40 && pwmOutput >= 100)
    
    delay(1000);      // Delay för smidiagre backning (Mindre ryckigt)
  }
  else // Annars, om värdet är tillräckligt högt så gasa
  {
  digitalWrite(in1, LOW);       // Slår i gasen
  digitalWrite(in2, HIGH);      // Slår i gasen
  analogWrite(enA, pwmOutput);  // Gasar med en hastighet mellan 0-255 (pwmOutput)
  delay(1000);
  }

  // Skriver ut värdet på den inverterade pwm signalen i konsollen
  
  Serial.print("PWM_output:");
  Serial.print("\t");
  Serial.print(pwmOutput);
  Serial.print("\n");
  delay(250);
}
