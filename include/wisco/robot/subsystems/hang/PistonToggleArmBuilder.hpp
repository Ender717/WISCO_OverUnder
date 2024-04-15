#ifndef WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_TOGGLE_ARM_BUILDER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_HANG_PISTON_TOGGLE_ARM_BUILDER_HPP

#include "PistonToggleArm.hpp"
#include "wisco/io/IPiston.hpp"

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
class PistonToggleArmBuilder
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
     * @brief Adds a piston to the build
     * 
     * @param piston The piston
     * @return This object for build chaining
     */
    PistonToggleArmBuilder* withPiston(std::unique_ptr<io::IPiston>& piston);

    /**
     * @brief Adds an up state to the build
     * 
     * @param up_state The state of the pistons when the arm is up
     * @return This object for build chaining
     */
    PistonToggleArmBuilder* withUpState(bool up_state);

    /**
     * @brief Builds a piston toggle arm
     * 
     * @return std::unique_ptr<IToggleArm> The piston toggle arm as a toggle arm interface object
     */
    std::unique_ptr<IToggleArm> build();
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif