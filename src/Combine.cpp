#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Combine.hpp"
#include "TractorFacility.hpp"

using namespace std;

Combine::Combine(Shift *shift,
                 int num, 
                 Store *combines,
                 Stat *statCombineNumRuns, 
                 Stat *CombineHarvestDuration,
                 Stat *CombineWaitDuration,
                 Stat *TractorNumRuns,
                 Stat *statQueueOcupancy
                 ):
                 shift(shift), 
                 num(num), 
                 combines(combines), 
                 statCombineNumRuns(statCombineNumRuns),
                 statCombineHarvestDuration(CombineHarvestDuration),
                 statCombineWaitDuration(CombineWaitDuration),
                 statTractorNumRuns(TractorNumRuns),
                 statQueueOcupancy(statQueueOcupancy)
{
    this->fieldSize = shift->fieldSize;
}

void Combine::Behavior()
{
    // number of combine runs in total in one shift
    (*statCombineNumRuns)(1);
    float harvestTime = Normal(24,4);

   // storing the time when the combine started harvesting
    long startedHarvest = Time;

    // duration of harvesting
    Wait(harvestTime);

    // storing the stat of harvesting duration
    (*statCombineHarvestDuration)(Time - startedHarvest);

    // storiing the time when the combine started waiting for the tractor
    long startedWaiting = Time;


    // if the field is smaller than then capacity of one harvest, we set the 
    // remaining field size to 0
    if (*fieldSize < 0.021)
    {
        *fieldSize = 0;
    }
    else
    {
        *fieldSize -= 0.021; 
    }

    int k = -1;
back:

    // checking if there is a free tractor
    for (unsigned int i = 0; i < shift->harvest->num_tractors; i++)
    {
        if (!shift->tractorFacilities[i]->Busy())
        {
            k = i;
            break;
        }
    }
    // if there is no free tractor, combine goes to the queue
    if (k == -1)
    {
        Into(shift->queue);
        Passivate();
        goto back;
    }

    // storing the stat of waiting for the tractor
    (*statCombineWaitDuration)(Time - startedWaiting);
    Seize(*shift->tractorFacilities[k]);
    
    // dumping the grain out of the tractor  (90sec)
    shift->tractorFacilities[k]->capacity -= 1;
    Wait(1.5);

    // if the tractor is full, it goes to the storage to dump the grain
    if (shift->tractorFacilities[k]->capacity == 0)
    {
        (new Tractor(1,this->shift, statTractorNumRuns, k))->Activate();
    }
    Release(*shift->tractorFacilities[k]);

    // activating the next combine in the queue if queue is non-empty
    if (shift->queue->Length() > 0)
    {
        (shift->queue->GetFirst())->Activate();
    }

    Leave(*combines, 1);
}

Combine::~Combine()
{
}