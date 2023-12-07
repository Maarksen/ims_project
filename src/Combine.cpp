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
                 Stat *TractorDumpingDuration,
                 Stat *TractorNumRuns
                 ):
                 shift(shift), 
                 num(num), 
                 combines(combines), 
                 statCombineNumRuns(statCombineNumRuns),
                 statCombineHarvestDuration(CombineHarvestDuration),
                 statCombineWaitDuration(CombineWaitDuration),
                 statTractorDumpingDuration(TractorDumpingDuration),
                 statTractorNumRuns(TractorNumRuns)
{
    cout << "Combine is created." << endl;
    this->fieldSize = shift->fieldSize;
}

void Combine::Behavior()
{
    //number of combine runs in total in one shift
    (*statCombineNumRuns)(1);
    int number = num;
    float harvestTime = Normal(24,6);

   //storing the time when the combine started harvesting
    long startedHarvest = Time;

    //duration of harvesting
    Wait(harvestTime);

    //storing the stat of harvesting duration
    (*statCombineHarvestDuration)(Time - startedHarvest);

    //storiing the time when the combine started waiting for the tractor
    long startedWaiting = Time;


    //if the field is smaller than then capacity of one harvest, we set the 
    //remaining field size to 0
    if (*fieldSize < 0.055)
    {
        *fieldSize = 0;
    }
    else
    {
        *fieldSize -= 0.055; 
    }

    cout << "[" << Time << "]";


    int k = -1;
back:

    for (int i = 0; i < 2; i++)
    {
        if (!shift->tractorFacilities[i]->Busy())
        {
            cout << "ja, kombajn " << num <<" som nasiel som volny vo for loope s cislom " << i <<", a ma kapacitu   -> " << shift->tractorFacilities[i]->capacity << endl;
            k = i;
            break;
        }
    }
    if (k == -1)
    {
        Into(shift->queue);
        Passivate();
        goto back;
    }

    //storing the stat of waiting for the tractor
    (*statCombineWaitDuration)(Time - startedWaiting);
    Seize(*shift->tractorFacilities[k]);

 
    cout << "[" << Time << "]"
         << "kombajn[" << number << "] ziskal traktor cislo  " << k << " s kapacitou " << shift->tractorFacilities[k]->capacity << endl;

    //dumping the grain out of the tractor  (90sec)
    shift->tractorFacilities[k]->capacity -= 1;
    Wait(1.5);

    // ak je traktor full, spustame proces vysypania do skladu
    if (shift->tractorFacilities[k]->capacity == 0)
    {
        // cout << "[" << Time << "]" << "Traktor je fullka, vysielam ho do skladu(nikto nevie seiznut traktor medzi tymto a TRAKTOR SYPE)" << endl;
        // cout << "toto je qyueueu" << this->queue->Length() << endl;
        cout <<Time<<"kombajn "<< num << "posiela traktor " << k << " na vandrovku" << endl;
        (new Tractor(1,this->shift, statTractorDumpingDuration, statTractorNumRuns, k))->Activate();
    }
    

    // cout << "[" << Time << "]" << "kombajn[" <<number << "]releasuje trakokot, traktor capa:" << tractors[k]->capacity << endl;
    cout << "[" << Time << "]"
         << "kombajn cislo " << number << " opusta traktor cislo " << k << endl;
    Release(*shift->tractorFacilities[k]);

    if (shift->queue->Length() > 0)
    {
        // cout << "toto sa vzdy predtym ako niekto seizuje traktor musi vypisat do pice. " << endl;
        cout << "niekto vystupuje z queue" << endl;
        (shift->queue->GetFirst())->Activate();
    }
    // }
    // cout << "[" << Time << "]" << "releasing the tractor. Combine was waiting for " << Time - waiting_time << endl;

    Leave(*combines, 1);
}

Combine::~Combine()
{
}