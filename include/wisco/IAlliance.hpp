#ifndef WISCO_I_ALLIANCE_HPP
#define WISCO_I_ALLIANCE_HPP

#include <string>
#include <vector>

#include "wisco/io/EVisionObjectID.hpp"

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

	/**
	 * @brief Get the alliance-relevant vision object ids
	 * 
	 * @param object_type The type of object to get vision IDs for
	 * @return std::vector<io::EVisionObjectID> The vision object ids for that alliance
	 */
	virtual std::vector<io::EVisionObjectID> getVisionObjectIDs(std::string object_type) = 0;
};
} // namespace wisco

#endif