#include "wisco/autons/BlueMatchAuton.hpp"

namespace wisco
{
namespace autons
{
void BlueMatchAuton::boomerangGoToPoint(std::shared_ptr<control::ControlSystem> control_system, 
						std::shared_ptr<robot::Robot> robot, 
						double velocity, double x, double y, double theta)
{
	if (control_system)
		control_system->sendCommand(BOOMERANG_CONTROL_NAME, BOOMERANG_GO_TO_POSITION_COMMAND_NAME, &robot, velocity, x, y, theta);
}

bool BlueMatchAuton::boomerangTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(BOOMERANG_CONTROL_NAME, BOOMERANG_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

double BlueMatchAuton::intakeBallDistance(std::shared_ptr<robot::Robot> robot)
{
	double ball_distance{};
	if (robot)
	{
		double* result{static_cast<double*>(robot->getState("INTAKE", "GET BALL DISTANCE"))};
		if (result)
		{
			ball_distance = *result;
			delete result;
		}
	}
	return ball_distance;
}

double BlueMatchAuton::elevatorGetPosition(std::shared_ptr<robot::Robot> robot)
{
	double position{};
	if (robot)
	{
		double* result{static_cast<double*>(robot->getState("ELEVATOR", "GET POSITION"))};
		if (result)
		{
			position = *result;
			delete result;
		}
	}
	return position;
}

void BlueMatchAuton::odometrySetPosition(std::shared_ptr<robot::Robot> robot,
										 double x, double y, double theta)
{
	if (robot)
	{
		robot::subsystems::position::Position position{x, y, theta};
		robot->sendCommand(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_SET_POSITION_COMMAND_NAME, position);
	}
}

robot::subsystems::position::Position BlueMatchAuton::odometryGetPosition(std::shared_ptr<robot::Robot> robot)
{
	robot::subsystems::position::Position position{};

	if (robot)
	{
		robot::subsystems::position::Position* result{static_cast<robot::subsystems::position::Position*>(robot->getState(ODOMETRY_SUBSYSTEM_NAME, ODOMETRY_GET_POSITION_STATE_NAME))};
		if (result)
		{
			position = *result;
			delete result;
		}
	}

	return position;
}

void BlueMatchAuton::motionTurnToAngle(std::shared_ptr<control::ControlSystem> control_system, 
									   std::shared_ptr<robot::Robot> robot, 
									   double velocity, double theta, bool reversed,
									   control::motion::ETurnDirection direction)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_ANGLE_COMMAND_NAME, &robot, velocity, theta, static_cast<int>(reversed), direction);
}

void BlueMatchAuton::motionTurnToPoint(std::shared_ptr<control::ControlSystem> control_system, 
									   std::shared_ptr<robot::Robot> robot, 
									   double velocity, double x, double y, bool reversed,
									   control::motion::ETurnDirection direction)
{
	if (control_system)
		control_system->sendCommand(MOTION_CONTROL_NAME, MOTION_TURN_TO_POINT_COMMAND_NAME, &robot, velocity, x, y, static_cast<int>(reversed), direction);
}

bool BlueMatchAuton::motionTurnTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(MOTION_CONTROL_NAME, MOTION_TURN_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

void BlueMatchAuton::pathFollowingFollowPath(std::shared_ptr<control::ControlSystem> control_system, 
											 std::shared_ptr<robot::Robot> robot, 
											 std::vector<control::path::Point> path,
											 double velocity)
{
	if (control_system)
		control_system->sendCommand(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_FOLLOW_PATH_COMMAND_NAME, &robot, &path, velocity);
}

void BlueMatchAuton::pathFollowingSetVelocity(std::shared_ptr<control::ControlSystem> control_system,
											  double velocity)
{
	if (control_system)
		control_system->sendCommand(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_SET_VELOCITY_COMMAND_NAME, velocity);
}

bool BlueMatchAuton::pathFollowingTargetReached(std::shared_ptr<control::ControlSystem> control_system)
{
	bool target_reached{};
	if (control_system)
	{
		bool* result{static_cast<bool*>(control_system->getState(PATH_FOLLOWING_CONTROL_NAME, PATH_FOLLOWING_TARGET_REACHED_STATE_NAME))};
		if (result)
		{
			target_reached = *result;
			delete result;
		}
	}
	return target_reached;
}

bool BlueMatchAuton::validSentryPointLoad(control::path::Point point)
{
	bool valid{true};

	if (point.getX() > 69.0 || point.getX() < 2.0)
		valid = false;

	if (point.getY() > 72.0 || point.getY() < 2.0)
		valid = false;

	if (point.getX() > 45.0 && point.getY() > 21.0 && point.getY() < 27.0)
		valid = false;

	if (point.getX() < 26.0 && point.getY() > 44.0)
		valid = false;

	return valid;
}

bool BlueMatchAuton::validSentryPointGoal(control::path::Point point)
{
	bool valid{true};

	if (point.getX() < 75.0 || point.getX() > 142.0)
		valid = false;

	if (point.getY() > 84.0 || point.getY() < 2.0)
		valid = false;
	
	if (point.getX() < 99.0 && point.getY() > 21.0 && point.getY() < 27.0)
		valid = false;

	if (point.getX() > 118.0 && point.getY() > 44.0)
		valid = false;

	return valid;
}

bool BlueMatchAuton::sentryMode(std::shared_ptr<rtos::IClock> clock,
						  		std::unique_ptr<rtos::IDelayer>& delayer,
						  		std::shared_ptr<control::ControlSystem> control_system, 
								std::shared_ptr<robot::Robot> robot,
								bool new_ball, uint32_t timeout, 
								control::motion::ETurnDirection direction)
{
	uint32_t start_time{clock->getTime()};
	bool found{};
	auto position{odometryGetPosition(robot)};
	double ball_distance{intakeBallDistance(robot)};
	control::path::Point ball_start_point{};
	if (new_ball)
	{
		double ball_x{position.x + (ball_distance * std::cos(position.theta))};
		double ball_y{position.y + (ball_distance * std::sin(position.theta))};
		control::path::Point ball_point{ball_x, ball_y};
		if (position.x < 72.0 && validSentryPointLoad(ball_point) ||
			position.x > 72.0 && validSentryPointGoal(ball_point))
			ball_start_point = ball_point;
		else
			new_ball = false;
	}
	control::path::Point ball_end_point{ball_start_point};
	motionTurnToAngle(control_system, robot, 2 * M_PI, position.theta + M_PI, false, direction);
	delayer->delay(20);
	motionTurnToAngle(control_system, robot, 4 * M_PI / 5, position.theta + M_PI, false, direction);
	while (start_time + timeout > clock->getTime() && !found && !motionTurnTargetReached(control_system))
	{
		position = odometryGetPosition(robot);
		ball_distance = intakeBallDistance(robot);
		double ball_x{position.x + (ball_distance * std::cos(position.theta))};
		double ball_y{position.y + (ball_distance * std::sin(position.theta))};
		control::path::Point ball_point{ball_x, ball_y};
		if ((position.x < 72.0 && validSentryPointLoad(ball_point)) ||
			(position.x > 72.0 && validSentryPointGoal(ball_point)))
		{
			if (ball_start_point.getX() == 0 && ball_start_point.getY() == 0)
				ball_start_point = ball_point;
			ball_end_point = ball_point;
			if (distance(ball_start_point.getX(), ball_start_point.getY(),
						 ball_end_point.getX(), ball_end_point.getY()) > 6.0)
			{
				if (new_ball)
				{
					new_ball = false;
					ball_start_point.setX(0);
					ball_start_point.setY(0);
					ball_end_point.setX(0);
					ball_end_point.setY(0);
				}
				else
				{
					found = true;
				}
			}
		}
		else if (ball_end_point.getX() == 0 && ball_end_point.getY() == 0)
		{
			new_ball = false;
			ball_start_point.setX(0);
			ball_start_point.setY(0);
		}
		else 
		{
			found = true;
		}
		delayer->delay(5);
	}
	control_system->pause();

	control::path::Point ball{(ball_start_point + ball_end_point) / 2};

	if (ball.getX() != 0 || ball.getY() != 0)
	{
		motionTurnToPoint(control_system, robot, 2 * M_PI, ball.getX(), ball.getY());
		while (!motionTurnTargetReached(control_system))
			delayer->delay(10);

		position = odometryGetPosition(robot);
		ball_distance = distance(position.x, position.y, ball.getX(), ball.getY());
		double elevator_distance{std::min(ball_distance - 5, 15.0)};

		robot->sendCommand("ELEVATOR", "SET POSITION", elevator_distance);
		robot->sendCommand("INTAKE", "SET VOLTAGE", 12.0);

		position = odometryGetPosition(robot);
		double target_angle{std::atan2(ball.getY() - position.y, ball.getX() - position.x)};
		double target_distance{elevator_distance + 6};
		if (distance(position.x, position.y, ball.getX(), ball.getY()) > target_distance)
		{
			boomerangGoToPoint(control_system, robot, 36.0, ball.getX(), ball.getY(), target_angle);
			while (distance(position.x, position.y, ball.getX(), ball.getY()) > target_distance)
			{
				delayer->delay(10);
				position = odometryGetPosition(robot);
			}
			control_system->pause();
		}
		while (elevatorGetPosition(robot) < elevator_distance - 1)
			delayer->delay(10);

		robot->sendCommand("ELEVATOR", "SET POSITION", 3.25);
		while (elevatorGetPosition(robot) > 4.0)
			delayer->delay(10);
	}

	return intakeBallDistance(robot) < 12.0;
}

std::string BlueMatchAuton::getName()
{
    return AUTONOMOUS_NAME;
}

void BlueMatchAuton::initialize(std::shared_ptr<control::ControlSystem> control_system, 
					            std::shared_ptr<robot::Robot> robot)
{
	std::vector<control::path::Point> test_path_control_points
	{
		control::path::Point{0.0, 0.0},
		control::path::Point{24.0, 0.0},
		control::path::Point{48.0, 0.0},
		control::path::Point{48.0, 24.0},
		control::path::Point{48.0, 48.0},
		control::path::Point{24.0, 48.0},
		control::path::Point{0.0, 48.0}
	};
	test_path = control::path::QuinticBezierSpline::calculate(test_path_control_points);
}

void BlueMatchAuton::run(std::shared_ptr<rtos::IClock> clock,
						  std::unique_ptr<rtos::IDelayer>& delayer,
						  std::shared_ptr<control::ControlSystem> control_system, 
					      std::shared_ptr<robot::Robot> robot)
{
	odometrySetPosition(robot, 96.0, 48.0, M_PI / 2);

	std::unique_ptr<rtos::IMutex> sentry_mutex{std::make_unique<pros_adapters::ProsMutex>()};
	std::unique_ptr<rtos::ITask> sentry_task{std::make_unique<pros_adapters::ProsTask>()};
	routines::SentryMode sentry_mode{clock, delayer, sentry_mutex, sentry_task, control_system, robot};

	bool sentry{true};
	auto position{odometryGetPosition(robot)};
	double last_ball_angle{};
	while (sentry)
	{
		sentry_mode.run(-M_PI, control::motion::ETurnDirection::COUNTERCLOCKWISE);
		while (!sentry_mode.isFinished())
			delayer->delay(10);
		sentry = sentry_mode.ballFound();
		if (sentry)
		{
			position = odometryGetPosition(robot);
			last_ball_angle = position.theta;
			double target_distance{distance(position.x, position.y, 108.0, 60.0)};
			if (target_distance > 6.0)
			{
				double target_angle{angle(position.x, position.y, 108.0, 60.0)};
				bool reversed{std::abs(bindRadians(target_angle - position.theta)) > M_PI / 2};
				motionTurnToPoint(control_system, robot, 2 * M_PI, 108.0, 60.0, reversed);
				while (!motionTurnTargetReached(control_system))
					delayer->delay(20);

				position = odometryGetPosition(robot);
				boomerangGoToPoint(control_system, robot, 36.0, 108.0, 60.0, position.theta);
				while (!boomerangTargetReached(control_system))
					delayer->delay(20);
			}

			motionTurnToAngle(control_system, robot, 2 * M_PI, 0);
			while (!motionTurnTargetReached(control_system))
				delayer->delay(20);

			robot->sendCommand("ELEVATOR", "SET POSITION", 0.0);
			robot->sendCommand("INTAKE", "SET VOLTAGE", -12.0);
			while (elevatorGetPosition(robot) > 0.5)
				delayer->delay(20);
			
			robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", 12.0, 12.0);
			position = odometryGetPosition(robot);
			while (position.x < 110.0 || position.xV > 8.0)
			{
				delayer->delay(20);
				position = odometryGetPosition(robot);
			}

			robot->sendCommand("DIFFERENTIAL DRIVE", "SET VOLTAGE", -12.0, -12.0);
			delayer->delay(200);

			motionTurnToAngle(control_system, robot, 2 * M_PI, last_ball_angle);
			while (!motionTurnTargetReached(control_system))
				delayer->delay(20);
		}
	}
}
}
}