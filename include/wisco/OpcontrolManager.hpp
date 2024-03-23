#ifndef WISCO_OPCONTROL_MANAGER_HPP
#define WISCO_OPCONTROL_MANAGER_HPP

#include <memory>

#include "io/ITouchScreen.hpp"
#include "robot/subsystems/position/Position.hpp"
#include "robot/subsystems/drive/Velocity.hpp"
#include "rtos/IDelayer.hpp"
#include "IProfile.hpp"
#include "user/IController.hpp"
#include "robot/Robot.hpp"

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
	static constexpr uint8_t CONTROL_DELAY{10};
	/**
	 * @brief The driver profile
	 *
	 */
	std::unique_ptr<IProfile> m_profile{};

public:
	/**
	 * @brief Set the operator profile
	 *
	 * @param profile The operator profile
	 */
	void setProfile(std::unique_ptr<IProfile>& profile);

	/**
	 * @brief Initialize the operator control
	 *
	 * @param robot The robot being controlled
	 */
	void initializeOpcontrol(std::shared_ptr<robot::Robot> robot);

	/**
	 * @brief Run the operator control
	 *
	 * @param robot The robot being controlled
	 * @param delayer The rtos delayer
	 */
	void runOpcontrol(std::shared_ptr<user::IController> controller, std::shared_ptr<robot::Robot> robot, std::shared_ptr<io::ITouchScreen> touch_screen, std::shared_ptr<rtos::IDelayer> delayer);
};

} // namespace wisco

#endif