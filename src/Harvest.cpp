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
    num_combines = num_combine;
    num_tractors = num_tractor;

    this->shifts = new Store("Shift store", 1);
    
    //creating tractors
    // for (unsigned int i = 0; i < num_tractor; i++) {
        // (new Tractor)->Activate();
    // }
}

void Harvest::Behavior() {
    cout << "Harvest started." << endl;

     while(field_size > 0) {
        if(rand()/RAND_MAX < 0.9) {
            // (new Tractor)->Activate();
            cout << "field size: " << field_size << endl;

            Enter (*shifts, 1);

            (new Shift(this,this->shifts))->Activate();
        }
        else{
            Wait(24);
        }
     }
     Stop();

}

Harvest::~Harvest() {
    // Implementation of the destructor goes here
    std::cout << "Harvest class destructor\n";
}   