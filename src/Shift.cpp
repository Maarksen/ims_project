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
             TractorFacility** tractorFacilities,
             Stat *statWhetaherRecord
             ): 
             harvest(harvest), 
             shifts(shifts),
             queue(queue),
             statCombineNumRuns(statCombineNumRuns),
             statCombineHarvestDuration(statCombineHarvestDuration),
             statCombineWaitDuration(statCombineWaitDuration),
             statTractorNumRuns(statTractorNumRuns),
             statQueueOcupancy(statQueueOcupancy),
             tractorFacilities(tractorFacilities),
             statWhetaherRecord(statWhetaherRecord)
{

    this->combines = new Store("Combine store", harvest->num_combines);
    this->tractors = new Store("Tractor store", harvest->num_tractors);
    this->isOver = false;
    this->fieldSize = harvest->fieldSize;

}

void Shift::Behavior() {
	cout << Time/60 << " zacina shifta " << endl;

    new ShiftTimer(this, *shifts, harvest->shift_len);
    queue->Clear();
    
    if ((double)rand() / RAND_MAX < 0.9){
	cout << Time/60 << " field size je" <<  *fieldSize<< " a neprsi" << endl;
    int comb_num = 0;
    Enter(*combines, harvest->num_combines);

    // creates combines
    for(int i = 0; i < (int)harvest->num_combines; i++){
            (new Combine(this,comb_num++, this->combines,
            statCombineNumRuns, statCombineHarvestDuration,
            statCombineWaitDuration,statTractorNumRuns,
            statQueueOcupancy))->Activate();
    }

    while(*fieldSize > 0){//  && !this->isOver){ 
if (this->isOver){
	break;
}

         Enter(*combines, 1);
        if(*fieldSize == 0 ){// || isOver){
            break;
        }
if (!this->isOver){
        (new Combine( this,comb_num++, this->combines,
        statCombineNumRuns, statCombineHarvestDuration,
        statCombineWaitDuration,statTractorNumRuns, 
        statQueueOcupancy))->Activate();
}
    }
    }
    else{
Wait(1);
         (*statWhetaherRecord)(1);
	Wait((24*60) - harvest->shift_len); 

        
}  
	Wait((24*60) - harvest->shift_len); 
	
    Leave(*shifts, 1); 
}

Shift::~Shift() {
cout << " shift destroyed" << endl;
}

