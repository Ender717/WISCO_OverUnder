#include "pros_adapters/ProsVision.hpp"
#include "wisco/io/EVisionObjectID.hpp"

namespace pros_adapters
{
ProsVision::ProsVision(std::unique_ptr<pros::Vision>& sensor)
    : m_sensor{std::move(sensor)}
{

}

void ProsVision::initialize()
{
    static pros::vision_signature_s_t blue_triball_signature
    {
        pros::c::vision_signature_from_utility
        (BLUE_TRIBALL_SIGNATURE, -3665, -2917, -3292, 4135, 10193, 7164, 2.000, 0)
    };
    static pros::vision_signature_s_t green_triball_signature
    {
        pros::c::vision_signature_from_utility
        (GREEN_TRIBALL_SIGNATURE, -5845, -4809, -5328, -5495, -4151, -4822, 3.100, 0)
    };
    static pros::vision_signature_s_t red_triball_signature
    {
        pros::c::vision_signature_from_utility
        (RED_TRIBALL_SIGNATURE, 6481, 9637, 8060, -1387, -463, -924, 2.000, 0)
    };
    if (m_sensor)
    {
        m_sensor->set_signature(BLUE_TRIBALL_SIGNATURE, &blue_triball_signature);
        m_sensor->set_signature(GREEN_TRIBALL_SIGNATURE, &green_triball_signature);
        m_sensor->set_signature(RED_TRIBALL_SIGNATURE, &red_triball_signature);
    }
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