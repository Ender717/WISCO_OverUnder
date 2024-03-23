#ifndef PROS_ADAPTERS_PROS_CONTROLLER_HPP
#define PROS_ADAPTERS_PROS_CONTROLLER_HPP

#include <map>
#include <memory>

#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"

#include "wisco/user/IController.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros controller adapter for the wisco user IController interface
 * @author Nathan Sandvig
 * 
 */
class ProsController : public wisco::user::IController
{
private:
    /**
     * @brief The delay in the task loop
     * 
     */
    static constexpr uint8_t TASK_DELAY{10};

    /**
     * @brief The refresh rate of the rumble output
     * 
     */
    static constexpr uint8_t RUMBLE_REFRESH_RATE{50};

    /**
     * @brief Converts the analog values to [-1, 1]
     * 
     */
    static constexpr double ANALOG_CONVERSION{1.0 / 127};

    /**
     * @brief The maximum length of a rumble pattern
     * 
     */
    static constexpr uint8_t MAX_RUMBLE_LENGTH{8};

    /**
     * @brief The task loop function for background updates
     * 
     * @param params 
     */
    static void taskLoop(void* params);

    /**
     * @brief The mapping of analog controls
     * 
     */
    const std::map<wisco::user::EControllerAnalog, pros::controller_analog_e_t> ANALOG_MAP
    {
        {wisco::user::EControllerAnalog::JOYSTICK_LEFT_X, pros::E_CONTROLLER_ANALOG_LEFT_X},
        {wisco::user::EControllerAnalog::JOYSTICK_LEFT_Y, pros::E_CONTROLLER_ANALOG_LEFT_Y},
        {wisco::user::EControllerAnalog::JOYSTICK_RIGHT_X, pros::E_CONTROLLER_ANALOG_RIGHT_X},
        {wisco::user::EControllerAnalog::JOYSTICK_RIGHT_Y, pros::E_CONTROLLER_ANALOG_RIGHT_Y}
    };

    /**
     * @brief The mapping of digital controls
     * 
     */
    const std::map<wisco::user::EControllerDigital, pros::controller_digital_e_t> DIGITAL_MAP
    {
        {wisco::user::EControllerDigital::BUTTON_A, pros::E_CONTROLLER_DIGITAL_A},
        {wisco::user::EControllerDigital::BUTTON_B, pros::E_CONTROLLER_DIGITAL_B},
        {wisco::user::EControllerDigital::BUTTON_X, pros::E_CONTROLLER_DIGITAL_X},
        {wisco::user::EControllerDigital::BUTTON_Y, pros::E_CONTROLLER_DIGITAL_Y},
        {wisco::user::EControllerDigital::DPAD_DOWN, pros::E_CONTROLLER_DIGITAL_DOWN},
        {wisco::user::EControllerDigital::DPAD_LEFT, pros::E_CONTROLLER_DIGITAL_LEFT},
        {wisco::user::EControllerDigital::DPAD_RIGHT, pros::E_CONTROLLER_DIGITAL_RIGHT},
        {wisco::user::EControllerDigital::DPAD_UP, pros::E_CONTROLLER_DIGITAL_UP},
        {wisco::user::EControllerDigital::SCUFF_LEFT_REAR, pros::E_CONTROLLER_DIGITAL_RIGHT},
        {wisco::user::EControllerDigital::SCUFF_RIGHT_REAR, pros::E_CONTROLLER_DIGITAL_Y},
        {wisco::user::EControllerDigital::TRIGGER_LEFT_BOTTOM, pros::E_CONTROLLER_DIGITAL_L2},
        {wisco::user::EControllerDigital::TRIGGER_LEFT_TOP, pros::E_CONTROLLER_DIGITAL_L1},
        {wisco::user::EControllerDigital::TRIGGER_RIGHT_BOTTOM, pros::E_CONTROLLER_DIGITAL_R2},
        {wisco::user::EControllerDigital::TRIGGER_RIGHT_TOP, pros::E_CONTROLLER_DIGITAL_R1}
    };

    /**
     * @brief The controller being adapted
     * 
     */
    std::unique_ptr<pros::Controller> m_controller{};

    /**
     * @brief The mutex for thread safety
     * 
     */
    pros::Mutex mutex{};

    /**
     * @brief The current rumble pattern
     * 
     */
    char rumble_pattern[MAX_RUMBLE_LENGTH]{};

    /**
     * @brief Whether or not there is a new rumble pattern
     * 
     */
    bool new_rumble_pattern{};

    /**
     * @brief The last time the rumble was refreshed
     * 
     */
    uint32_t last_rumble_refresh{};

    /**
     * @brief Updates the rumble
     * 
     */
    void updateRumble();

    /**
     * @brief Runs in the task loop to update the controller
     * 
     */
    void taskUpdate();

public:
    /**
     * @brief Construct a new Pros Controller object
     * 
     * @param controller The controller being adapted
     */
    ProsController(std::unique_ptr<pros::Controller>& controller);

    /**
     * @brief Initializes the controller
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the controller
     * 
     */
    void run() override;

    /**
     * @brief Get the analog input of a channel from the controller
     * 
     * @param analog_channel The channel to read analog input from 
     * @return double The value of the analog channel
     */
    double getAnalog(wisco::user::EControllerAnalog analog_channel) override;

    /**
     * @brief Get the digital input of a channel from the controller
     * 
     * @param digital_channel The channel to read digital input from
     * @return true The digital channel is active
     * @return false The digital channel is not active
     */
    bool getDigital(wisco::user::EControllerDigital digital_channel) override;

    /**
     * @brief Check for a new digital input of a channel from the controller
     * 
     * @param digital_channel The channel to read digital input from
     * @return true The digital channel has a new input
     * @return false The digital channel does not have a new input
     */
    bool getNewDigital(wisco::user::EControllerDigital digital_channel) override;

    /**
     * @brief Rumbles the controller
     * 
     * @param pattern The rumble pattern to follow
     *                Up to 8 characters, '.' short, '-' long, ' ' pause
     */
    void rumble(std::string pattern) override;
};
} // namespace pros_adapters

#endif