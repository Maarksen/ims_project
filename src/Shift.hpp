#ifndef SHIFT_HPP
#define SHIFT_HPP

#include <simlib.h>  

#include "Harvest.hpp"
#include "Tractor.hpp"

class Harvest;

class Shift : public Process {
public:
    Shift(Harvest *harvest,
          Store *shifts,
          Queue *queue,
          Stat *statCombineNumRuns,
          Stat *statCombineHarvestDuration,
          Stat *statCombineWaitDuration,
          Stat *statTractorNumRuns,
          Stat *statQueueOcupancy,
          TractorFacility **tractorFacilities,
          Stat *statWhetaherRecord
          );

    void Behavior() override;

    ~Shift() override;

    Harvest *harvest;
    Store *shifts;
    Queue *queue;
    Store *combines;
    Store *tractors;
    float *fieldSize;

    Stat *statCombineNumRuns;
    Stat *statCombineHarvestDuration;
    Stat *statCombineWaitDuration;

    Stat *statTractorNumRuns;

    Stat *statQueueOcupancy;

    TractorFacility **tractorFacilities;
    Stat *statWhetaherRecord;

private:
};

#endif // SHIFT_HPP
