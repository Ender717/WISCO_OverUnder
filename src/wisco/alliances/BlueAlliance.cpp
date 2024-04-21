#include "wisco/alliances/BlueAlliance.hpp"

namespace wisco
{
namespace alliances
{
std::string BlueAlliance::getName()
{
    return ALLIANCE_NAME;
}

std::vector<io::EVisionObjectID> BlueAlliance::getVisionObjectIDs(std::string object_type)
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