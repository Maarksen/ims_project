#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Combine.hpp"
#include "TractorFacility.hpp"
#include "Tractor.hpp"

using namespace std;

Combine::Combine(int num, Store *combines, float *fieldSize, TractorFacility *tractors) : num(num), combines(combines) , fieldSize(fieldSize) , tractors(tractors){
    //cout << "Combine is created." << endl;
}

void Combine::Behavior() {
    long time_started = Time;
    int number = num;
    Wait(Normal(24,6));
    if (*fieldSize < 0.055) {
        *fieldSize = 0;
    }
    else{  
        *fieldSize -= (0.055); //* harvest_time/60;
    }

    cout << "[" << Time << "]";
    cout << " Combine " << number << " was harvesting for " << Time - time_started << " minutes."<< *fieldSize << " km left in the field." << endl;
    
    // cout << "capacity of the tractor before dumping :" << tractors->capacity <<  endl;
    long waiting_time = Time;

    //kombajn sa snazi ziskat traktor
    // if(number_tractors != 0){
    Seize(*tractors);
    cout << "[" << Time << "]" << "kombajn["<< number <<"] ziskal traktor" << endl;
    //vysypu sa
    tractors->capacity -= 1;
    Wait(1.5);

    //ak je traktor full, spustame proces vysypania do skladu
    if (tractors->capacity == 0){
        cout << "[" << Time << "]" << "Traktor je fullka, vysielam ho do skladu" << endl;
        Tractor *tractor = (new Tractor(tractors)); 
        tractor->Activate();
    }
    cout << "[" << Time << "]" << "kombajn[" <<number << "]releasuje trakokot, traktor capa:" << tractors->capacity << endl;
    Release(*tractors);
    // }
    //cout << "[" << Time << "]" << "releasing the tractor. Combine was waiting for " << Time - waiting_time << endl;

    Leave(*combines, 1);
}

Combine::~Combine() {
    //cout << "Combine is destroyed." << endl;

}