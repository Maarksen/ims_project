#ifndef TRACTOR_HPP
#define TRACTOR_HPP

#include <simlib.h>
#include "Shift.hpp"

class Shift;
class Tractor : public Process
{
public:
    Tractor(Priority_t priority, Shift *shift,
            Stat *statTractorDumpingDuration,
            Stat *statTractorNumRuns,
            int fullTractor);

    void Behavior() override;

    ~Tractor() override;

    Shift *shift;

    Stat *statTractorDumpingDuration;
    Stat *statTractorNumRuns;

    int fullTractor;

private:
};

#endif // TRACTOR_HPP
