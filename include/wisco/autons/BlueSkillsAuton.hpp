#ifndef WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP
#define WISCO_AUTONS_BLUE_SKILLS_AUTON_HPP

#include <cmath>

#include "pros_adapters/ProsMutex.hpp"
#include "pros_adapters/ProsTask.hpp"

#include "wisco/routines/SentryMode.hpp"
#include "wisco/utils/UtilityFunctions.hpp"
#include "wisco/control/motion/ETurnDirection.hpp"
#include "wisco/control/path/QuinticBezierSpline.hpp"
#include "wisco/robot/subsystems/drive/Velocity.hpp"
#include "wisco/robot/subsystems/position/Position.hpp"

#include "wisco/IAutonomous.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for autonomous routines
 * @author Nathan Sandvig
 * 
 */
namespace autons
{

/**
 * @brief The auton for the blue robot in skills
 * @author Nathan Sandvig
 * 
 */
class BlueSkillsAuton : public IAutonomous
{
private:
    /**
     * @brief The name of the autonomous
     * 
     */
    static constexpr char AUTONOMOUS_NAME[]{"B_SKILLS"};

public:
    /**
	 * @brief Get the name of the autonomous
	 *
	 * @return std::string The name of the autonomous
	 */
	std::string getName() override;

	/**
	 * @brief Initialize the autonomous
	 *
	 * @param control_system The control system
	 * @param robot The robot
	 */
	void initialize(std::shared_ptr<control::ControlSystem> control_system, 
					std::shared_ptr<robot::Robot> robot) override;

	/**
	 * @brief Run the autonomous
	 *
	 * @param alliance The alliance
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 * @param control_system The control system
	 * @param robot The robot
	 */
	void run(std::shared_ptr<IAlliance> alliance,
			 std::shared_ptr<rtos::IClock> clock,
			 std::unique_ptr<rtos::IDelayer>& delayer,
			 std::shared_ptr<control::ControlSystem> control_system, 
			 std::shared_ptr<robot::Robot> robot) override;
};
}
}

#endif