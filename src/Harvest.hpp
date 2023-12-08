#ifndef HARVEST_HPP
#define HARVEST_HPP

#include <simlib.h>
#include "Combine.hpp"

class Harvest : public Process
{
public:
    Harvest(unsigned long num_combine,
            unsigned int num_tractor, float FIELD_SIZE, unsigned int shift_length,
            Stat *statCombineNumRuns,
            Stat *statCombineHarvestDuration,
            Stat *statCombineWaitDuration, 
            Stat *statTractorNumRuns, 
            Stat *statWhetaherRecord, 
            Stat *statQueueOcupancy,
            float *fieldSize
            );

    ~Harvest() override;

    void Behavior() override;

    unsigned long num_combines;

    unsigned int num_tractors;

    float field_size;
    float *fieldSize;
    float beginningFieldSize;

    unsigned int shift_len;

private:
    unsigned long harvested_size;
    bool isShift;

    Store *shifts;

    // stats
    // kombajn
    Stat *statCombineNumRuns;
    Stat *statCombineHarvestDuration;
    Stat *statCombineWaitDuration;
    // traktor
    Stat *statTractorNumRuns;

    Stat *statWhetaherRecord;

    Stat *statQueueOcupancy;
};

#endif // HARVEST_HPP