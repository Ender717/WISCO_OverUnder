#ifndef I_HEADING_TRACKER_H
#define I_HEADING_TRACKER_H

namespace devices
{
/**
 * @brief An interface for devices that track heading in radians
 *
 * @author Nathan Sandvig
 */
class IHeadingTracker
{
public:
    /**
     * @brief Destroy the Heading Tracker object
     *
     */
    virtual ~IHeadingTracker() = default;

    /**
     * @brief Get the Heading
     *
     * @return double The heading
     */
    virtual double getHeading() = 0;
};
} // namespace devices

#endif