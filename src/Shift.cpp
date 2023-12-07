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

Shift::Shift(Harvest* harvest, Store* shifts, Queue *queue) : harvest(harvest), shifts(shifts), queue(queue) {


    this->combines = new Store("Combine store", harvest->num_combines);
    this->tractors = new Store("Tractor store", harvest->num_tractors);
    this->fieldSize = &harvest->field_size;
    this->queue = queue;



    TractorFacility **tractorFacilities = new TractorFacility*[harvest->num_tractors];
    this->tractorFacilities = tractorFacilities;

    // Create TractorFacility instances
    for (int i = 0; i < harvest->num_tractors; i++) {
    tractorFacilities[i] = new TractorFacility();
    }
    
}

void Shift::Behavior() {

    cout << "[" << Time << "]" << " Shift started" << endl;

    ShiftTimer *shift_timer = new ShiftTimer(this, *shifts);
    // TractorFacility *tractor = new TractorFacility();
    
    int comb_num = 0;
    Enter(*combines, harvest->num_combines);
    for(int i = 0; i < harvest->num_combines; i++){
            cout << "vytvaram combajn a fieldSize je:" << harvest->field_size << endl;
            (new Combine(comb_num++, this->combines, this))->Activate();
    }
    while(*fieldSize > 0){

         
         Enter(*combines, 1);
        // cout << "vytvaram combajn a fieldSize je:" << harvest->field_size << " shift fieldSize je" << *this->fieldSize << endl;
        if(*fieldSize == 0){
            break;
        }
        // cout << "vytvaram combajn a fieldSize je:" << harvest->field_size << endl;
        //for(int i = 0; i < harvest->num_combines; i++){
            cout << "vytvaram combajn a fieldSize je:" << harvest->field_size << endl;
            (new Combine(comb_num++, this->combines, this))->Activate();
        //}
        // Combine *combine1 = (new Combine(comb_num++, this->combines, this->fieldSize, tractor));
        // Combine *combine2 = (new Combine(comb_num++, this->combines, this->fieldSize, tractor));
        // combine1->Activate();       
        // combine2->Activate();       
        
        
    }
    Leave(*shifts, 1);
    cout << "[" << Time << "]" << " Harvest is done." << endl;
}

Shift::~Shift() {
    cout << "Shift destructor" << endl;
    // for (int i = 0; i < harvest->num_tractors; i++) {
    //     delete tractorFacilities[i];
    // }
    // delete[] tractorFacilities;
    // delete this->combines;
    // delete tractors;
}

