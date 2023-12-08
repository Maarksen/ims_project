#ifndef SHIFT_TIMER_HPP
#define SHIFT_TIMER_HPP

#include <stdbool.h>
#include <simlib.h>

#include "Shift.hpp"

class ShiftTimer : public Process {
    public:
        ShiftTimer( Shift* shift, Store *shifts, unsigned int shiftLength);

        void Behavior() override;

        bool isShift; 
        
    private:

    Shift *shift;
    Store *shifts;
    unsigned int shiftLength;
};

#endif // SHIFT_TIMER_HPP