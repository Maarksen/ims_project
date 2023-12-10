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
cout <<Time/60 <<  " shift tarted" << endl;
    Activate(Time + shiftLength);
}

void ShiftTimer::Behavior() {


cout <<Time/60 <<  " starting shift timer destructor" << endl;
cout << Time / 60 << " prepisal som isOver na true, mal by si vyskocit brasko" << endl;
shift->isOver = true;
    //shift->Terminate();
    //delete shift;	
cout <<Time/60 <<  " terminated shift" << endl;
    //Wait((( 60 * 24 )  - shiftLength));

cout <<Time/60 <<  " after waiting in the shiftimer destructor " << endl;

    //Leave(*shifts, 1);
cout <<Time/60 <<  " shift ended" << endl;
}
