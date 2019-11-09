#pragma config(Motor,  port1,           frontRight,    tmotorVex269_HBridge, openLoop)
#pragma config(Motor,  port2,           backLeft,      tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port9,           frontLeft,     tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          backRight,     tmotorVex269_HBridge, openLoop)

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
int modeChanger=1;
float div=1.27;

void pre_auton()
{
	// Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
	// Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
	bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	// .....................................................................................
	// Insert user code here.
	// .....................................................................................

	AutonomousCodePlaceholderForTesting();  // Remove this function call once you have "real" code.
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task ourArcadeControl(){
	while (true)
	{
		if(abs(vexRT[Ch3])>15){
			motor[frontRight]=-vexRT[Ch3]/div;
			motor[frontLeft]=vexRT[Ch3]/div;
			motor[backRight]=-vexRT[Ch3]/div;
			motor[backLeft]=vexRT[Ch3]/div;
			}
			else if(abs(vexRT[Ch1])>15){
			motor[frontRight]=-vexRT[Ch1]/div;
			motor[frontLeft]=-vexRT[Ch1]/div;
			motor[backRight]=-vexRT[Ch1]/div;
			motor[backLeft]=-vexRT[Ch1]/div;
			} else {
			motor[frontRight]=0;
			motor[frontLeft]=0;
			motor[backRight]=0;
			motor[backLeft]=0;

		}
	}
}

task ourTankDrive(){
	while(true){
		if(abs(vexRT[Ch2])>20){
			motor[frontRight]=vexRT[Ch2]/div;
			motor[backRight]=vexRT[Ch2]/div;
		}
		if(abs(vexRT[Ch3])>20){
			motor[frontLeft]=vexRT[Ch3]/div;
			motor[backLeft]=vexRT[Ch3]/div;
			} else {
			motor[frontRight]=0;
			motor[frontLeft]=0;
			motor[backRight]=0;
			motor[backLeft]=0;

		}
	}
}
task usercontrol()
{
	startTask(ourArcadeControl);
	// User control code here, inside the loop
	while (true){
		if(vexRT[Btn5UXmtr2]==1&&modeChanger==1){
			stopTask(ourArcadeControl);
			startTask(ourTankDrive);
			modeChanger--;
		}
		if(vexRT[Btn5UXmtr2]==1&&modeChanger==0){
			stopTask(ourTankDrive);
			startTask(ourArcadeControl);
			modeChanger++;
		}
	}
}
