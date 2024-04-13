#include "main.h"
#include "wisco/control/path/QuinticBezierSpline.hpp"
#include "pros/screen.hpp"

#define TESTING false

static wisco::MatchController match_controller{MatchControllerFactory::createMatchController()};

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize()
{
	/*
	auto drive_test{wisco::testing::TestFactory::createDriveTest()};
	drive_test->initialize();
	drive_test->runLinearTest();
	pros::delay(2000);
	drive_test->runTurningTest();
	*/
	if (TESTING)
	{
		std::vector<wisco::control::path::Point> control_points
		{
			wisco::control::path::Point{36.0, 24.0},
			wisco::control::path::Point{36.0, 36.0},
			wisco::control::path::Point{60.0, 36.0},
			wisco::control::path::Point{60.0, 60.0},
			wisco::control::path::Point{60.0, 84.0},
			wisco::control::path::Point{36.0, 108.0},
			wisco::control::path::Point{36.0, 132.0}
		};
		std::vector<wisco::control::path::Point> spline{wisco::control::path::QuinticBezierSpline::calculate(control_points)};

		pros::screen::set_pen(pros::Color::yellow);
		for (auto point : spline)
		{
			pros::screen::fill_circle(static_cast<int16_t>(point.getX()), static_cast<int16_t>(point.getY()), 1);
		}
		pros::screen::set_pen(pros::Color::red);
		for (auto point : control_points)
		{
			pros::screen::fill_circle(static_cast<int16_t>(point.getX()), static_cast<int16_t>(point.getY()), 3);
		}
		while (true);
	}	
	else
	{
		match_controller.initialize();
	}
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled()
{
	if (TESTING)
	{

	}
	else
	{
		match_controller.disabled();
	}
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
	if (TESTING)
	{

	}
	else
	{
		match_controller.competitionInitialize();
	}
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
	if (TESTING)
	{

	}
	else
	{
		match_controller.autonomous();
	}
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
	if (TESTING)
	{

	}
	else
	{
		match_controller.operatorControl();
	}
}