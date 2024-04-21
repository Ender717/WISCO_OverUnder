#include "wisco/alliances/RedAlliance.hpp"

namespace wisco
{
namespace alliances
{
std::string RedAlliance::getName()
{
    return ALLIANCE_NAME;
}

std::vector<io::EVisionObjectID> RedAlliance::getVisionObjectIDs(std::string object_type)
{
    std::vector<io::EVisionObjectID> object_ids{};

    if (object_type == TRIBALL_TYPE)
    {
        object_ids = TRIBALL_IDS;
    }

    return object_ids;
}
}
}