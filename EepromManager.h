#include <avr/eeprom.h>
#include "Reporter.h"
#include "AbstractDataManager.h"

class EepromManager : public AbstractDataManager
{
private:
    Reporter *reporter;
    bool is_address_valid(int address);

public:
    EepromManager(Reporter *reporter);
    bool save(int value, int address) override;
    int read(int address) override;
};