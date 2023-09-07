#ifndef RTOS_A_TASK_HPP
#define RTOS_A_TASK_HPP

#include <memory>

#include "pros/rtos.hpp"

#include "IDelay.hpp"

namespace rtos
{
/**
 * @brief Abstract parent class for tasks
 *
 * @author Nathan Sandvig
 */
class ATask
{
private:
    static constexpr uint32_t DEFAULT_DELAY{10};
    std::shared_ptr<IDelay> delayHandler{nullptr};
    uint32_t delay{DEFAULT_DELAY};
    bool active{false};
    bool running{false};

public:

};
} // namespace rtos

#endif