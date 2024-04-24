#include "pros_adapters/ProsVision.hpp"

namespace pros_adapters
{
ProsVision::ProsVision(std::unique_ptr<pros::Vision>& sensor, std::vector<pros::vision_signature_s_t>& signatures)
    : m_sensor{std::move(sensor)}
{
    if (m_sensor)
    {
        for (auto& signature : signatures)
        {
            m_sensor->set_signature(signature.id, &signature);
        }
    }
}

void ProsVision::initialize()
{
    
}

std::vector<wisco::io::VisionObject> ProsVision::getObjects()
{
    std::vector<wisco::io::VisionObject> objects{};

    if (m_sensor)
    {
        int32_t object_count{m_sensor->get_object_count()};
        for (uint8_t i{}; i < object_count; ++i)
        {
            pros::vision_object_s_t vision_object{m_sensor->get_by_size(i)};
            wisco::io::EVisionObjectID object_id{wisco::io::EVisionObjectID::UNKNOWN};
            if (SIGNATURE_ID_MAP.contains(vision_object.signature))
                object_id = SIGNATURE_ID_MAP.at(vision_object.signature);
            double horizontal{((PIXEL_WIDTH / 2.0) - vision_object.x_middle_coord) * RADIANS_PER_PIXEL};
            double vertical{((PIXEL_HEIGHT / 2.0) - vision_object.y_middle_coord) * RADIANS_PER_PIXEL};
            double width{vision_object.width * RADIANS_PER_PIXEL};
            double height{vision_object.height * RADIANS_PER_PIXEL};
            wisco::io::VisionObject object{object_id, horizontal, vertical, width, height};
            objects.push_back(object);
        }
    }
    return objects;
}
} // namespace pros_adapters