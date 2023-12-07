#ifndef TRACTOR_HPP
#define TRACTOR_HPP   

#include <simlib.h>
#include "Shift.hpp"

class Shift;
class Tractor : public Process {
public:
    Tractor(Shift *shift, Priority_t priority);

    void Behavior() override;

    ~Tractor() override;
    Shift *shift;

private:
    Queue *queue;
};

#endif // TRACTOR_HPP
