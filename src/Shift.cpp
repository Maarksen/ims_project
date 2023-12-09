#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Shift.hpp"
#include "Combine.hpp"
#include "Harvest.hpp"
#include "ShiftTimer.hpp"
#include "TractorFacility.hpp"
#include "Tractor.hpp"

using namespace std;

Shift::Shift(Harvest* harvest,
             Store* shifts,
             Queue *queue, 
             Stat *statCombineNumRuns,
             Stat *statCombineHarvestDuration,
             Stat *statCombineWaitDuration,
             Stat *statTractorNumRuns,
             Stat *statQueueOcupancy,
             TractorFacility** tractorFacilities
             ): 
             harvest(harvest), 
             shifts(shifts),
             queue(queue),
             statCombineNumRuns(statCombineNumRuns),
             statCombineHarvestDuration(statCombineHarvestDuration),
             statCombineWaitDuration(statCombineWaitDuration),
             statTractorNumRuns(statTractorNumRuns),
             statQueueOcupancy(statQueueOcupancy),
             tractorFacilities(tractorFacilities)
{

    this->combines = new Store("Combine store", harvest->num_combines);
    this->tractors = new Store("Tractor store", harvest->num_tractors);
    this->fieldSize = harvest->fieldSize;

}

void Shift::Behavior() {

    new ShiftTimer(this, *shifts, harvest->shift_len);
    //queue->Clear();
    
    int comb_num = 0;
    Enter(*combines, harvest->num_combines);

    // creates combines
    for(int i = 0; i < (int)harvest->num_combines; i++){
            (new Combine(this,comb_num++, this->combines,
            statCombineNumRuns, statCombineHarvestDuration,
            statCombineWaitDuration,statTractorNumRuns,
            statQueueOcupancy))->Activate();
    }
    while(*fieldSize > 0){ 
         Enter(*combines, 1);
        if(*fieldSize == 0){
            break;
        }
        (new Combine( this,comb_num++, this->combines,
        statCombineNumRuns, statCombineHarvestDuration,
        statCombineWaitDuration,statTractorNumRuns, 
        statQueueOcupancy))->Activate();
    }
    
    Leave(*shifts, 1);
}

Shift::~Shift() {
}

