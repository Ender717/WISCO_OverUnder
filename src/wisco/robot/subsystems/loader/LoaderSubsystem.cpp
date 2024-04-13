#include "wisco/robot/subsystems/loader/LoaderSubsystem.hpp"

namespace wisco
{
namespace robot
{
namespace subsystems
{
namespace loader
{
LoaderSubsystem::LoaderSubsystem(std::unique_ptr<ILoader>& loader)
    : ASubsystem{SUBSYSTEM_NAME}, m_loader{std::move(loader)}
{

}

void LoaderSubsystem::initialize()
{
    if (m_loader)
        m_loader->initialize();
}

void LoaderSubsystem::run()
{
    if (m_loader)
        m_loader->run();
}

void LoaderSubsystem::command(std::string command_name, va_list& args)
{
    if (command_name == DO_LOAD_COMMAND_NAME)
    {
        m_loader->doLoad();
    }
    else if (command_name == DO_READY_COMMAND_NAME)
    {
        m_loader->doReady();
    }
}

void* LoaderSubsystem::state(std::string state_name)
{
    void* result{nullptr};

    if (state_name == IS_LOADED_STATE_NAME)
    {
        bool* loaded{new bool{m_loader->isLoaded()}};
        result = loaded;
    }
    else if (state_name == IS_READY_STATE_NAME)
    {
        bool* ready{new bool{m_loader->isReady()}};
        result = ready;
    }

    return result;
}
} // namespace loader
} // namespace subsystems
} // namespace robot
} // namespace wisco