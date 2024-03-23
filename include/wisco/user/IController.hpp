#ifndef WISCO_USER_I_CONTROLLER_HPP
#define WISCO_USER_I_CONTROLLER_HPP

#include <string>

#include "EControllerAnalog.hpp"
#include "EControllerDigital.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for all user interactive components
 * @author Nathan Sandvig
 * 
 */
namespace user
{

/**
 * @brief Interface for a controller
 * @author Nathan Sandvig
 * 
 */
class IController
{
public:
    /**
     * @brief Destroy the IController object
     * 
     */
    virtual ~IController() = default;

    /**
     * @brief Initializes the controller
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the controller
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Get the analog input of a channel from the controller
     * 
     * @param analog_channel The channel to read analog input from 
     * @return double The value of the analog channel
     */
    virtual double getAnalog(EControllerAnalog analog_channel) = 0;

    /**
     * @brief Get the digital input of a channel from the controller
     * 
     * @param digital_channel The channel to read digital input from
     * @return true The digital channel is active
     * @return false The digital channel is not active
     */
    virtual bool getDigital(EControllerDigital digital_channel) = 0;

    /**
     * @brief Check for a new digital input of a channel from the controller
     * 
     * @param digital_channel The channel to read digital input from
     * @return true The digital channel has a new input
     * @return false The digital channel does not have a new input
     */
    virtual bool getNewDigital(EControllerDigital digital_channel) = 0;

    /**
     * @brief Rumbles the controller
     * 
     * @param pattern The rumble pattern to follow
     *                Up to 8 characters, '.' short, '-' long, ' ' pause
     */
    virtual void rumble(std::string pattern) = 0;
};
} // namespace user
} // namespace wisco

#endif