#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "Harvest.hpp"


#define START_TIME 0
#define NUM_OF_DAYS 3
#define TIME_CONSTANT 60 * 24 

#define NUM_OF_COMBINES 7
#define NUM_OF_TRACTORS 4

// field size in kilometres squared
#define FIELD_SIZE 100.0 // 100km^2

using namespace std;

int main(int argc, char *argv[]) {

    srand((unsigned int)time(NULL));
    RandomSeed(time(nullptr));

    unsigned long num_combines = NUM_OF_COMBINES;
    unsigned int num_tractors = NUM_OF_TRACTORS;
    unsigned int num_days = NUM_OF_DAYS;

    // Parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "c:t:d:")) != -1) {
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
    Stat *statTractorDumpingDuration = new Stat("Tractor dumping time");
    Stat *statTractorNumRuns = new Stat("Tractor number of runs");

    // other
    Stat *statWhetaherRecord = new Stat("Weather record");
    Stat *statQueueOcupancy = new Stat("Queue occupancy");

    //for (int i = 1; i <= 5; i++) {
    //    cout << "RUN NUMBER " << i << "." << endl;
        Init(START_TIME, TIME_CONSTANT * num_days);
        (new Harvest(num_combines, num_tractors, FIELD_SIZE, statCombineNumRuns,statCombineHarvestDuration,statCombineWaitDuration,
        statTractorDumpingDuration, statTractorNumRuns, statWhetaherRecord, statQueueOcupancy))->Activate();
        Run();
    //    cout << "RUN NUMBER " << i << ". STATISTICS" << endl;
    //}

    statCombineNumRuns->Output();
    statCombineHarvestDuration->Output();
    statCombineWaitDuration->Output();
    statTractorNumRuns->Output();
    statTractorDumpingDuration->Output();
    statWhetaherRecord->Output();
    statQueueOcupancy->Output();
    SIMLIB_statistics.Output();

    cout << "------------------------" << endl;
    cout << "SIMULATION FINISHED" << endl;
    cout << "------------------------" << endl;

    return 0;
}
