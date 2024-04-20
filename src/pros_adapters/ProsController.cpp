#include "pros_adapters/ProsController.hpp"

namespace pros_adapters
{
ProsController::ProsController(std::unique_ptr<pros::Controller>& controller) : m_controller{std::move(controller)}
{

}

void ProsController::taskLoop(void* params)
{
    ProsController* controller{static_cast<ProsController*>(params)};

    while (true)
    {
        controller->taskUpdate();
        pros::delay(TASK_DELAY);
    }
}

void ProsController::updateRumble()
{
    uint32_t time{pros::millis()};
    if (new_rumble_pattern && time - last_rumble_refresh >= RUMBLE_REFRESH_RATE)
    {
        if (m_controller)
            m_controller->rumble(rumble_pattern);
        new_rumble_pattern = false;
        last_rumble_refresh = time;
    }
}

void ProsController::taskUpdate()
{
    mutex.take();
    updateRumble();
    mutex.give();
}

void ProsController::initialize()
{

}

void ProsController::run()
{
    pros::Task controller_task{&ProsController::taskLoop, this};
}

double ProsController::getAnalog(wisco::user::EControllerAnalog analog_channel)
{
    double value{};
    if (ANALOG_MAP.contains(analog_channel))
        if (m_controller)
            value = m_controller->get_analog(ANALOG_MAP.at(analog_channel)) * ANALOG_CONVERSION;
    return value;
}

bool ProsController::getDigital(wisco::user::EControllerDigital digital_channel)
{
    bool value{};
    if (DIGITAL_MAP.contains(digital_channel))
        if (m_controller)
            value = m_controller->get_digital(DIGITAL_MAP.at(digital_channel));
    return value;
}

bool ProsController::getNewDigital(wisco::user::EControllerDigital digital_channel)
{
    bool value{};
    if (DIGITAL_MAP.contains(digital_channel))
        if (m_controller)
            value = m_controller->get_digital_new_press(DIGITAL_MAP.at(digital_channel));
    return value;
}

void ProsController::rumble(std::string pattern)
{
    mutex.take();
    for (uint8_t i{0}; i < MAX_RUMBLE_LENGTH; ++i)
        rumble_pattern[i] = pattern[i];
    new_rumble_pattern = true;
    mutex.give();
}
} // namespace pros_adapters