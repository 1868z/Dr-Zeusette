  #pragma config(Sensor, in1,    pot,            sensorPotentiometer)
#pragma config(Sensor, dgtl3,  ultraIn,        sensorSONAR_cm)
#pragma config(Motor,  port1,           ForkDown,      tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           backRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           frontLeft,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           Motor6,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           Motor7,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Motor8,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Motor9,        tmotorVex393_MC29, openLoop, reversed)

void fwom();
void drivestraight(int speed, int duration);
void driveside(int speed, int duration);
void forklift(int speed, int duration);

int minPower = 30;

// Move robot to position "target".
void Cposition (int target) {
	while(SensorValue[ultraIn] < target) {
		int power = target-SensorValue[ultraIn];
		if (power < minPower) power = minPower;
		drivestraight(power, 0);
	}
	drivestraight(0,0);
}

// This function is invoked when the robot enters Autonomous.
// This is either during competition or if you press 7U and 8U at once.
void autonomous() {
	Cposition(90);
	fwom();
	forklift(-70, 1000);
	forklift(0,0);
	Cposition(125);

	forklift(70, 650);
	forklift(-70, 400);
	forklift(0,0);
	wait1Msec(200);
	driveside(80, 900);
	driveside(0,0);
	forklift(70, 400);
	forklift(-70, 700);
	forklift(0,0);
	wait1Msec(200);
	driveside(80, 800);
	driveside(0,0);
	forklift(70, 400);
	forklift(-70, 400);
	forklift(0,0);
}

void setArmSpeed(int power) {
	motor[Motor6] = power;
	motor[Motor7] = power;
	motor[Motor8] = power;
	motor[Motor9] = power;

}
int threshold = 15;

void fwom () {
	motor[ForkDown] = 127;
	wait1Msec(500);
	motor[ForkDown] = -127;
	wait1Msec(500);
	motor[ForkDown] = 0;
}

void drivestraight(int speed, int duration) {
	motor[frontRight] = speed;
	motor[backRight] = speed;
	motor[frontLeft] = speed;
	motor[backLeft] = speed;
	wait1Msec(duration);
}

void driveside(int speed, int duration) {
  motor[frontRight] = - speed;
  motor[backRight] =  + speed;
  motor[frontLeft] =  + speed;
  motor[backLeft] =   - speed;
  wait1Msec(duration);
}

void forklift(int speed, int duration) {
 motor[Motor6] = speed;
 motor[Motor7] =  speed;
 motor[Motor8] = speed;
 motor[Motor9] = speed;
 wait1Msec(duration);
}



// This function is invoked in a loop to perform driver control.
void joystick() {

  if(vexRT[Btn5UXmtr2]) {
  	fwom();
  }
	// Mecanum style, with a threshold. The threshold avoids having
  // a joystick that is too sensitive throw off the direction of
  // robot.
  // http://www.robotc.net/blog/2011/11/22/vex-mecanum-drive-using-robotc/
  int X2 = 0, Y1 = 0, X1 = 0;

  if(abs(vexRT[Ch3]) > threshold) Y1 = vexRT[Ch3];
  if(abs(vexRT[Ch4]) > threshold) X1 = vexRT[Ch4];
  if(abs(vexRT[Ch1]) > threshold) X2 = vexRT[Ch1];

  //Remote Control Commands
  motor[frontRight] = Y1 - X2 - X1;
  motor[backRight] =  Y1 - X2 + X1;
  motor[frontLeft] =  Y1 + X2 + X1;
  motor[backLeft] =   Y1 + X2 - X1;


  setArmSpeed(-vexRT[Ch2Xmtr2] * 0.8);
}

// ==========================================================================
// ========= Things below this line don't need to be modified ===============
// ==========================================================================

  //                             ,|
  //                           //|                              ,|
  //                         //,/                             -~ |
  //                       // / |                         _-~   /  ,
  //                     /'/ / /                       _-~   _/_-~ |
  //                    ( ( / /'                   _ -~     _-~ ,/'
  //                     \~\/'/|             __--~~__--\ _-~  _/,
  //             ,,)))))));, \/~-_     __--~~  --~~  __/~  _-~ /
  //          __))))))))))))));,>/\   /        __--~~  \-~~ _-~
  //         -\(((((''''(((((((( >~\/     --~~   __--~' _-~ ~|
  //--==//////((''  .     `)))))), /     ___---~~  ~~\~~__--~
  //        ))| @    ;-.     (((((/           __--~~~'~~/
  //        ( `|    /  )      )))/      ~~~~~__\__---~~__--~~--_
  //           |   |   |       (/      ---~~~/__-----~~  ,;::'  \         ,
  //           o_);   ;        /      ----~~/           \,-~~~\  |       /|
  //                 ;        (      ---~~/         `:::|      |;|      < >
  //                |   _      `----~~~~'      /      `:|       \;\_____//
  //          ______/\/~    |                 /        /         ~------~
  //        /~;;.____/;;'  /          ___----(   `;;;/
  //       / //  _;______;'------~~~~~    |;;/\    /
  //      //  | |                        /  |  \;;,\
  //     (<_  | ;                      /',/-----'  _>
  //      \_| ||_                     //~;~~~~~~~~~
  //          `\_|                   (,~~
  //                                  \~\
  //                                   ~~


// True while autonomous is still running.
bool autonomous_on = false;

// Autonomous task. Invokes the user program and ensures
// |autonomous_on| is reset when the task is done.
task autonomous_task() {
	autonomous();
	autonomous_on = false;
}

// Continuously updates the display based on battery and mode.
task updateDisplay()
{
	char status[32];

	while (true) {
		if ((vexRT[Btn7U] && vexRT[Btn8U]) || bIfiAutonomousMode) {
			if (!autonomous_on) {
			  autonomous_on = true;
			  startTask(autonomous_task);
		  }
		}
		clearLCDLine(0);
    if (bIfiRobotDisabled) {
    	displayLCDCenteredString(0, "Dead Zeusette");
    } else {
    	displayLCDCenteredString(0, autonomous_on ? "Autozeusette!" : "Superzeusette!");
    }
	  clearLCDLine(1);
  	//snprintf(status, sizeof(status)-1, "bat %d", nAvgBatteryLevel);
  	snprintf(status, sizeof(status)-1, "sens %d", SensorValue[ultraIn]);
  	displayLCDCenteredString(1, status);
		wait1Msec(100);


	}
}

// Starts the display and enters optimistic user controlled.
task main()
{
	startTask(updateDisplay);


	// For competition, don't start too early.
	while (bIfiRobotDisabled) {
		wait1Msec(25);
	}

	while (true) {
		if (autonomous_on) {
			wait1Msec(25);
			continue;
		}
		joystick();
  }
}
