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
class IPositionTracker
{
public:
    /**
     * @brief Destroy the Position Tracker object
     *
     */
    virtual ~IPositionTracker() = default;

    /**
     * @brief Get the Position
     *
     * @return Position The position
     */
    virtual Position getPosition() = 0;

    /**
     * @brief Set the Position
     *
     * @param position The new position
     */
    virtual void setPosition(Position position) = 0;
};
} // namespace position
} // namespace drive
} // namespace subsystems

#endif