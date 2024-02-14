#include "pros_adapters/ProsTask.hpp"

namespace pros_adapters
{
void ProsTask::start(void (*function)(void*), void* parameters)
{
    task = std::make_unique<pros::Task>(function, parameters);
}

void ProsTask::remove()
{
    task->remove();
}

void ProsTask::suspend()
{
    task->suspend();
}

void ProsTask::resume()
{
    task->resume();
}

void ProsTask::join()
{
    task->join();
}
} // namespace pros_adapters