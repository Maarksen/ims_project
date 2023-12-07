#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Combine.hpp"
#include "TractorFacility.hpp"

using namespace std;

Combine::Combine(int num, Store *combines, Shift *shift) : num(num), combines(combines) , shift(shift){
    cout << "Combine is created." << endl;
    this->fieldSize = shift->fieldSize;
}

void Combine::Behavior() {
    long time_started = Time;
    int number = num;
    Wait(Normal(24,6));
    cout << "field size before harvesting:" << *fieldSize << endl;
        
    if (*fieldSize < 0.055) {
       *fieldSize = 0;
    }
    else{  
        *fieldSize -= 0.055; //* harvest_time/60;
    }

    cout << "[" << Time << "]";
    cout << " Combine " << number << " was harvesting for " << Time - time_started << " minutes."<< *fieldSize << " km left in the field." << endl;
    
    // cout << "capacity of the tractor before dumping :" << tractors->capacity <<  endl;
    long waiting_time = Time;

    //kombajn sa snazi ziskat traktor

    int k = -1;
    back:
    for(int i = 0; i < 2; i++){
        if(!shift->tractorFacilities[i]->Busy()){ 
            k = i;
            break;
        }
    }
    if(k == -1){
        Into(shift->queue);
        Passivate();
        goto back;

    }
    Seize(*shift->tractorFacilities[k]);
    cout << "[" << Time << "]" << "kombajn["<< number <<"] ziskal traktor cislo  " <<  k  << " s kapacitou "<< shift->tractorFacilities[k]->capacity <<  endl;
    //vysypu sa
    shift->tractorFacilities[k]->capacity -= 1;
    Wait(1.5);


    //ak je traktor full, spustame proces vysypania do skladu
    if (shift->tractorFacilities[k]->capacity == 0){
        // cout << "[" << Time << "]" << "Traktor je fullka, vysielam ho do skladu(nikto nevie seiznut traktor medzi tymto a TRAKTOR SYPE)" << endl;
        // cout << "toto je qyueueu" << this->queue->Length() << endl;
        (new Tractor(this->shift, 1))->Activate(); 
    }
    // cout << "[" << Time << "]" << "kombajn[" <<number << "]releasuje trakokot, traktor capa:" << tractors[k]->capacity << endl;
    cout << "["<< Time<< "]"<<"kombajn cislo "<<  number << " vypusta traktor cislo " << k << endl;
    Release(*shift->tractorFacilities[k]);
    
    if(shift->queue->Length() > 0){
        (shift->queue->GetFirst())->Activate();
    }
    // }
    //cout << "[" << Time << "]" << "releasing the tractor. Combine was waiting for " << Time - waiting_time << endl;

    Leave(*combines, 1);
}

Combine::~Combine() {
    //cout << "Combine is destroyed." << endl;

}