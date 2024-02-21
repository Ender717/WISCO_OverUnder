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
     * @brief The different cartridges and their gear ratios
     * @author Nathan Sandvig
     * 
     */
    enum class Cartridge : uint8_t
    {
        V5_100 = 36,
        V5_200 = 18,
        V5_600 = 6,
        NO_CARTRIDGE = 1
    };

    const std::map<pros::MotorGears, Cartridge> cartridge_map
    {
        {pros::MotorGears::rpm_100, Cartridge::V5_100},
        {pros::MotorGears::rpm_200, Cartridge::V5_200},
        {pros::MotorGears::rpm_600, Cartridge::V5_600}
    };

    /**
     * @brief The torque constant of the motor
     * 
     */
    static constexpr double TORQUE_CONSTANT{0.35 / 2.5};

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
     * @brief Set the voltage input to the motor in Volts
     * 
     * @param volts The voltage input in Volts
     */
    void setVoltage(double volts) override;
};
} // namespace pros_adapters

#endif