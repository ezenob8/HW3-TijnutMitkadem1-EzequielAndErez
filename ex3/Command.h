//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <vector>
#include <string>
#include <map>
#include "Info.h"
#include "Singleton.h"

using namespace std;

//Command pattern
class Command {
protected:
    string varSim[36]; //variables of the simulator
    static bool done; //if we finished the communication

public:
    virtual int execute(vector<string> *v, int i) = 0;
};


#endif //EX3_COMMAND_H
