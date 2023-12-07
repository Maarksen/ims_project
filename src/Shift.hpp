#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <simlib.h>  
#include "Harvest.hpp"
#include "Tractor.hpp"

class Harvest;

class Shift : public Process {
public:
    Shift(Harvest *harvest, Store *shifts, Queue *queue);

    void Behavior() override;

    ~Shift() override;

    TractorFacility **tractorFacilities;
    Queue *queue;
    Store *combines;
    Store *tractors;
    Harvest *harvest;
    Store *shifts;
    float *fieldSize;

private:
};

#endif // SHIFT_HPP
