#include <iostream>
#include <stdlib.h>
#include "ShiftTimer.hpp"

using namespace std;

ShiftTimer::ShiftTimer(Shift *shift, Store *shifts): shift(shift), shifts(shifts) {
    Activate(Time + shiftTime);
}

void ShiftTimer::Behavior() {
    this->isShift = false;
    cout << "["<< Time << "] Shift ended" << endl;
    delete shift;
    Wait(12 * 60);
    Leave(*shifts, 1);
}