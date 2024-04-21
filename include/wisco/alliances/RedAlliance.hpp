#ifndef WISCO_ALLIANCES_RED_ALLIANCE
#define WISCO_ALLIANCES_RED_ALLIANCE

#include <string>

#include "wisco/IAlliance.hpp"

/**
 * @brief Namespace for all library code
 * @author Nathan Sandvig
 *
 */
namespace wisco
{
/**
 * @brief Namespace for all alliances
 * @author Nathan Sandvig
 * 
 */
namespace alliances
{

/**
 * @brief The red match alliance
 * @author Nathan Sandvig
 * 
 */
class RedAlliance : public IAlliance
{
private:
    /**
     * @brief The name of the alliance
     * 
     */
    static constexpr char ALLIANCE_NAME[]{"RED"};

    /**
     * @brief The object type name for triballs
     * 
     */
    static constexpr char TRIBALL_TYPE[]{"TRIBALL"};

    /**
     * @brief The triball vision object IDs
     * 
     */
    const std::vector<io::EVisionObjectID> TRIBALL_IDS
    {
        io::EVisionObjectID::GREEN_TRIBALL,
        io::EVisionObjectID::RED_TRIBALL
    };

public:
    /**
     * @brief Get the name of the alliance
     * 
     * @return std::string The name of the alliance
     */
    std::string getName() override;

    /**
	 * @brief Get the alliance-relevant vision object ids
	 * 
	 * @param object_type The type of object to get vision IDs for
	 * @return std::vector<io::EVisionObjectID> The vision object ids for that alliance
	 */
	std::vector<io::EVisionObjectID> getVisionObjectIDs(std::string object_type) override;
};
}
}

#endif