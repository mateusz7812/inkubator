#include "EepromManager.h"

EepromManager::EepromManager(Reporter *reporter)
{
    this->reporter = reporter;
}

bool EepromManager::is_address_valid(int address)
{
    return address >= 0 && address <= 200;
}

bool EepromManager::save(int value, int address)
{
    if (is_address_valid(address))
    {
        eeprom_write_block(&value, address, 2);
        return true;
    }
    return false;
}

int EepromManager::read(int address)
{
    if (is_address_valid(address))
    {
        int value = 0;
        eeprom_read_block(&value, address, 2);
        return value;
    }
    reporter->reportError("Address invalid");
}