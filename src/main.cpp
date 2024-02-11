#include "main.h"

static wisco::MatchController match_controller{MatchControllerFactory::createMatchController()};

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
    match_controller.initialize();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	match_controller.disabled();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize()
{
	match_controller.competitionInitialize();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous()
{
	match_controller.autonomous();
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol()
{
	pros::Controller master{pros::E_CONTROLLER_MASTER};
	pros::MotorGroup leftMotors{19, 20, -11, -12};
	pros::MotorGroup rightMotors{1, 2, -9, -10};
	pros::MotorGroup intakeMotors{13, -3};
	bool arcade{true};

	double leftPower{};
	double rightPower{};
	double intakePower{};
	while (true)
	{
		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
			arcade = !arcade;

		if (arcade)
		{
			leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) +
				master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
			rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) -
				master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
		}
		else
		{
			leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
			rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		}

		intakePower = (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) -
			master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) * INT8_MAX;

		leftMotors.move(leftPower);
		rightMotors.move(rightPower);
		intakeMotors.move(intakePower);

		pros::delay(10);
	}

	match_controller.operatorControl();
}