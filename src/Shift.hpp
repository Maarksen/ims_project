#ifndef SHIFT_HPP
#define SHIFT_HPP

#include "Harvest.hpp"

#include <simlib.h>

class Shift : public Process {
public:
    // Constructor
    Shift(Harvest* harvest, Store *shifts);

    // Behavior function
    void Behavior() override;

    Store *shifts;

    float *fieldSize;



private:
    Harvest* harvest; 

    Store *combines;

    Store *tractors;

    static const unsigned long SHIFT_TIME = 12;
};

#endif // SHIFT_HPP
