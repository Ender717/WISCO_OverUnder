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
	 * @return SystemConfiguration The system configuration information
	 */
	virtual SystemConfiguration getSystemConfiguration() = 0;
};
} // namespace wisco

#endif