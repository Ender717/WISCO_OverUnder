#ifndef WISCO_OPCONTROL_MANAGER_HPP
#define WISCO_OPCONTROL_MANAGER_HPP

#include <memory>

#include "rtos/IClock.hpp"
#include "rtos/IDelayer.hpp"
#include "IProfile.hpp"
#include "user/IController.hpp"
#include "robot/Robot.hpp"

#include "user/drive/DifferentialDriveOperator.hpp"
#include "user/elevator/ElevatorOperator.hpp"
#include "user/hang/HangOperator.hpp"
#include "user/intake/IntakeOperator.hpp"
#include "user/loader/LoaderOperator.hpp"
#include "user/wings/WingsOperator.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Manages the execution of the operator control
 * @author Nathan Sandvig
 *
 */
class OPControlManager
{
private:
	/**
	 * @brief The loop delay for control inputs
	 * 
	 */
	static constexpr uint32_t CONTROL_DELAY{10};

	/**
	 * @brief The rtos clock for the control loop
	 * 
	 */
	std::shared_ptr<rtos::IClock> m_clock{};

	/**
	 * @brief The rtos delayer for the control loop
	 * 
	 */
	std::unique_ptr<rtos::IDelayer> m_delayer{};

	/**
	 * @brief The driver profile
	 *
	 */
	std::unique_ptr<IProfile> m_profile{};

public:
	/**
	 * @brief Construct a new OPControlManager object
	 * 
	 * @param clock The rtos clock
	 * @param delayer The rtos delayer
	 */
	OPControlManager(const std::shared_ptr<rtos::IClock>& clock, const std::unique_ptr<rtos::IDelayer>& delayer);

	/**
	 * @brief Set the operator profile
	 *
	 * @param profile The operator profile
	 */
	void setProfile(std::unique_ptr<IProfile>& profile);

	/**
	 * @brief Initialize the operator control
	 *
	 * @param controller The controller for the robot
	 * @param robot The robot being controlled
	 */
	void initializeOpcontrol(std::shared_ptr<user::IController> controller, std::shared_ptr<robot::Robot> robot);

	/**
	 * @brief Run the operator control
	 *
	 * @param controller The controller for the robot
	 * @param robot The robot being controlled
	 */
	void runOpcontrol(std::shared_ptr<user::IController> controller, std::shared_ptr<robot::Robot> robot);
};

} // namespace wisco

#endif