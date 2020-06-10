#include <MotorRobot.h>

#include <avr/wdt.h>

MotorRobot motor;



//distance variables
const int trigPin = 6;
const int echoPin = 5;

const int AIN1 = 13;      
const int AIN2 = 12;          
const int PWMA = 11;
const int PWMB = 10;           
const int BIN2 = 9;           
const int BIN1 = 8; 

int switchPin = 7;             //switch to turn the robot on and off

float distance = 0;            //variable to store the distance measured by the distance sensor

//robot behaviour variables
int backupTime = 300;           //amount of time that the robot will back up when it senses an object
int turnTime = 200;             //amount that the robot will turn once it has backed up

//fsm setup
#define ST_STOP_WHEELS 1
#define ST_DRIVE_FORWARDS 2
#define ST_DRIVE_BACKWARDS 3
#define ST_TURN_LEFT 4
#define ST_SPECIAL_SENSOR 5

int machine_state;

//led 
int photoresistor = 0;              
int threshold = 350; 


/********************************************************************************/
void setup()
{
  pinMode(trigPin, OUTPUT);       //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);        //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  pinMode(4, OUTPUT);
  //set the motor control pins as outputs

  Serial.begin(9600);                       //begin serial communication with the computer
  //wdt_enable(WDTO_60MS);
  Serial.print("To infinity and beyond!");  //test the serial connection
  machine_state = ST_STOP_WHEELS;
}

/********************************************************************************/
void loop()
{

  do_state_things();
  test_transition();
  delay(300);
 // wdt_reset();
}

//fsm machine that performs whatever action the robot is supposed to do
void do_state_things()
{
  switch(machine_state)
  {
    case ST_STOP_WHEELS:
     motor.stopWheelsRight(0);
     motor.stopWheelsLeft(0); 
    break;

    case ST_DRIVE_FORWARDS:
      digitalWrite(4, LOW);
      Serial.print(" ");
      Serial.print("Moving...");
      motor.driveForwardRight(255);
      motor.driveForwardLeft(255); 
    break;

    case ST_DRIVE_BACKWARDS:
       Serial.print(" ");
       Serial.print("BACK!");
       //stop for a moment
       motor.stopWheelsRight(0);
       motor.stopWheelsLeft(0);
       delay(200);
       motor.driveBackwardsRight(-255);
       motor.driveBackwardsLeft(-255);
       delay(backupTime);
    break;

    case ST_TURN_LEFT:
       motor.driveForwardRight(255);
       motor.driveBackwardsLeft(-255);
       delay(turnTime);
    break;

    case ST_SPECIAL_SENSOR:
       motor.stopWheelsRight(0);
       motor.stopWheelsLeft(0); 
       Serial.print("Its too dark its not safe to continue driving!");
       digitalWrite(4, HIGH);
    break;
  }
}
// fsm that decides which action is supposed to be performed by the robot
void test_transition()
{
  distance = getDistance();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" in");
  switch(machine_state)
  {
    case ST_STOP_WHEELS:
       if (digitalRead(switchPin) == LOW)
       {
         
          machine_state = ST_DRIVE_FORWARDS;
       }
       else
       {
          machine_state = ST_STOP_WHEELS;
       }
    break;

    case ST_DRIVE_FORWARDS:
       if (digitalRead(switchPin) == LOW)
        {
          photoresistor = analogRead(A0);
          if (photoresistor > threshold)
          {
            if (distance < 10)
            {
              machine_state = ST_DRIVE_BACKWARDS;
            }
            else
            {
              machine_state = ST_DRIVE_FORWARDS;
            }
          }
          else
          {
            machine_state = ST_SPECIAL_SENSOR;
          }
        }
        else
        {
          machine_state = ST_STOP_WHEELS;
        }
    break;

    case ST_DRIVE_BACKWARDS:
        machine_state = ST_TURN_LEFT;
    break;

    case ST_TURN_LEFT:
        machine_state = ST_DRIVE_FORWARDS;
    break;

    case ST_SPECIAL_SENSOR:
          photoresistor = analogRead(A0);
          if (photoresistor > threshold) 
          {
                machine_state = ST_DRIVE_FORWARDS;  
          }         
    break;
  }
 
}
/********************************************************************************/
//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}
