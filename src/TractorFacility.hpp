#ifndef TRACTORFACILITY_HPP
#define TRACTORFACILITY_HPP

#include <simlib.h>

class TractorFacility : public Facility {
    public:
        TractorFacility();
        // void Behavior() override;

        unsigned long capacity = 3;
    private:

};

#endif // TRACTORFACILITY_HPP