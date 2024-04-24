#ifndef PROS_ADAPTERS_PROS_VISION_HPP
#define PROS_ADAPTERS_PROS_VISION_HPP

#include <cmath>
#include <map>
#include <memory>

#include "pros/vision.h"
#include "pros/vision.hpp"

#include "wisco/io/IVisionSensor.hpp"

/**
 * @brief Namespace for adapters from the pros library to the wisco library
 * @author Nathan Sandvig
 * 
 */
namespace pros_adapters
{

/**
 * @brief Pros vision sensor adapter for the wisco IVisionSensor interface
 * @author Nathan Sandvig
 * 
 */
class ProsVision : public wisco::io::IVisionSensor
{
private:
    /**
     * @brief The width of the vision sensor in pixels
     * 
     */
    static constexpr uint16_t PIXEL_WIDTH{316};

    /**
     * @brief The height of the vision sensor in pixels
     * 
     */
    static constexpr uint16_t PIXEL_HEIGHT{212};

    /**
     * @brief Conversion from pixels to radians
     * 
     */
    static constexpr double RADIANS_PER_PIXEL{61.0 / PIXEL_WIDTH * (M_PI / 180)};

    /**
     * @brief The object signature for blue triballs
     * 
     */
    static constexpr uint8_t BLUE_TRIBALL_SIGNATURE{1};

    /**
     * @brief The object signatures for green triballs
     * 
     */
    static constexpr uint8_t GREEN_TRIBALL_SIGNATURE{2};

    /**
     * @brief The object signatures for red triballs
     * 
     */
    static constexpr uint8_t RED_TRIBALL_SIGNATURE{3};

    /**
     * @brief The map from signatures to object ids
     * 
     */
    const std::map<uint8_t, wisco::io::EVisionObjectID> SIGNATURE_ID_MAP
    {
        {BLUE_TRIBALL_SIGNATURE, wisco::io::EVisionObjectID::BLUE_TRIBALL},
        {GREEN_TRIBALL_SIGNATURE, wisco::io::EVisionObjectID::GREEN_TRIBALL},
        {RED_TRIBALL_SIGNATURE, wisco::io::EVisionObjectID::RED_TRIBALL}
    };

    /**
     * @brief The sensor being adapted
     * 
     */
    std::unique_ptr<pros::Vision> m_sensor{};

public:
    /**
     * @brief Construct a new Pros Vision object
     * 
     * @param sensor The sensor being adapted
     * @param signatures The signatures for the vision sensor
     */
    ProsVision(std::unique_ptr<pros::Vision>& sensor, std::vector<pros::vision_signature_s_t>& signatures);

    /**
     * @brief Initializes the sensor
     * 
     */
    void initialize() override;

    /**
     * @brief Get the objects the vision sensor can see
     * 
     * @return std::vector<VisionObject> The objects the vision sensor can see
     */
    std::vector<wisco::io::VisionObject> getObjects() override;
};
} // namespace pros_adapters

#endif