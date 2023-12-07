#ifndef COMBINE_HPP
#define COMBINE_HPP

#include "TractorFacility.hpp"

#include <simlib.h>
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
             Stat *statTractorNumRuns
             );

    void Behavior() override;

    ~Combine() override;

    Shift *shift;

private:
    int num;
    Store *combines;
    float *fieldSize;
    //stats
    //kombajn 
    Stat *statCombineNumRuns;
    Stat *statCombineHarvestDuration;
    Stat *statCombineWaitDuration;
    //traktor
    Stat *statTractorDumpingDuration;
    Stat *statTractorNumRuns;
};

#endif // COMBINE_HPP