#include "wisco/user/elevator/ElevatorOperator.hpp"

namespace wisco
{
namespace user
{
namespace elevator
{
ElevatorOperator::ElevatorOperator(const std::shared_ptr<user::IController>& controller, 
                                   const std::shared_ptr<robot::Robot>& robot)
    : m_controller{controller}, m_robot{robot}
{

}

double ElevatorOperator::getElevatorPosition()
{
    double position{};
    if (m_robot)
    {
        double* result{static_cast<double*>(m_robot->getState(ELEVATOR_SUBSYSTEM_NAME, GET_POSITION_STATE))};
        if (result)
        {
            position = *result;
            delete result;
        }
    }
    return position;
}

double ElevatorOperator::getCapDistance()
{
    double distance{};
    if (m_robot)
    {
        double* result{static_cast<double*>(m_robot->getState(ELEVATOR_SUBSYSTEM_NAME, CAP_DISTANCE_STATE_NAME))};
        if (result)
        {
            distance = *result;
            delete result;
        }
    }
    return distance;
}

bool ElevatorOperator::getHangArmUp()
{
    bool arm_up{};
    if (m_robot)
    {
        bool* result{static_cast<bool*>(m_robot->getState(HANG_SUBSYSTEM_NAME, HANG_ARM_UP_STATE_NAME))};
        if (result)
        {
            arm_up = *result;
            delete result;
        }
    }
    return arm_up;
}

void ElevatorOperator::updateElevatorPosition(double position)
{
    m_robot->sendCommand(ELEVATOR_SUBSYSTEM_NAME, SET_POSITION_COMMAND, position);
}

void ElevatorOperator::updatePoleHangPosition()
{
    if (getHangArmUp())
    {
        double distance{getCapDistance()};
        if (distance != 0 && distance < CAP_DETECTED_DISTANCE)
        {
            double position{getElevatorPosition()};
            updateElevatorPosition(position - (distance - POLE_HANG_DISTANCE));
        }
    }
}

void ElevatorOperator::updateManual(EControllerDigital in, EControllerDigital out)
{
    bool move_in{m_controller->getDigital(in)};
    bool move_out{m_controller->getDigital(out)};
    if (move_in && move_out)
    {
        updateElevatorPosition(getElevatorPosition());
        manual_input = true;
    }
    else if (move_in)
    {
        updateElevatorPosition(IN_POSITION);
        manual_input = true;
    }
    else if (move_out)
    {
        updateElevatorPosition(PARTNER_HANG_POSITION);
        manual_input = true;
    }
    else if (manual_input)
    {
        updateElevatorPosition(getElevatorPosition());
        manual_input = false;
    }
}

void ElevatorOperator::updatePresetSplit(EControllerDigital in, EControllerDigital field, EControllerDigital match_load, EControllerDigital pole_hang, EControllerDigital partner_hang)
{
    bool move_in{m_controller->getNewDigital(in)};
    bool move_field{m_controller->getNewDigital(field)};
    bool move_match_load{m_controller->getNewDigital(match_load)};
    bool move_pole_hang{m_controller->getNewDigital(pole_hang)};
    bool move_partner_hang{m_controller->getNewDigital(partner_hang)};

    if (move_in && !move_field && !move_match_load && !move_pole_hang && !move_partner_hang)
        updateElevatorPosition(IN_POSITION);
    else if (!move_in && move_field && !move_match_load && !move_pole_hang && !move_partner_hang)
        updateElevatorPosition(FIELD_POSITION);
    else if (!move_in && !move_field && move_match_load && !move_pole_hang && !move_partner_hang)
        updateElevatorPosition(MATCH_LOAD_POSITION);
    else if (!move_in && !move_field && !move_match_load && move_pole_hang && !move_partner_hang)
        updateElevatorPosition(POLE_HANG_POSITION);
    else if (!move_in && !move_field && !move_match_load && !move_pole_hang && move_partner_hang)
        updateElevatorPosition(PARTNER_HANG_POSITION);
}

void ElevatorOperator::updatePresetToggle(EControllerDigital toggle)
{
    if (m_controller->getNewDigital(toggle))
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            updateElevatorPosition(FIELD_POSITION);
            toggle_state = EToggleState::FIELD;
            break;
        case EToggleState::FIELD:
            updateElevatorPosition(MATCH_LOAD_POSITION);
            toggle_state = EToggleState::MATCH_LOAD;
            break;
        case EToggleState::MATCH_LOAD:
            updateElevatorPosition(POLE_HANG_POSITION);
            toggle_state = EToggleState::POLE_HANG;
            break;
        case EToggleState::POLE_HANG:
            updateElevatorPosition(PARTNER_HANG_POSITION);
            toggle_state = EToggleState::PARTNER_HANG;
            break;
        case EToggleState::PARTNER_HANG:
            updateElevatorPosition(IN_POSITION);
            toggle_state = EToggleState::IN;
            break;
        }
    }
}

void ElevatorOperator::updatePresetLadder(EControllerDigital in, EControllerDigital out)
{
    bool move_in{m_controller->getNewDigital(in)};
    bool move_out{m_controller->getNewDigital(out)};

    if (move_in && !move_out)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            break;
        case EToggleState::FIELD:
            updateElevatorPosition(IN_POSITION);
            toggle_state = EToggleState::IN;
            break;
        case EToggleState::MATCH_LOAD:
            updateElevatorPosition(FIELD_POSITION);
            toggle_state = EToggleState::FIELD;
            break;
        case EToggleState::POLE_HANG:
            updateElevatorPosition(MATCH_LOAD_POSITION);
            toggle_state = EToggleState::MATCH_LOAD;
        case EToggleState::PARTNER_HANG:
            updateElevatorPosition(POLE_HANG_POSITION);
            toggle_state = EToggleState::POLE_HANG;
            break;
        }
    }
    else if (!move_in && move_out)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            updateElevatorPosition(FIELD_POSITION);
            toggle_state = EToggleState::FIELD;
            break;
        case EToggleState::FIELD:
            updateElevatorPosition(MATCH_LOAD_POSITION);
            toggle_state = EToggleState::MATCH_LOAD;
            break;
        case EToggleState::MATCH_LOAD:
            updateElevatorPosition(POLE_HANG_POSITION);
            toggle_state = EToggleState::POLE_HANG;
            break;
        case EToggleState::POLE_HANG:
            updateElevatorPosition(PARTNER_HANG_POSITION);
            toggle_state = EToggleState::PARTNER_HANG;
            break;
        case EToggleState::PARTNER_HANG:
            break;
        }
    }
}

