#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_TOGGLE_ARM_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_TOGGLE_ARM_HPP

#include "wisco/hal/PistonGroup.hpp"

#include "IToggleArm.hpp"

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
 * @brief Interface for arms with an up and down position
 * @author Nathan Sandvig
 * 
 */
class PistonToggleArm : public IToggleArm
{
private:
    /**
     * @brief The pistons on the arm
     * 
     */
    hal::PistonGroup m_pistons{};

    /**
     * @brief The state of the pistons when the arm is up
     * 
     */
    bool m_up_state{};

public:
    /**
     * @brief Initializes the arm
     * 
     */
    void initialize() override;

    /**
     * @brief Runs the arm
     * 
     */
    void run() override;

    /**
     * @brief Sets the arm to the down position
     * 
     */
    void setDown() override;

    /**
     * @brief Sets the arm to the up position
     * 
     */
    void setUp() override;

    /**
     * @brief Checks if the arm is in the down position
     * 
     * @return true The arm is in the down position
     * @return false The arm is not in the down position
     */
    bool isDown() override;

    /**
     * @brief Checks if the arm is in the up position
     * 
     * @return true The arm is in the up position
     * @return false The arm is not in the up position
     */
    bool isUp() override;

    /**
     * @brief Sets the pistons for the arm
     * 
     * @param pistons The pistons for the arm
     */
    void setPistons(hal::PistonGroup& pistons);

    /**
     * @brief Sets the state of the pistons when the arm is up
     * 
     * @param up_state The state of the pistons when the arm is up
     */
    void setUpState(bool up_state);
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif