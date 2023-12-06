#ifndef TRACTOR_HPP
#define TRACTOR_HPP

#include <simlib.h>
#include "TractorFacility.hpp"

class Tractor : public Process {
    public:
        Tractor(TractorFacility *tractor);

        void Behavior() override;
        ~Tractor() ;

        Priority_t Priority = 1;
        
        TractorFacility *tractor;

    private:


};

#endif // TRACTOR_HPP