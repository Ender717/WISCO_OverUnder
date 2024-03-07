#ifndef WISCO_HAL_MOTOR_GROUP_HPP
#define WISCO_HAL_MOTOR_GROUP_HPP

#include <memory>
#include <vector>

#include "wisco/io/IMotor.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace for the hardware abstraction layer
 * @author Nathan Sandvig
 *
 */
namespace hal
{

/**
 * @brief A group of motors on the same connected output
 *        SHOULD ONLY BE USED WITH IDENTICAL MOTORS
 * @author Nathan Sandvig
 * 
 */
class MotorGroup
{
private:
    /**
     * @brief The motors in the group
     * 
     */
    std::vector<std::unique_ptr<io::IMotor>> motors{};

public:
    /**
     * @brief Adds a motor to the motor group
     * 
     * @param motor The motor being added to the group
     */
    void addMotor(std::unique_ptr<io::IMotor>& motor);

    /**
     * @brief Initializes the motors
     * 
     */
    void initialize();

    /**
     * @brief Get the torque constant of the motors
     * 
     * @return double The torque constant of the motors
     */
    double getTorqueConstant();

    /**
     * @brief Get the resistance of the motors
     * 
     * @return double The resistance of the motors
     */
    double getResistance();

    /**
     * @brief Get the angular velocity constant of the motors
     * 
     * @return double The angular velocity constant of the motors
     */
    double getAngularVelocityConstant();

    /**
     * @brief Get the gear ratio of the motors (1 if n/a)
     * 
     * @return double The gear ratio of the motors
     */
    double getGearRatio();

    /**
     * @brief Get the angular velocity of the motors in radians/second
     * 
     * @return double The angular velocity of the motors in radians/second
     */
    double getAngularVelocity();

    /**
     * @brief Set the voltage input to the motors in Volts
     * 
     * @param volts The voltage input in Volts
     */
    void setVoltage(double volts);

    /**
     * @brief Override for the assignment operator for MotorGroup
     * 
     * @param rhs The MotorGroup object on the right hand side of the operator
     * @return MotorGroup& This MotorGroup object with the assigned values
     */
    MotorGroup& operator=(MotorGroup& rhs);
};
} // namespace hal
} // namespace wisco

#endif