#ifndef WISCO_SYSTEM_CONFIGURATION_HPP
#define WISCO_SYSTEM_CONFIGURATION_HPP

#include <memory>

#include "IAlliance.hpp"
#include "IAutonomous.hpp"
#include "IConfiguration.hpp"
#include "IProfile.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Holds the system configuration information
 * @author Nathan Sandvig
 *
 */
struct SystemConfiguration
{
	/**
	 * @brief The system alliance
	 *
	 */
	std::unique_ptr<IAlliance> alliance{};

	/**
	 * @brief The system autonomous
	 *
	 */
	std::unique_ptr<IAutonomous> autonomous{};

	/**
	 * @brief The system configuration
	 *
	 */
	std::unique_ptr<IConfiguration> configuration{};

	/**
	 * @brief The system profile
	 *
	 */
	std::unique_ptr<IProfile> profile{};
};

} // namespace wisco

#endif