#include "MotorRobot.h"
MotorRobot::MotorRobot()
{
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void MotorRobot::driveForwardRight(int motorSpeed)
{
	digitalWrite(AIN1, HIGH);                         
    digitalWrite(AIN2, LOW);
	analogWrite(PWMA, abs(motorSpeed));
}
void MotorRobot::driveForwardLeft(int motorSpeed)
{
	digitalWrite(BIN1, HIGH);                         
    digitalWrite(BIN2, LOW);
	analogWrite(PWMB, abs(motorSpeed));
}
void MotorRobot::driveBackwardsRight(int motorSpeed)
{
	digitalWrite(AIN1, LOW);                         
    digitalWrite(AIN2, HIGH); 
	analogWrite(PWMA, abs(motorSpeed)); 
}
void MotorRobot::driveBackwardsLeft(int motorSpeed)
{
	digitalWrite(BIN1, LOW);                         
    digitalWrite(BIN2, HIGH); 
	analogWrite(PWMB, abs(motorSpeed));	
}

void MotorRobot::stopWheelsRight(int motorSpeed)
{
	digitalWrite(AIN1, LOW);                          
    digitalWrite(AIN2, LOW); 
	analogWrite(PWMA, abs(motorSpeed));
}
void MotorRobot::stopWheelsLeft(int motorSpeed)
{ 
	digitalWrite(BIN1, LOW);                          
    digitalWrite(BIN2, LOW);
	analogWrite(PWMB, abs(motorSpeed));
}
