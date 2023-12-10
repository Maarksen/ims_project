#include <iostream>

#include "Harvest.hpp"
#include "Combine.hpp"
#include "TractorFacility.hpp"
#include "ShiftTimer.hpp"
#include "Shift.hpp"

using namespace std;

Harvest::Harvest(unsigned long num_combine, unsigned int num_tractor, 
                 float FIELD_SIZE, float *fieldSize, unsigned int  shift_length,
                 TractorFacility **tractorFacilities,
                 Stat *statCombineNumRuns,
                 Stat *statCombineHarvestDuration,
                 Stat *statCombineWaitDuration,
                 Stat *statTractorNumRuns,
                 Stat *statWhetaherRecord,
                 Stat *statQueueOcupancy
                 ): 
                fieldSize(fieldSize),
                tractorFacilities(tractorFacilities),
                statCombineNumRuns(statCombineNumRuns),
                statCombineHarvestDuration(statCombineHarvestDuration),
                statCombineWaitDuration(statCombineWaitDuration),
                statTractorNumRuns(statTractorNumRuns),
                statWhetaherRecord(statWhetaherRecord),
                statQueueOcupancy(statQueueOcupancy)
{

    harvested_size = 0;
    field_size = FIELD_SIZE;
    beginningFieldSize = field_size;
    num_combines = num_combine;
    num_tractors = num_tractor;
    shift_len = shift_length;
    this->shifts = new Store("Shift store", 1);
}

void Harvest::Behavior()
{
    while (*fieldSize > 0){

        Enter(*shifts, 1);
        (new Shift(this, this->shifts,
                    new Queue(),
                    statCombineNumRuns,
                    statCombineHarvestDuration,
                    statCombineWaitDuration,
                    statTractorNumRuns,
                    statQueueOcupancy,
                    tractorFacilities, statWhetaherRecord))
            ->Activate();
    }
    Stop();
}

Harvest::~Harvest()
{
}