#ifndef COMBINE_HPP
#define COMBINE_HPP

#include "TractorFacility.hpp"

#include <simlib.h>
#include "Shift.hpp"
#include "Tractor.hpp"
 class Shift;

class Combine : public Process {
public:
    Combine(int num, Store *combines, Shift *shift);

    void Behavior() override;

    ~Combine() override;

    Shift *shift;

private:
    int num;
    Store *combines;
    float *fieldSize;
};

#endif // COMBINE_HPP