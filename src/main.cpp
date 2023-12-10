#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Harvest.hpp"


#define START_TIME 0
#define NUM_OF_DAYS 14
#define TIME_CONSTANT 60 * 24 

#define LEN_SHIFT 8

#define NUM_OF_COMBINES 3
#define NUM_OF_TRACTORS 4

// field size in kilometres squared
#define FIELD_SIZE 70.0 // 100km^2

using namespace std;

int main(int argc, char *argv[]) {

    srand((unsigned int)time(NULL));
    RandomSeed(time(nullptr));

    // default values
    unsigned long num_combines = NUM_OF_COMBINES;
    unsigned int num_tractors = NUM_OF_TRACTORS;
    unsigned int num_days = NUM_OF_DAYS;
    unsigned int shift_length = LEN_SHIFT;
    float field_size = (float)FIELD_SIZE;
    float *fieldSize = &field_size; 

    // Parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:s:f:")) != -1) {
        switch (opt) {
            case 'c':
                try {
                    num_combines = stoi(optarg);
                } catch (const invalid_argument &e) {
                    cerr << "[ERROR] Argument for -c must be an unsigned int!" << endl;
                    return 1;
                }
                break;
            case 't':
                try {
                    num_tractors = stoi(optarg);
                } catch (const invalid_argument &e) {
                    cerr << "[ERROR] Argument for -t must be an unsigned int!" << endl;
                    return 1;
                }
                break;

            case 'd':
                try {
                    num_days = stoi(optarg);
                } catch (const invalid_argument &e) {
                    cerr << "[ERROR] Argument for -d must be an unsigned int!" << endl;
                    return 1;
                }
                break;
            case 's':
                try {
                    shift_length = stoi(optarg);
                } catch (const invalid_argument &e) {
                    cerr << "[ERROR] Argument for -s must be an unsigned int!" << endl;
                    return 1;
                }
                break;
            case 'f':
                try {
                    field_size = stoi(optarg);
                } catch (const invalid_argument &e) {
                    cerr << "[ERROR] Argument for -d must be an unsigned int!" << endl;
                    return 1;
                }
                break;
            default:
                cerr << "[ERROR] Invalid arguments! Usage: " << argv[0] << " -c <unsigned int> -t <unsigned int> -d <unisgned int>" << endl;
                return 1;
        }
    }

    if (num_combines <= 0 || num_tractors <= 0) {
        cerr << "[ERROR] Arguments must be greater than 0! Usage: " << argv[0] << " -c <unsigned int> -t <unsigned int> -d <unsigned int>" << endl;
        return 1;
    }

    cout << "------------------------" << endl;
    cout << "SIMULATION START" << endl;
    cout << "------------------------" << endl;   
    // statistics
    // combines
    Stat *statCombineNumRuns = new Stat("Combine number of runs");
    Stat *statCombineHarvestDuration = new Stat("Combine harvest duration");
    Stat *statCombineWaitDuration = new Stat("Combine wait duration");

    // tractors
    Stat *statTractorNumRuns = new Stat("Tractor number of runs");

    // other
    Stat *statWhetaherRecord = new Stat("Weather record");
    Stat *statQueueOcupancy = new Stat("Queue occupancy");

    TractorFacility **tractorFacilities = new TractorFacility*[num_tractors];
    // Create TractorFacility instances
    for (int i = 0; i < (int)num_tractors; i++) {
    tractorFacilities[i] = new TractorFacility();
    }

    float beginningFieldSize = field_size;
    //for (int i = 1; i <= 5; i++) {
    //    cout << "RUN NUMBER " << i << "." << endl;
        Init(START_TIME, TIME_CONSTANT * num_days);
        (new Harvest(num_combines, num_tractors, field_size,  fieldSize, 60 * shift_length, 
        tractorFacilities, statCombineNumRuns,statCombineHarvestDuration,statCombineWaitDuration,
        statTractorNumRuns, statWhetaherRecord, statQueueOcupancy))->Activate();
        Run();
    //    cout << "RUN NUMBER " << i << ". STATISTICS" << endl;
    //}

    statCombineNumRuns->Output();
    statCombineHarvestDuration->Output();
    statCombineWaitDuration->Output();
    statTractorNumRuns->Output();
    statWhetaherRecord->Output();

    // for(int i = 0; i < num_tractors; i++){
    //     cout << "TRACTOR FACILITY " << i + 1 << " STATISTICS" << endl;
    //     tractorFacilities[i]->Output();
    // }

    SIMLIB_statistics.Output();

    delete statCombineHarvestDuration;
    delete statQueueOcupancy;
    delete statCombineNumRuns;
    delete statCombineWaitDuration;
    delete statWhetaherRecord;
    delete statTractorNumRuns;

    cout << "success rate:" << ((beginningFieldSize - field_size)/(float)beginningFieldSize)*100 << "%" << endl;
    cout << " Time: " << (Time / (TIME_CONSTANT)) << " days" << endl;

    cout << "------------------------" << endl;
    cout << "SIMULATION FINISHED" << endl;
    cout << "------------------------" << endl;

    return 0;
}
