#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

#include "Harvest.hpp"

#define START_TIME 0
#define END_TIME 60*24*21

#define NUM_OF_COMBINES 5
#define NUM_OF_TRACTORS 2

//field size in kilometres squared
#define FIELD_SIZE 10.0 // 10km^2

using namespace std;

int main(int argc, char *argv[]) {

    srand((unsigned int)time(NULL));
    RandomSeed(time(nullptr));

    unsigned long num_conbines = NUM_OF_COMBINES; 
    unsigned int num_tractors = NUM_OF_TRACTORS;


    //arguments handling 
    if(argc != 3 && argc != 1){
        cerr << "[ERROR] Invalid number of arguments! usage:" << argv[0] << " <integer1> <integer2>" << endl;
        return 1;
    }

    if (argc ==3 ){
        try{
            //converting the command line arguments to integers
            num_conbines = stoi(argv[1]);
            num_tractors = stoi(argv[2]);
        }
        catch(const invalid_argument& e){
            cerr << "[ERROR] Arguments must be of type unsigned int! ussage:" << argv[0] << " <integer1> <integer2>" << endl;
            return 1;
        }
    }

    if (num_conbines <= 0 || num_tractors <= 0){
        cerr << "[ERROR] Arguments must be greater than 0! ussage:" << argv[0] << " <integer1> <integer2>" << endl;
        return 1;
    }


    cout << "------------------------" << endl;
    cout << "SIMULATION START ty coco" << endl;

    //for(int i = 0; i < 5; i++){
        cout << "RUN NUMBER " << /*i << */ "." << endl;
        Init(START_TIME, END_TIME);
        (new Harvest(num_conbines, num_tractors, FIELD_SIZE))->Activate();
        Run();
        SIMLIB_statistics.Output();
    //}

    cout << "SIMUATION FINISHED" << endl;
    cout << "------------------------" << endl;


    

    return 0;
}