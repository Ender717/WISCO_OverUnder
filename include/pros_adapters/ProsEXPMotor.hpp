#ifndef PROS_ADAPTERS_PROS_EXP_MOTOR_HPP
#define PROS_ADAPTERS_PROS_EXP_MOTOR_HPP

#include <cmath>
#include <memory>

#include "pros/motors.hpp"
#include "wisco/io/IMotor.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros exp smart motor adapter for the wisco IMotor interface
 * @author Nathan Sandvig
 * 
 */
class ProsEXPMotor : public wisco::io::IMotor
{
private:
    /**
     * @brief The torque constant of the motor
     * 
     */
    static constexpr double TORQUE_CONSTANT{(0.5 / 18) / 2.5};

    /**
     * @brief The resistance of the motor
     * 
     */
    static constexpr double RESISTANCE{};

    /**
     * @brief The angular velocity constant of the motor
     * 
     */
    static constexpr double ANGULAR_VELOCITY_CONSTANT{};

    /**
     * @brief The internal gear ratio for the motor
     * 
     */
    static constexpr double GEAR_RATIO{18};

    /**
     * @brief Converts motor velocity to radians/second
     * 
     */
    static constexpr double VELOCITY_CONVERSION{2 * M_PI / 60};

    /**
     * @brief Converts input voltage to millivolts
     * 
     */
    static constexpr double VOLTAGE_CONVERSION{1000};

    /**
     * @brief The motor being adapted
     * 
     */
    std::unique_ptr<pros::Motor> m_motor{};

public:
    /**
     * @brief Construct a new Pros EXP Motor object
     * 
     * @param motor The motor being adapted
     */
    ProsEXPMotor(std::unique_ptr<pros::Motor>& motor);

    /**
     * @brief Initializes the motor
     * 
     */
    void initialize() override;

    /**
     * @brief Get the torque constant of the motor
     * 
     * @return double The torque constant of the motor
     */
    double getTorqueConstant() override;

    /**
     * @brief Get the resistance of the motor
     * 
     * @return double The resistance of the motor
     */
    double getResistance() override;

    /**
     * @brief Get the angular velocity constant of the motor
     * 
     * @return double The angular velocity constant of the motor
     */
    double getAngularVelocityConstant() override;

    /**
     * @brief Get the gear ratio of the motor (1 if n/a)
     * 
     * @return double The gear ratio of the motor
     */
    double getGearRatio() override;

    /**
     * @brief Get the angular velocity of the motor in radians/second
     * 
     * @return double The angular velocity of the motor in radians/second
     */
    double getAngularVelocity() override;

    /**
     * @brief Set the voltage input to the motor in Volts
     * 
     * @param volts The voltage input in Volts
     */
    void setVoltage(double volts) override;
};
} // namespace pros_adapters

#endif