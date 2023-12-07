#include "Tractor.hpp"
#include "TractorFacility.hpp"
#include <iostream>
#include "Shift.hpp"




using namespace std;

Tractor::Tractor(Shift *shift, Priority_t priority)
    : shift(shift), Process(priority)  {
    cout << "[" << Time << "]"
         << " aktivoval sa proces traktora (ide do skladu)" << endl;
}

void Tractor::Behavior() {
    float start_time = Time;
    int k = -1;
back:
    for (int i = 0; i < 2; i++) {
        if (!shift->tractorFacilities[i]->Busy()) {
            k = i;
            break;
        }
    }

    if (k == -1) {
        Into(shift->queue);
        Passivate();
        goto back;
    }

    Seize(*shift->tractorFacilities[k]);

    cout << "TRAKTOR " << k << " SYPE" << endl;

    // traktor ide do skladu
    Wait(Exponential(6));

    // traktor vysypa obilie
    Wait(Exponential(1.5));

    // tractor sa vracia naspat
    Wait(Exponential(6));
    shift->tractorFacilities[k]->capacity = 3;

    cout << "TRAKTOR " << k << " VYSYPAL, trvalo mu to cele aj s cestou " << Time - start_time << endl;
    Release(*shift->tractorFacilities[k]);

    cout << "[" << Time << "]";
    cout  << " traktor ide aktivovat dalsieho suhaja, queue len = " << shift->queue->Length() << "." << endl;
    if (shift->queue->Length() > 0) {
        cout << "[" << Time << "]"
             << " traktor aktivoval dalsieho suhaja" << endl;
        shift->queue->GetFirst()->Activate();
    }
}

Tractor::~Tractor() {
    // Destructor implementation
}
