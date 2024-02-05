#ifndef WISCO_CONFIGS_BLUE_CONFIGURATION_HPP
#define WISCO_CONFIGS_BLUE_CONFIGURATION_HPP

#include "wisco/IConfiguration.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for hardware configurations
 * @author Nathan Sandvig
 * 
 */
namespace configs
{
class BlueConfiguration : public IConfiguration
{
private:
    /**
     * @brief The name of the configuration
     * 
     */
    static constexpr char CONFIGURATION_NAME[]{"BLUE"};

public:
    /**
	 * @brief Get the name of the configuration
	 *
	 * @return std::string The name of the configuration
	 */
	std::string getName() override;

	/**
	 * @brief Build a robot using this configuration
	 *
	 * @return robot::Robot The robot built by this configuration
	 */
	std::shared_ptr<robot::Robot> buildRobot() override;
};
}
}

#endif