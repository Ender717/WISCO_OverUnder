#include "wisco/user/drive/DifferentialDriveOperator.hpp"

namespace wisco
{
namespace user
{
namespace drive
{
void DifferentialDriveOperator::updateDriveVoltage(double left_voltage, double right_voltage)
{
    if (m_robot)
    {
        m_robot->sendCommand(DIFFERENTIAL_DRIVE_SUBSYSTEM_NAME, SET_VOLTAGE_COMMAND, left_voltage, right_voltage);
    }
}

void DifferentialDriveOperator::updateArcade(double forward, double turn)
{
    double left_voltage{(forward + turn) * VOLTAGE_CONVERSION};
    double right_voltage{(forward - turn) * VOLTAGE_CONVERSION};
    updateDriveVoltage(left_voltage, right_voltage);
}

void DifferentialDriveOperator::updateSingleArcadeLeft()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_X)};
    updateArcade(forward, turn);
}

void DifferentialDriveOperator::updateSingleArcadeRight()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_X)};
    updateArcade(forward, turn);
}

void DifferentialDriveOperator::updateSplitArcadeLeft()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_X)};
    updateArcade(forward, turn);
}

void DifferentialDriveOperator::updateSplitArcadeRight()
{
    double forward{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y)};
    double turn{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_X)};
    updateArcade(forward, turn);
}

void DifferentialDriveOperator::updateTank()
{
    double left_voltage{m_controller->getAnalog(EControllerAnalog::JOYSTICK_LEFT_Y) * VOLTAGE_CONVERSION};
    double right_voltage{m_controller->getAnalog(EControllerAnalog::JOYSTICK_RIGHT_Y) * VOLTAGE_CONVERSION};
    updateDriveVoltage(left_voltage, right_voltage);
}

DifferentialDriveOperator::DifferentialDriveOperator(const std::shared_ptr<user::IController>& controller, 
                                                     const std::shared_ptr<robot::Robot>& robot) 
    : m_controller{controller}, m_robot{robot}
{

}

void DifferentialDriveOperator::setDriveVoltage(EChassisControlMode control_mode)
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
} // namespace drive
} // namespace user
} // namespace wisco