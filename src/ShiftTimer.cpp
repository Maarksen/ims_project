#include <iostream>
#include <stdlib.h>
#include "ShiftTimer.hpp"

using namespace std;

ShiftTimer::ShiftTimer(Shift *shift, Store *shifts): shift(shift), shifts(shifts) {
    cout << "["<< Time << "] ShifTimer started" << endl;
    Activate(Time + shiftTime);
}

void ShiftTimer::Behavior() {
    cout << "["<< Time << "] Shift ended" << endl;

    delete shift;
    Wait(12 * 60);
    Leave(*shifts, 1);
}