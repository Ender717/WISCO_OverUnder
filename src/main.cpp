#include "main.h"
#include "pros/rotation.hpp"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "pros/vision.hpp"

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
	if (TESTING)
	{

	}	
	else
	{
		bool fast_init{pros::competition::is_connected() && !pros::competition::is_disabled()};
		match_controller.initialize(fast_init);
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
		int vision_box_x{40}, vision_box_y{10};
		int vision_width{316}, vision_height{212};
		pros::screen::set_pen(pros::Color::white);
		pros::screen::draw_rect(vision_box_x, vision_box_y, vision_box_x + vision_width + 2, vision_box_y + vision_height + 2);
		pros::Vision vision_sensor(14);
		pros::vision_signature_s_t blue_triball_sig = pros::c::vision_signature_from_utility(1, -3855, -2239, -3047, 5083, 9307, 7195, 2.000, 0);
		vision_sensor.set_signature(1, &blue_triball_sig);
		pros::vision_signature_s_t green_triball_sig = pros::c::vision_signature_from_utility(2, -6145, -4515, -5330, -6257, -4479, -5368, 3.100, 0);
		vision_sensor.set_signature(2, &green_triball_sig);
		pros::vision_signature_s_t red_triball_sig = pros::c::vision_signature_from_utility(3, 9305, 10661, 9983, -1959, -1279, -1619, 3.000, 0);
		vision_sensor.set_signature(3, &red_triball_sig);
		while (true)
		{
			pros::screen::set_eraser(pros::Color::black);
			pros::screen::erase_rect(vision_box_x + 1, vision_box_y + 1, vision_box_x + vision_width + 1, vision_box_y + vision_height + 1);

			for (uint8_t i{}; i < vision_sensor.get_object_count(); ++i)
			{
				pros::vision_object_s_t object = vision_sensor.get_by_size(i);
				if (object.signature == 1)
					pros::screen::set_pen(pros::Color::blue);
				else if (object.signature == 2)
					pros::screen::set_pen(pros::Color::lime_green);
				else if (object.signature == 3)
					pros::screen::set_pen(pros::Color::red);
				else
					pros::screen::set_pen(pros::Color::yellow);
				int x0{object.x_middle_coord - (object.width / 2)};
				int y0{object.y_middle_coord - (object.height / 2)};
				int x1{object.x_middle_coord + (object.width / 2)};
				int y1{object.y_middle_coord + (object.height / 2)};
				x0 += vision_box_x + 1;
				y0 += vision_box_y + 1;
				x1 += vision_box_x + 1;
				y1 += vision_box_y + 1;
				pros::screen::fill_rect(x0, y0, x1, y1);
			}
			pros::delay(20);
		}
	}
	else
	{
		match_controller.operatorControl();
	}
}