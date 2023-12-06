#ifndef COMBINE_HPP
#define COMBINE_HPP

#include <simlib.h>
#include "TractorFacility.hpp"

class Combine : public Process {
    public:
        Combine(int num, Store *combines , float* fieldSize, TractorFacility *tractors);

        void Behavior() override;

        ~Combine() override;

        float* fieldSize;

        Priority_t Priority = 0;

        TractorFacility *tractors;

        int num;


    private:

    Store *combines;
};

#endif // COMBINE_HPP 