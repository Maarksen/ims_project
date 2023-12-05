#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include "Combine.hpp"

using namespace std;

Combine::Combine(Store *combines, float *fieldSize) : combines(combines) , fieldSize(fieldSize) {
    cout << "Combine is created." << endl;
}

void Combine::Behavior() {
    long time_started = Time;
    Wait(Normal(24,6));
    if (*fieldSize < 0.155) {
        cout << "[" << Time <<  "] filed size is less then 0.150"  << endl;
        *fieldSize = 0;
    }
    else{  
        *fieldSize -= (0.155); //* karvest_time/60;
    }

    cout << "[" << Time << "]";
    cout << " Combine was harvesting for " << Time - time_started << " minutes."<< *fieldSize << " km left in the field." << endl;
    Leave(*combines, 1);
}

Combine::~Combine() {
    //cout << "Combine is destroyed." << endl;

}