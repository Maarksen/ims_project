#include "Tractor.hpp"
#include "TractorFacility.hpp"
#include <iostream>
#include "Shift.hpp"

using namespace std;

Tractor::Tractor(Priority_t priority, 
                 Shift *shift, 
                 Stat *statTractorDumpingTime, 
                 Stat *statTractorNumRuns,
                 int fullTractor
                 ):
                 Process(priority), 
                 shift(shift), 
                 statTractorDumpingDuration(statTractorDumpingDuration), 
                 statTractorNumRuns(statTractorNumRuns),
                 fullTractor(fullTractor)
{
    cout << "[" << Time << "]"
         << " aktivoval sa proces traktora (ide do skladu)" << endl;
}

void Tractor::Behavior()

{
    float start_time = Time;
    Seize (*shift->tractorFacilities[fullTractor]);

    cout << "[" << Time << "]"
         << " traktor " << fullTractor << " ziskal traktorovu facility"<< endl;
    // Seize(*shift->tractorFacilities[k]);

    cout << "TRAKTOR " <<  fullTractor<< " SYPE" << endl;

    long startedDumping = Time;

    // traktor ide do skladu
    Wait(Exponential(6));

    // traktor vysypa obilie
    Wait(Exponential(1.5));

    // tractor sa vracia naspat
    Wait(Exponential(6));
    shift->tractorFacilities[fullTractor]->capacity = 3;

    cout << "TRAKTOR " << fullTractor<< " VYSYPAL, trvalo mu to cele aj s cestou " << Time - start_time << endl;
    (*statTractorDumpingDuration) (Time - startedDumping);
    Release(*shift->tractorFacilities[fullTractor]);

    cout << "[" << Time << "]";
    cout << " traktor ide aktivovat dalsieho suhaja, queue len = " << shift->queue->Length() << "." << endl;
    cout << "traktorovaa queue: " << shift->queue << endl;
    if (shift->queue->Length() > 0)
    {
        cout << "[" << Time << "]"
             << "niekto vystupuje z queue" << endl;
        (shift->queue->GetFirst())->Activate();
    }
}

Tractor::~Tractor()
{
    // Destructor implementation
}
