#include <iostream>

#include "Harvest.hpp"
#include "Combine.hpp"
#include "TractorFacility.hpp"
#include "ShiftTimer.hpp"
#include "Shift.hpp"

using namespace std;

Harvest::Harvest(unsigned long num_combine, unsigned int num_tractor , float FIELD_SIZE) {
    harvested_size = 0;
    field_size = (float) FIELD_SIZE;
    beginningFieldSize = (float) FIELD_SIZE;
    num_combines = num_combine;
    num_tractors = num_tractor;
    this->shifts = new Store("Shift store", 1);

    //STATISTIKY

    //kombajn
    statCombineNumRuns = new Stat("Combine number of runs");
    statCombineHarvestDuration = new Stat("Combine harvest duration");
    statCombineWaitDuration = new Stat("Combine wait duration");

    //traktor
    statTractorDumpingDuration = new Stat("Tractor dumping time");
    statTractorNumRuns = new Stat("Tractor number of runs");

    statWhetaherRecord = new Stat("Weather record");
}

void Harvest::Behavior() {
    cout << "Harvest started." << endl;

     while(field_size > 0) {
        if( (double)rand() / RAND_MAX < 0.9) {
            // (new Tractor)->Activate();
            cout << "field size: " << field_size << endl;
            (*statWhetaherRecord)(+0);

            Enter (*shifts, 1);

            (new Shift(this,this->shifts, 
                       new Queue(), 
                       statCombineNumRuns, 
                       statCombineHarvestDuration, 
                       statCombineWaitDuration, 
                       statTractorDumpingDuration,
                       statTractorNumRuns))->Activate();
        }
        else{
            cout << "["<< Time << "]" <<" cakam 24 hod lebo je zle pocasie" << endl;
            (*statWhetaherRecord)(24);
            Wait(24);
        }
     }
     SIMLIB_statistics.Output();
     statCombineHarvestDuration->Output();
     statCombineWaitDuration->Output();
     statTractorNumRuns->Output();
     statTractorDumpingDuration->Output();
     statWhetaherRecord->Output();
     cout << "success rate:" << beginningFieldSize - field_size  / beginningFieldSize << "%" << endl;
     cout <<"===================================================="<< endl;
     Stop();

}

Harvest::~Harvest() {
    // Implementation of the destructor goes here
    std::cout << "Harvest class destructor\n";
    delete shifts;

}   