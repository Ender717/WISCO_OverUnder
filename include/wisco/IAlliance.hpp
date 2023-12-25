#ifndef WISCO_I_ALLIANCE_HPP
#define WISCO_I_ALLIANCE_HPP

#include <string>

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{

/**
 * @brief Interface for the alliances for the robot
 * @author Nathan Sandvig
 *
 */
class IAlliance
{
public:
	/**
	 * @brief Destroy the IAlliance object
	 *
	 */
	virtual ~IAlliance() = default;

	/**
	 * @brief Get the name of the alliance
	 *
	 * @return std::string The name of the alliance
	 */
	virtual std::string getName() = 0;
};
} // namespace wisco

#endif