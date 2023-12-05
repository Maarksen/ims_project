#ifndef COMBINE_HPP
#define COMBINE_HPP

#include <simlib.h>

class Combine : public Process {
    public:
        Combine(Store *combines , float* fieldSize);

        void Behavior() override;

        ~Combine() override;

        float* fieldSize;


    private:

    Store *combines;
};

#endif // COMBINE_HPP 