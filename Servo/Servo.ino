#include <Servo.h>

Servo myservo;

// Pins för IR-sensorerna
const int IR1_pin = A0;
const int IR2_pin = A1;

// Variabler för att lagra sensorvärdena
int IR1_val = 0;
int IR2_val = 0;

// Max- och min-värde för IR1 och IR2
double max_val = 1023.0;
double min_val = 0.0;

// PID-konstanter
double Kp = 0.1;
double Ki = 0.01;
double Kd = 0.01;

// PID-felmariginaler
double error = 0;
double last_error = 0;
double integral = 0;
double derivative = 0;

// Börvärden för sensor
int IR1_target = 500;
int IR2_target = 500;

// Värden för servots vinkel och målvinkeln.
int servo_angle = 105;
int target_angle = 105;

// Nuvarande tid och förra mätningens tid
unsigned long current_time = 0;
unsigned long last_time = 0;

// Define variable to store PID output
double output = 0;

void setup() 
{
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(IR1_pin, INPUT);
  pinMode(IR2_pin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  // Read IR sensor values
  IR1_val = analogRead(IR1_pin);
  IR2_val = analogRead(IR2_pin);
  if(IR1_val < min_val) IR1_val = min_val; 
  if(IR1_val > max_val) IR1_val = max_val;
  if(IR2_val < min_val) IR2_val = min_val; 
  if(IR2_val > max_val) IR2_val = max_val;

  // Determine which IR sensor has the greater value
  if (IR1_val > IR2_val) 
  {
    // IR sensor 1 has greater value, turn servo towards IR sensor 1
    target_angle = 105 - (IR1_val - IR2_val) / 10;
  } 
  else 
  {
    // IR sensor 2 has greater value, turn servo towards IR sensor 2
    target_angle = 105 + (IR2_val - IR1_val) / 10;
  }

  // Limit target angle to between 0 and 180 degrees
  if (target_angle > 150) 
  {
    target_angle = 150;
  } 
  else if (target_angle < 30) 
  {
    target_angle = 30;
  }

  // Move servo to target angle
  myservo.write(target_angle);

  // Print sensor values and target angle to serial monitor
  Serial.print("IR1: ");
  Serial.print(IR1_val);
  Serial.print(" ");
  Serial.print("\tIR2: ");
  Serial.print(IR2_val);
  Serial.print(" ");
  Serial.print("\tTarget Angle: ");
  Serial.println(target_angle);

  // Delay to allow servo to move to target angle
  delay(150);
}
