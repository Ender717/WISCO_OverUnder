#ifndef WISCO_I_MENU_HPP
#define WISCO_I_MENU_HPP

#include "SystemConfiguration.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Interface for the menu system
 * @author Nathan Sandvig
 *
 */
class IMenu
{
public:
	/**
	 * @brief Destroy the IMenu object
	 *
	 */
	virtual ~IMenu() = default;

	/**
	 * @brief Adds an alliance to the menu system
	 * 
	 * @param alliance The new alliance
	 */
	virtual void addAlliance(const std::shared_ptr<IAlliance>& alliance) = 0;

	/**
	 * @brief Adds an autonomous routine to the menu system
	 * 
	 * @param autonomous The new autonomous routine
	 */
	virtual void addAutonomous(std::unique_ptr<IAutonomous>& autonomous) = 0;

	/**
	 * @brief Adds a hardware configuration to the menu system
	 * 
	 * @param configuration The new hardware configuration
	 */
	virtual void addConfiguration(std::unique_ptr<IConfiguration>& configuration) = 0;

	/**
	 * @brief Adds a driver profile to the menu system
	 * 
	 * @param profile The new driver profile
	 */
	virtual void addProfile(std::unique_ptr<IProfile>& profile) = 0;

	/**
	 * @brief Display the menu
	 *
	 */
	virtual void display() = 0;

	/**
	 * @brief Check if the system has been started
	 *
	 * @return true The system has been started
	 * @return false The system has not been started
	 */
	virtual bool isStarted() = 0;

	/**
	 * @brief Get the system configuration information
	 *
	 * @param read_only Whether or not to read the data instead of using the menu data
	 * @return SystemConfiguration The system configuration information
	 */
	virtual SystemConfiguration getSystemConfiguration(bool read_only = false) = 0;
};
} // namespace wisco

#endif