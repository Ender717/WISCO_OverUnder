#ifndef HEADING_TRACKER_H
#define HEADING_TRACKER_H

namespace devices
{
    /**
     * @brief An interface for devices that track heading in radians
     *
     * @author Nathan Sandvig
     */
    class HeadingTracker
    {
    public:
        /**
         * @brief Destroy the Heading Tracker object
         *
         */
        virtual ~HeadingTracker() = default;

        /**
         * @brief Get the Heading
         *
         * @return double The heading
         */
        virtual double getHeading() = 0;
    };
} // namespace devices

#endif