#ifndef WISCO_OPCONTROL_MANAGER_HPP
#define WISCO_OPCONTROL_MANAGER_HPP

#include <memory>

#include "IProfile.hpp"
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
	 */
	void runOpcontrol(std::shared_ptr<robot::Robot> robot);
};

} // namespace wisco

#endif