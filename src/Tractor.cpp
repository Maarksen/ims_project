#include "Tractor.hpp"
#include <iostream>


using namespace std;

Tractor::Tractor(TractorFacility *tractor) : tractor(tractor) {
    cout << "aktivoval sa proces traktora (ide do skladu)" << endl;


}

void Tractor::Behavior(){
    Seize(*tractor,1); //proces traktor si zabera traktor s vyssou prioritou aby mohol ist vysipat obilie do skladu
    cout << "TRAKTOR SYPE" << endl;
    //traktor ide do skladu 
    Wait(Exponential(6));

    //traktor vysypa obilie 
    Wait(Exponential(1.5));

    //tractor sa vracia naspat
    Wait(Exponential(6));
    tractor->capacity = 3;

    cout   << "TRAKTOR VYSYPAL" << endl;
    Release(*tractor);
}

Tractor::~Tractor() {

}