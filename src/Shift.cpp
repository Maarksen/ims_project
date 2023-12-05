#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "Shift.hpp"
#include "Combine.hpp"
#include "Harvest.hpp"
#include "ShiftTimer.hpp"

using namespace std;

Shift::Shift(Harvest* harvest, Store* shifts) : harvest(harvest), shifts(shifts) {


    this->combines = new Store("Combine store", harvest->num_combines);
    this->tractors = new Store("Tractor store", harvest->num_tractors);
    this->fieldSize = &harvest->field_size;
    
}

void Shift::Behavior() {

    cout << "[" << Time << "]" << " Shift started" << endl;

    ShiftTimer *shift_timer = new ShiftTimer(this, *shifts);
    while(harvest->field_size > 0){

        if(harvest->field_size == 0){
            cout << "[" << Time << "]" << " Harvest is done." << endl;
            break;
        }
        cout << "[" << Time << "]" << "este som spustil zmenu" << endl;
        Enter(*combines, 1);
        Combine *combine = (new Combine(this->combines, this->fieldSize));
        combine->Activate();       
    }
    // Leave(*combines, 1);
    cout << "[" << Time << "]" << " Harvest is done." << endl;
}

