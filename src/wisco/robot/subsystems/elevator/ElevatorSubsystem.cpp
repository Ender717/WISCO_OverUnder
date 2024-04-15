#include "wisco/robot/subsystems/elevator/ElevatorSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace elevator
{
ElevatorSubsystem::ElevatorSubsystem(std::unique_ptr<IElevator>& elevator, std::unique_ptr<io::IDistanceSensor>& distance_sensor) 
: ASubsystem{SUBSYSTEM_NAME}, m_elevator{std::move(elevator)}, m_distance_sensor{std::move(distance_sensor)}
{

}

void ElevatorSubsystem::initialize()
{
    if (m_elevator)
        m_elevator->initialize();
    if (m_distance_sensor)
        m_distance_sensor->initialize();
}

void ElevatorSubsystem::run()
{
    if (m_elevator)
        m_elevator->run();
}

void ElevatorSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == SET_POSITION_COMMAND_NAME)
    {
        double position{va_arg(args, double)};
        m_elevator->setPosition(position);
    }
    else if (command_name == CALIBRATE_COMMAND_NAME)
    {
        m_elevator->calibrate();
    }
}

void* ElevatorSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == GET_POSITION_STATE_NAME)
    {
        double* position{new double{m_elevator->getPosition()}};
        result = position;
    }
    else if (state_name == CAP_DISTANCE_STATE_NAME)
    {
        if (m_distance_sensor)
        {
            double* distance{new double{m_distance_sensor->getDistance()}};
            result = distance;
        }
    }
    else if (state_name == IS_CALIBRATING_STATE_NAME)
    {
        bool* calibrating{new bool{m_elevator->isCalibrating()}};
        result = calibrating;
    }

    return result;
}
} // namespace elevator
} // namespace subsystems
} // namespace robot
} // namespace wisco