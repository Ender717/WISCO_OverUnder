#ifndef WISCO_PROFILES_JOHN_PROFILE_HPP
#define WISCO_PROFILES_JOHN_PROFILE_HPP

#include <map>

#include "wisco/IProfile.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the available driver profiles
 * @author Nathan Sandvig
 *
 */
namespace profiles
{
/**
 * @brief Driver profile for John
 * @author Nathan Sandvig
 */
class JohnProfile : public IProfile
{
private:
    /**
     * @brief The name of the profile
     * 
     */
    static constexpr char PROFILE_NAME[]{"JOHN"};

    /**
     * @brief The chassis control mode of the profile
     * 
     */
    static constexpr char CHASSIS_CONTROL_MODE[]{"ARCADE"};

    /**
     * @brief The mapping of the controls to the digital inputs
     * 
     */
    const std::map<std::string, std::string> CONTROL_MAP{};

public:
	/**
	 * @brief Get the name of the profile
	 *
	 * @return std::string The name of the profile
	 */
	std::string getName() override;

	/**
	 * @brief Get the chassis control mode
	 *
	 * @return std::string The chassis control mode
	 */
	std::string getChassisControlMode() override;

	/**
	 * @brief Get the mapping of a control to digital inputs
	 *
	 * @return std::string The mapping of this control to a digital input
	 */
	std::string getControlMapping(std::string control) override;
};
}
}

#endif