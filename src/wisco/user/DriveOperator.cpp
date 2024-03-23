#include "wisco/user/DriveOperator.hpp"

namespace wisco
{
namespace user
{
void DriveOperator::updateDriveVoltage(double left_voltage, double right_voltage)
{
    if (m_robot)
    {
        m_robot->sendCommand(m_drive_name, SET_VOLTAGE_COMMAND, left_voltage, right_voltage);
    }
}

void DriveOperator::updateArcade(double forward, double turn)
{
    double left_voltage{(forward + turn) * VOLTAGE_CONVERSION};
    double right_voltage{(forward - turn) * VOLTAGE_CONVERSION};
    updateDriveVoltage(left_voltage, right_voltage);
}

void DriveOperator::updateSingleArcadeLeft()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_X)};
    updateArcade(forward, turn);
}

void DriveOperator::updateSingleArcadeRight()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_X)};
    updateArcade(forward, turn);
}

void DriveOperator::updateSplitArcadeLeft()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_X)};
    updateArcade(forward, turn);
}

void DriveOperator::updateSplitArcadeRight()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_X)};
    updateArcade(forward, turn);
}

void DriveOperator::updateTank()
{
    double left_voltage{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y) * VOLTAGE_CONVERSION};
    double right_voltage{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y) * VOLTAGE_CONVERSION};
}

DriveOperator::DriveOperator(const std::shared_ptr<user::IController>& controller, 
                  const std::shared_ptr<robot::Robot>& robot,
                  std::string drive_name) :
                  m_controller{controller}, m_robot{robot}, m_drive_name{drive_name}
{

}

void DriveOperator::setDriveVoltage(EChassisControlMode control_mode)
{
    if (!m_controller)
    {
        updateDriveVoltage(0, 0);
        return;
    }

    switch (control_mode)
    {
        case EChassisControlMode::SINGLE_ARCADE_LEFT:
            updateSingleArcadeLeft();
            break;
        case EChassisControlMode::SINGLE_ARCADE_RIGHT:
            updateSingleArcadeRight();
            break;
        case EChassisControlMode::SPLIT_ARCADE_LEFT:
            updateSplitArcadeLeft();
            break;
        case EChassisControlMode::SPLIT_ARCADE_RIGHT:
            updateSplitArcadeRight();
            break;
        case EChassisControlMode::TANK:
            updateTank();
            break;
    }
}
} // namespace user
} // namespace wisco