#ifndef HARVEST_HPP
#define HARVEST_HPP

#include <simlib.h>
#include "Combine.hpp"

class Harvest : public Process { 
    public:
        Harvest(unsigned long num_combine, unsigned int num_tractor, float field_size);

        ~Harvest() override;

        void Behavior() override;

        unsigned long num_combines;

        unsigned int num_tractors;

        float field_size;
        

    private:
        unsigned long harvested_size;
        bool isShift;

        //Combine** combines;

        Store *shifts;

        //stats
        //kombajn
        Stat *statCombineNumRuns;
        Stat *statCombineHarvestDuration;
        Stat *statCombineWaitDuration;
        //traktor
        Stat *statTractorDumpingDuration;
        Stat *statTractorNumRuns;
        

};

#endif // HARVEST_HPP