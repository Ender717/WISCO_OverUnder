#ifndef WISCO_MENU_MENU_ADAPTER_HPP
#define WISCO_MENU_MENU_ADAPTER_HPP

#include <vector>

#include "wisco/IMenu.hpp"

#include "LvglMenu.hpp"

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
     * @brief The alliance option name
     * 
     */
    static constexpr char ALLIANCE_OPTION_NAME[]{"ALLIANCE"};

    /**
     * @brief The autonomous option name
     * 
     */
    static constexpr char AUTONOMOUS_OPTION_NAME[]{"AUTON"};

    /**
     * @brief The configuration option name
     * 
     */
    static constexpr char CONFIGURATION_OPTION_NAME[]{"CONFIG"};

    /**
     * @brief The profile option name
     * 
     */
    static constexpr char PROFILE_OPTION_NAME[]{"PROFILE"};

    /**
     * @brief The alliances available in the menu system
     * 
     */
    std::vector<std::shared_ptr<IAlliance>> alliances{};

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

    /**
     * @brief The lvgl menu being adapted
     * 
     */
    LvglMenu lvgl_menu{};

public:
    /**
	 * @brief Adds an alliance to the menu system
	 * 
	 * @param alliance The new alliance
	 */
	void addAlliance(const std::shared_ptr<IAlliance>& alliance) override;

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
     * @param read_only Whether or not to read the data instead of using the menu data
     * @return SystemConfiguration The system configuration settings
     */
    SystemConfiguration getSystemConfiguration(bool read_only = false) override;
};
}
}

#endif