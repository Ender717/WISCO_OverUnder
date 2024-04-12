#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_WINCH_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_WINCH_HPP

#include "wisco/hal/PistonGroup.hpp"

#include "IWinch.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief The namespace that holds all robot classes
 * @author Nathan Sandvig
 *
 */
namespace robot
{

/**
 * @brief Namespace for all robot subsystems
 * @author Nathan Sandvig
 * 
 */
namespace subsystems
{

/**
 * @brief Namespace for hang classes
 * @author Nathan Sandvig
 * 
 */
namespace hang
{

/**
 * @brief A winch controlled using a piston
 * @author Nathan Sandvig
 * 
 */
class PistonWinch : public IWinch
{
private:
    /**
     * @brief The pistons for the claw
     * 
     */
    hal::PistonGroup m_pistons{};

    /**
     * @brief The state of the piston group when the winch is engaged
     * 
     */
    bool m_engaged_state{};

public:
    /**
     * @brief Initializes the winch
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the winch
     * 
     */
    void run() override;

    /**
     * @brief Engages the winch
     * 
     */
    void engage() override;

    /**
     * @brief Disengages the winch
     * 
     */
    void disengage() override;

    /**
     * @brief Checks if the winch is engaged
     * 
     * @return true The winch is engaged
     * @return false The winch is not engaged
     */
    bool isEngaged() override;

    /**
     * @brief Checks if the winch is disengaged
     * 
     * @return true The winch is disengaged
     * @return false The winch is not disengaged
     */
    bool isDisengaged() override;

    /**
     * @brief Sets the pistons for the winch
     * 
     * @param pistons The pistons for the winch
     */
    void setPistons(hal::PistonGroup& pistons);

    /**
     * @brief Sets the state of the pistons when the winch is engaged
     * 
     * @param engaged_state The state of the pistons when the winch is engaged
     */
    void setEngagedState(bool engaged_state);
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif