// Included headers
#include "devices/PistonGroup.h"

PistonGroup::PistonGroup()
{
    size = 0;
}

PistonGroup::PistonGroup(const PistonGroup& copy)
{
    for (int i = 0; i < copy.size; i++)
        pistons[i] = copy.pistons[i];
    size = copy.size;
}

void PistonGroup::add_piston(Piston& piston)
{
    mutex.take();
    if (size != MAX_SIZE)
        pistons[size++] = piston;
    mutex.give();
}

int PistonGroup::get_size()
{
    mutex.take();
    int result = size;
    mutex.give();
    return result;
}

uint8_t* PistonGroup::get_ports()
{
    static uint8_t ports[MAX_SIZE  + 1];
    mutex.take();
    for (int i = 0; i < MAX_SIZE; i++)
        ports[i] = pistons[i].get_port();
    mutex.give();
    ports[MAX_SIZE] = '\0';
    return ports;
}

void PistonGroup::toggle()
{
    mutex.take();
    for (int i = 0; i < size; i++)
        pistons[i].toggle();
    mutex.give();
}

bool PistonGroup::get_toggled()
{
    mutex.take();
    bool result = pistons[0].get_toggled();
    mutex.give();
    return result;
}

PistonGroup& PistonGroup::operator=(const PistonGroup& rhs)
{
    mutex.take();
    for (int i = 0; i < rhs.size; i++)
        pistons[i] = rhs.pistons[i];
    size = rhs.size;
    mutex.give();
    return *this;
}