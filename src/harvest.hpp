#include <simlib.h>

class Harvest : public Process { 
    public:

    Harvest(unsigned int num_combine, unsigned int num_tractor);

    ~Harvest() override;

    void Behavior() override;


};