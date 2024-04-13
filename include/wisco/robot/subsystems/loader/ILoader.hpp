#ifndef WISCO_ROBOT_SUBSYSTEMS_LOADER_I_LOADER_HPP
#define WISCO_ROBOT_SUBSYSTEMS_LOADER_I_LOADER_HPP

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
 * @brief Namespace for all loader subsystem classes
 * @author Nathan Sandvig
 * 
 */
namespace loader
{

/**
 * @brief Interface for loader subsystems
 * @author Nathan Sandvig
 * 
 */
class ILoader
{
public:
    /**
     * @brief Destroy the ILoader object
     * 
     */
    virtual ~ILoader() = default;

    /**
     * @brief Initializes the loader
     * 
     */
    virtual void initialize() = 0;

    /**
     * @brief Runs the loader
     * 
     */
    virtual void run() = 0;

    /**
     * @brief Does one match load
     * 
     */
    virtual void doLoad() = 0;

    /**
     * @brief Gets the system ready for another match load
     * 
     */
    virtual void doReady() = 0;

    /**
     * @brief Checks if the match load is loaded
     * 
     * @return true The match load is loaded
     * @return false The match load is not loaded
     */
    virtual bool isLoaded() = 0;

    /**
     * @brief Checks if the loader is ready
     * 
     * @return true The loader is ready
     * @return false The loader is not ready
     */
    virtual bool isReady() = 0;
};
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco

#endif