#ifndef WISCO_CONTROL_PID_HPP
#define WISCO_CONTROL_PID_HPP

#include <memory>

#include "wisco/rtos/IClock.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Namespace for control algorithms
 * @author Nathan Sandvig
 * 
 */
namespace control
{

/**
 * @brief A general-purpose PID controller
 * @author Nathan Sandvig
 * 
 */
class PID
{
private:
    /**
     * @brief The system clock
     * 
     */
    std::unique_ptr<rtos::IClock> m_clock{};

    /**
     * @brief The proportional constant
     * 
     */
    double m_kp{};

    /**
     * @brief The integral constant
     * 
     */
    double m_ki{};

    /**
     * @brief The derivative constant
     * 
     */
    double m_kd{};

    /**
     * @brief The accumulated error
     * 
     */
    double accumulated_error{};

    /**
     * @brief The error during the last timestep
     * 
     */
    double last_error{};

    /**
     * @brief The system clock time during the last timestep
     * 
     */
    double last_time{};

public:
    /**
     * @brief Construct a new PID object
     * 
     */
    PID() = default;

    /**
     * @brief Construct a new PID object
     * 
     * @param clock The system clock
     * @param kp The proportional constant
     * @param ki The integral constant
     * @param kd The derivative constant
     */
    PID(const std::unique_ptr<rtos::IClock>& clock, double kp, double ki, double kd);

    /**
     * @brief Construct a new PID object
     * 
     * @param copy The PID object being copied
     */
    PID(const PID& copy);

    /**
     * @brief Construct a new PID object
     * 
     * @param move The PID object being moved
     */
    PID(PID&& move) = default;

    /**
     * @brief Get the control value output of the PID controller
     * 
     * @param current The current system value
     * @param target The target system value
     * @return double The output system value
     */
    double getControlValue(double current, double target);

    /**
     * @brief Resets the PID controller
     * 
     */
    void reset();

    /**
     * @brief Copy assignment operator
     * 
     * @param rhs The PID object being copied
     * @return PID& This PID object with the assigned values
     */
    PID& operator=(const PID& rhs);

    /**
     * @brief Move assignment operator
     * 
     * @param rhs The PID object being moved
     * @return PID& This PID object with the assigned values
     */
    PID& operator=(PID&& rhs) = default;
};
} // namespace control
} // namespace wisco

#endif