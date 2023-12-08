#include <iostream>

#include "Harvest.hpp"
#include "Combine.hpp"
#include "TractorFacility.hpp"
#include "ShiftTimer.hpp"
#include "Shift.hpp"

using namespace std;

Harvest::Harvest(unsigned long num_combine, unsigned int num_tractor, float FIELD_SIZE,
                 Stat *statCombineNumRuns,
                 Stat *statCombineHarvestDuration,
                 Stat *statCombineWaitDuration,
                 Stat *statTractorDumpingDuration,
                 Stat *statTractorNumRuns,
                 Stat *statWhetaherRecord,
                 Stat *statQueueOcupancy
                 ): 
                statCombineNumRuns(statCombineNumRuns),
                statCombineHarvestDuration(statCombineHarvestDuration),
                statCombineWaitDuration(statCombineWaitDuration),
                statTractorDumpingDuration(statTractorDumpingDuration),
                statTractorNumRuns(statTractorNumRuns),
                statWhetaherRecord(statWhetaherRecord),
                statQueueOcupancy(statQueueOcupancy)
{

    harvested_size = 0;
    field_size = (float)FIELD_SIZE;
    beginningFieldSize = (float)FIELD_SIZE;
    num_combines = num_combine;
    num_tractors = num_tractor;
    this->shifts = new Store("Shift store", 1);


}

void Harvest::Behavior()
{
    while (field_size > 0)
    {
        if ((double)rand() / RAND_MAX < 0.9)
        {

            (*statWhetaherRecord)(+0);

            Enter(*shifts, 1);

            (new Shift(this, this->shifts,
                       new Queue(),
                       statCombineNumRuns,
                       statCombineHarvestDuration,
                       statCombineWaitDuration,
                       statTractorDumpingDuration,
                       statTractorNumRuns,
                       statQueueOcupancy))
                ->Activate();
        }
        else
        {
            (*statWhetaherRecord)(24);
            Wait(24);
        }
    }
    Stop();
}

Harvest::~Harvest()
{
    delete shifts;
}