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
class RedAlliance : public IAlliance
{
private:
    /**
     * @brief The name of the alliance
     * 
     */
    static constexpr char ALLIANCE_NAME[]{"RED"};

public:
    /**
     * @brief Get the name of the alliance
     * 
     * @return std::string The name of the alliance
     */
    std::string getName() override;
};
}
}

#endif