#include "Tractor.hpp"
#include "TractorFacility.hpp"
#include <iostream>
#include "Shift.hpp"

using namespace std;

Tractor::Tractor(Priority_t priority, 
                 Shift *shift, 
                 Stat *statTractorNumRuns,
                 int fullTractor
                 ):
                 Process(priority), 
                 shift(shift), 
                 statTractorNumRuns(statTractorNumRuns),
                 fullTractor(fullTractor)
{
}

void Tractor::Behavior()

{
    Seize (*shift->tractorFacilities[fullTractor]);
    cout << "seizol som tractor " << fullTractor<< endl;

    // tractor goes to the storage
    Wait(Exponential(6));

    // stractor is dumping the grain
    Wait(Exponential(1.5));

    // tractor is going back to the field
    Wait(Exponential(6));
    shift->tractorFacilities[fullTractor]->capacity = 3;;

    // storing the stats
    // (*statTractorNumRuns)(1);
    cout <<" release facility cislo"<< fullTractor << endl;
    Release(*shift->tractorFacilities[fullTractor]);

    // if the queue is not empty, activate the first combine in the queue
    if (shift->queue->Length() > 0)
    {
        (shift->queue->GetFirst())->Activate();
    }
}

Tractor::~Tractor()
{
}
