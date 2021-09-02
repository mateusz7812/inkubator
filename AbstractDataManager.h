#ifndef DATA_MANAGER

#define DATA_MANAGER

class AbstractDataManager
{
public:
    virtual bool save(int value, int address) = 0;
    virtual int read(int address) = 0;
};

#endif