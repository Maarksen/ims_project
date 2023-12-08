#ifndef COMBINE_HPP
#define COMBINE_HPP

#include <simlib.h>

#include "TractorFacility.hpp"
#include "Shift.hpp"
#include "Tractor.hpp"

class Shift;

class Combine : public Process {
public:
    Combine( Shift *shift,
             int num,
             Store *combines,
             Stat *statCombineNumRuns,
             Stat *statCombineHarvestDuration,
             Stat *statCombineWaitDuration,
             Stat *statTractorDumpingDuration,
             Stat *statTractorNumRuns,
             Stat *statQueueOcupancy
             );

    void Behavior() override;

    ~Combine() override;

    Shift *shift;

private:
    int num;
    Store *combines;
    float *fieldSize;
    //stats
    //combine 
    Stat *statCombineNumRuns;
    Stat *statCombineHarvestDuration;
    Stat *statCombineWaitDuration;
    //tractor
    Stat *statTractorDumpingDuration;
    Stat *statTractorNumRuns;

    Stat *statQueueOcupancy;
};

#endif // COMBINE_HPP