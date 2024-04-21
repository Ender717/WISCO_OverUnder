#include "wisco/alliances/SkillsAlliance.hpp"

namespace wisco
{
namespace alliances
{
std::string SkillsAlliance::getName()
{
    return ALLIANCE_NAME;
}

std::vector<io::EVisionObjectID> SkillsAlliance::getVisionObjectIDs(std::string object_type)
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