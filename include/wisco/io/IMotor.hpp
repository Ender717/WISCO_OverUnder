#ifndef WISCO_IO_I_MOTOR_HPP
#define WISCO_IO_I_MOTOR_HPP

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for the io types
 * @author Nathan Sandvig
 * 
 */
namespace io
{

/**
 * @brief Interface for electric motors controlled by voltage
 * @author Nathan Sandvig
 * 
 */
class IMotor
{
public:
    /**
     * @brief Destroy the IMotor object
     * 
     */
    virtual ~IMotor() = default;

    /**
     * @brief Initializes the motor
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Get the torque constant of the motor
     * 
     * @return double The torque constant of the motor
     */
    virtual double getTorqueConstant() = 0;

    /**
     * @brief Get the resistance of the motor
     * 
     * @return double The resistance of the motor
     */
    virtual double getResistance() = 0;

    /**
     * @brief Get the angular velocity constant of the motor
     * 
     * @return double The angular velocity constant of the motor
     */
    virtual double getAngularVelocityConstant() = 0;

    /**
     * @brief Get the gear ratio of the motor (1 if n/a)
     * 
     * @return double The gear ratio of the motor
     */
    virtual double getGearRatio() = 0;

    /**
     * @brief Get the angular velocity of the motor in radians/second
     * 
     * @return double The angular velocity of the motor in radians/second
     */
    virtual double getAngularVelocity() = 0;

    /**
     * @brief Get the position of the motor in total radians
     * 
     * @return double The total number of radians moved since last reset
     */
    virtual double getPosition() = 0;

    /**
     * @brief Set the voltage input to the motor in Volts
     * 
     * @param volts The voltage input in Volts
     */
    virtual void setVoltage(double volts) = 0;

    /**
     * @brief Set the position of the motor in radians
     * 
     * @param position The position of the motor
     */
    virtual void setPosition(double position) = 0;
};
}
}

#endif