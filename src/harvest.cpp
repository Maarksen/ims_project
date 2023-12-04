#include <iostream>

#include "harvest.hpp"
#include "combine.hpp"
#include "tractor.hpp"

using namespace std;

Harvest::Harvest(unsigned int num_combine, unsigned int num_tractor) {
    //creating combines
    for (unsigned int i = 0; i < num_combine; i++) {
        (new Combine)->Activate();
    }

    //creating tractors
    for (unsigned int i = 0; i < num_tractor; i++) {
        (new Tractor)->Activate();
    }
}
