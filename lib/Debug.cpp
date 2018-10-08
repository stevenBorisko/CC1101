#include "CC1100.hpp"

uint8_t CC1100::set_debug_level(uint8_t set_debug_level = 1)  //default ON
{
    debug_level = set_debug_level;        //set debug level of CC1101 outputs

    return debug_level;
}

uint8_t CC1100::get_debug_level(void)
{
    return debug_level;
}
