#ifndef WISCO_MENU_MENU_ADAPTER_HPP
#define WISCO_MENU_MENU_ADAPTER_HPP

#include <vector>

#include "wisco/IMenu.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Program data related to the menu system
 * @author Nathan Sandvig
 * 
 */
namespace menu
{
/**
 * @brief This class adapts the menu system to the IMenu interface
 * @author Nathan Sandvig
 * 
 */
class MenuAdapter : public IMenu
{
private:
    /**
     * @brief The alliances available in the menu system
     * 
     */
    std::vector<std::unique_ptr<IAlliance>> alliances{};

    /**
     * @brief The autonomous routines available in the menu system
     * 
     */
    std::vector<std::unique_ptr<IAutonomous>> autonomous_routines{};

    /**
     * @brief The hardware configurations available in the menu system
     * 
     */
    std::vector<std::unique_ptr<IConfiguration>> hardware_configurations{};

    /**
     * @brief The driver profiles available in the menu system
     * 
     */
    std::vector<std::unique_ptr<IProfile>> driver_profiles{};

public:
    /**
	 * @brief Adds an alliance to the menu system
	 * 
	 * @param alliance The new alliance
	 */
	void addAlliance(std::unique_ptr<IAlliance>& alliance) override;

	/**
	 * @brief Adds an autonomous routine to the menu system
	 * 
	 * @param autonomous The new autonomous routine
	 */
	void addAutonomous(std::unique_ptr<IAutonomous>& autonomous) override;

	/**
	 * @brief Adds a hardware configuration to the menu system
	 * 
	 * @param configuration The new hardware configuration
	 */
	void addConfiguration(std::unique_ptr<IConfiguration>& configuration) override;

	/**
	 * @brief Adds a driver profile to the menu system
	 * 
	 * @param profile The new driver profile
	 */
	void addProfile(std::unique_ptr<IProfile>& profile) override;

    /**
     * @brief Displays the menu
     * 
     */
    void display() override;

    /**
     * @brief Checks if the system is started
     * 
     * @return true The system is started
     * @return false The system is not started
     */
    bool isStarted() override;

    /**
     * @brief Get the System Configuration settings
     * 
     * @return SystemConfiguration The system configuration settings
     */
    SystemConfiguration getSystemConfiguration() override;
};
}
}

#endif