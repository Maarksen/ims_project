#include <iostream>
#include <stdlib.h>
#include "ShiftTimer.hpp"

using namespace std;

ShiftTimer::ShiftTimer(Shift *shift, 
                       Store *shifts, 
                       unsigned int shiftLength
                       ): 
                       shift(shift), 
                       shifts(shifts), 
                       shiftLength(shiftLength)
{
    Activate(Time + shiftLength);
}

void ShiftTimer::Behavior() {


shift->isOver = true;
    //shift->Terminate();
    //delete shift;	
    //Wait((( 60 * 24 )  - shiftLength));


    //Leave(*shifts, 1);
}