void ElevatorOperator::updatePresetLadderIntake(EControllerDigital in, EControllerDigital out, EControllerDigital intake, EControllerDigital outtake)
{
    bool move_in{m_controller->getNewDigital(in)};
    bool move_out{m_controller->getNewDigital(out)};
    bool move_intake{m_controller->getNewDigital(intake)};
    bool move_outtake{m_controller->getNewDigital(outtake)};

    if (move_intake && toggle_state == EToggleState::IN)
    {
        updateElevatorPosition(FIELD_POSITION);
        toggle_state = EToggleState::FIELD;
    }
    else if (move_outtake && toggle_state == EToggleState::FIELD)
    {
        updateElevatorPosition(IN_POSITION);
        toggle_state = EToggleState::IN;
    }
    else if (move_in && !move_out)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            break;
        case EToggleState::FIELD:
            updateElevatorPosition(IN_POSITION);
            toggle_state = EToggleState::IN;
            break;
        case EToggleState::MATCH_LOAD:
            updateElevatorPosition(FIELD_POSITION);
            toggle_state = EToggleState::FIELD;
            break;
        case EToggleState::POLE_HANG:
            updateElevatorPosition(MATCH_LOAD_POSITION);
            toggle_state = EToggleState::MATCH_LOAD;
            break;
        case EToggleState::PARTNER_HANG:
            updateElevatorPosition(POLE_HANG_POSITION);
            toggle_state = EToggleState::POLE_HANG;
            break;
        }
    }
    else if (!move_in && move_out)
    {
        switch (toggle_state)
        {
        case EToggleState::IN:
            updateElevatorPosition(FIELD_POSITION);
            toggle_state = EToggleState::FIELD;
            break;
        case EToggleState::FIELD:
            updateElevatorPosition(MATCH_LOAD_POSITION);
            toggle_state = EToggleState::MATCH_LOAD;
            break;
        case EToggleState::MATCH_LOAD:
            updateElevatorPosition(POLE_HANG_POSITION);
            toggle_state = EToggleState::POLE_HANG;
            break;
        case EToggleState::POLE_HANG:
            updateElevatorPosition(PARTNER_HANG_POSITION);
            toggle_state = EToggleState::PARTNER_HANG;
            break;
        case EToggleState::PARTNER_HANG:
            break;
        }
    }
}

void ElevatorOperator::setElevatorPosition(const std::unique_ptr<IProfile>& profile)
{
    EControllerDigital in{profile->getDigitalControlMapping(EControl::ELEVATOR_IN)};
    EControllerDigital field{profile->getDigitalControlMapping(EControl::ELEVATOR_FIELD)};
    EControllerDigital match_load{profile->getDigitalControlMapping(EControl::ELEVATOR_MATCH_LOAD)};
    EControllerDigital pole_hang{profile->getDigitalControlMapping(EControl::ELEVATOR_POLE_HANG)};
    EControllerDigital partner_hang{profile->getDigitalControlMapping(EControl::ELEVATOR_PARTNER_HANG)};
    EControllerDigital out{profile->getDigitalControlMapping(EControl::ELEVATOR_OUT)};
    EControllerDigital toggle{profile->getDigitalControlMapping(EControl::ELEVATOR_TOGGLE)};
    EControllerDigital intake{profile->getDigitalControlMapping(EControl::INTAKE_IN)};
    EControllerDigital outtake{profile->getDigitalControlMapping(EControl::INTAKE_OUT)};

    switch (static_cast<EElevatorControlMode>(profile->getControlMode(EControlType::ELEVATOR)))
    {
    case EElevatorControlMode::MANUAL:
        updateManual(in, out);
        break;
    case EElevatorControlMode::PRESET_SPLIT:
        updatePresetSplit(in, field, match_load, pole_hang, partner_hang);
        break;
    case EElevatorControlMode::PRESET_TOGGLE_LADDER:
        updatePresetLadder(in, out);
        break;
    case EElevatorControlMode::PRESET_TOGGLE_SINGLE:
        updatePresetToggle(toggle);
        break;
    case EElevatorControlMode::PRESET_TOGGLE_LADDER_INTAKE:
        updatePresetLadderIntake(in, out, intake, outtake);
        break;
    }

    if (toggle_state == EToggleState::POLE_HANG)
        updatePoleHangPosition();
}
} // namespace elevator
} // namespace user
} // namespace wisco