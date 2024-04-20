#include "pros_adapters/ProsTask.hpp"

namespace pros_adapters
{
void ProsTask::start(void (*function)(void*), void* parameters)
{
    task = std::make_unique<pros::Task>(function, parameters);
}

void ProsTask::remove()
{
    if (task)
        task->remove();
}

void ProsTask::suspend()
{
    if (task)
        task->suspend();
}

void ProsTask::resume()
{
    if (task)
        task->resume();
}

void ProsTask::join()
{
    if (task)
        task->join();
}
} // namespace pros_adapters