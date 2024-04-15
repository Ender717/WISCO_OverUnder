#ifndef PROS_ADAPTERS_PROS_V5_MOTOR_HPP
#define PROS_ADAPTERS_PROS_V5_MOTOR_HPP

#include <cmath>
#include <map>
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
 * @brief Pros v5 smart motor adapter for the wisco IMotor interface
 * @author Nathan Sandvig
 * 
 */
class ProsV5Motor : public wisco::io::IMotor
{
private:
    /**
     * @brief Map from v5 motor cartridges to gear ratios
     * 
     */
    const std::map<pros::MotorGears, double> cartridge_map
    {
        {pros::MotorGears::rpm_100, 36.0},
        {pros::MotorGears::rpm_200, 18.0},
        {pros::MotorGears::rpm_600, 6.0}
    };

    /**
     * @brief The gear ratio if no cartridge is present
     * 
     */
    static constexpr double NO_CARTRIDGE{1.0};

    /**
     * @brief The torque constant of the motor
     * 
     */
    static constexpr double TORQUE_CONSTANT{(2.1 / 36) / 2.5};

    /**
     * @brief The resistance of the motor in ohms
     * 
     */
    static constexpr double RESISTANCE{3.2};

    /**
     * @brief The angular velocity constant of the motor
     * 
     */
    static constexpr double ANGULAR_VELOCITY_CONSTANT{2.1};

    /**
     * @brief Converts motor velocity to radians/second
     * 
     */
    static constexpr double VELOCITY_CONVERSION{2 * M_PI / 60};

    /**
     * @brief Converts motor position to radians
     * 
     */
    static constexpr double POSITION_CONVERSION{2 * M_PI / (900 / 18.0)};

    /**
     * @brief Converts input voltage to millivolts
     * 
     */
    static constexpr double VOLTAGE_CONVERSION{1000};

    /**
     * @brief The maximum output to the motor in millivolts
     * 
     */
    static constexpr int MAX_MILLIVOLTS{12000};

    /**
     * @brief The motor being adapted
     * 
     */
    std::unique_ptr<pros::Motor> m_motor{};

    /**
     * @brief The position offset
     * 
     */
    double position_offset{};

public:
    /**
     * @brief Construct a new Pros V5 Motor object
     * 
     * @param motor The motor being adapted
     */
    ProsV5Motor(std::unique_ptr<pros::Motor>& motor);

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
     * @brief Get the position of the motor in total radians
     * 
     * @return double The total number of radians moved since last reset
     */
    double getPosition() override;

    /**
     * @brief Set the voltage input to the motor in Volts
     * 
     * @param volts The voltage input in Volts
     */
    void setVoltage(double volts) override;

    /**
     * @brief Set the position of the motor in radians
     * 
     * @param position The position of the motor
     */
    void setPosition(double position) override;
};
} // namespace pros_adapters

#endif