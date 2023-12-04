#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>

#define NUM_OF_COMBINES 1
#define NUM_OF_TRACTORS 2

//field size in kilometres squared
#define FIELD_SIZE 9

using namespace std;

int main(int argc, char *argv[]) {

    unsigned int num_conbines = NUM_OF_COMBINES; 
    unsigned int num_tractors = NUM_OF_COMBINES;


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

    cout << "Number of combines: " << num_conbines << endl;
    cout << "Number of tractors: " << num_tractors << endl;


    return 0;
}