
task main()
{
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


}
