#ifndef WISCO_HAL_PISTON_GROUP_HPP
#define WISCO_HAL_PISTON_GROUP_HPP

#include <memory>
#include <vector>

#include "wisco/io/IPiston.hpp"

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
 * @brief A group of pistons on the same connected output
 * @author Nathan Sandvig
 * 
 */
class PistonGroup
{
private:
    /**
     * @brief The pistons in the group
     * 
     */
    std::vector<std::unique_ptr<io::IPiston>> pistons{};

    /**
     * @brief The state of the piston group
     * 
     */
    bool m_state{};

public:
    /**
     * @brief Adds a piston to the piston group
     * 
     * @param piston The piston being added to the group
     */
    void addPiston(std::unique_ptr<io::IPiston>& piston);

    /**
     * @brief Sets the state of the pistons
     * 
     * @param state The state of the pistons
     */
    void setState(bool state);

    /**
     * @brief Gets the state of the pistons
     * 
     * @return true The pistons are active
     * @return false The pistons are not active
     */
    bool getState();

    /**
     * @brief Override for the assignment operator for PistonGroup
     * 
     * @param rhs The PistonGroup object on the right hand side of the operator
     * @return PistonGroup& This PistonGroup object with the assigned values
     */
    PistonGroup& operator=(PistonGroup& rhs);
};
} // namespace hal
} // namespace wisco

#endif