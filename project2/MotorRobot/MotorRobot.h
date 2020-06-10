#ifndef MotorRobot_h
#define MotorRobot_h
#include "Arduino.h"


class MotorRobot
{
	public:
		
	
	
		MotorRobot();
		void driveForwardRight(int motorSpeed);
		void driveForwardLeft(int motorSpeed);
		void driveBackwardsRight(int motorSpeed);
		void driveBackwardsLeft(int motorSpeed);
		void stopWheelsRight(int motorSpeed);
		void stopWheelsLeft(int motorSpeed);
	private:
	
};
#endif