#ifndef POSITION_TRACKER_H
#define POSITION_TRACKER_H

#include "Position.h"

namespace subsystems
{
    namespace drive
    {
        namespace position
        {
            /**
             * @brief An interface for classes which track position
             *
             * @author Nathan Sandvig
             */
            class PositionTracker
            {
            public:
                /**
                 * @brief Destroy the Position Tracker object
                 *
                 */
                virtual ~PositionTracker() = default;

                /**
                 * @brief Get the Position
                 *
                 * @return Position The position
                 */
                virtual Position getPosition() = 0;
            };
        } // namespace position
    } // namespace drive
} // namespace subsystems

#endif