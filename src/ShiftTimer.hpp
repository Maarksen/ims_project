#ifndef SHIFT_TIMER_HPP
#define SHIFT_TIMER_HPP

#include <simlib.h>
#include <stdbool.h>

#include "Shift.hpp"

class ShiftTimer : public Process {
    public:
        ShiftTimer( Shift* shift, Store *shifts);

        void Behavior() override;

        bool isShift; 


    private:

    const double shiftTime = 12 * 60;

    Shift *shift;
    Store *shifts;
};

#endif // SHIFT_TIMER_HPP