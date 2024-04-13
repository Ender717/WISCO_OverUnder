#ifndef WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_I_UMBRELLA_HPP
#define WISCO_ROBOT_SUBSYSTEMS_UMBRELLA_I_UMBRELLA_HPP

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
 * @brief Namespace for umbrella classes
 * @author Nathan Sandvig
 * 
 */
namespace umbrella
{

/**
 * @brief Interface for umbrellas with an out and in position
 * @author Nathan Sandvig
 * 
 */
class IUmbrella
{
public:
    /**
     * @brief Destroy the IUmbrella object
     * 
     */
    virtual ~IUmbrella() = default;

    /**
     * @brief Initializes the umbrella
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the umbrella
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Sets the umbrella to the in position
     * 
     */
    virtual void setIn() = 0;

    /**
     * @brief Sets the umbrella to the out position
     * 
     */
    virtual void setOut() = 0;

    /**
     * @brief Checks if the umbrella is in
     * 
     * @return true The umbrella is in
     * @return false The umbrella is not in
     */
    virtual bool isIn() = 0;

    /**
     * @brief Checks if the umbrella is out
     * 
     * @return true The umbrella is out
     * @return false The umbrella is not out
     */
    virtual bool isOut() = 0;
};
} // namespace hang
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif