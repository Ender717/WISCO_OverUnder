#ifndef WISCO_IO_I_PISTON_HPP
#define WISCO_IO_I_PISTON_HPP

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
 * @brief Interface for a discrete state-based piston
 * @author Nathan Sandvig
 * 
 */
class IPiston
{
public:
    /**
     * @brief Destroy the IPiston object
     * 
     */
    virtual ~IPiston() = default;

    /**
     * @brief Extends the piston
     * 
     */
    virtual void extend() = 0;

    /**
     * @brief Retracts the piston
     * 
     */
    virtual void retract() = 0;

    /**
     * @brief Toggles the piston state
     * 
     */
    virtual void toggle() = 0;

    /**
     * @brief Checks if the piston is extended
     * 
     * @return true The piston is extended
     * @return false The piston is not extended
     */
    virtual bool isExtended() = 0;

    /**
     * @brief Checks if the piston is retracted
     * 
     * @return true The piston is retracted
     * @return false The piston is not retracted
     */
    virtual bool isRetracted() = 0;
};
} // namespace io
} // namespace wisco

#endif