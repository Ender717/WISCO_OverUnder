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
    const double m_kp{};

    /**
     * @brief The integral constant
     * 
     */
    const double m_ki{};

    /**
     * @brief The derivative constant
     * 
     */
    const double m_kd{};

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
     * @param clock The system clock
     * @param kp The proportional constant
     * @param ki The integral constant
     * @param kd The derivative constant
     */
    PID(std::unique_ptr<rtos::IClock>& clock, double kp, double ki, double kd);

    /**
     * @brief Get the control value output of the PID controller
     * 
     * @param current The current system value
     * @param target The target system value
     * @return double The output system value
     */
    double getControlValue(double current, double target);
};
} // namespace control
} // namespace wisco

#endif