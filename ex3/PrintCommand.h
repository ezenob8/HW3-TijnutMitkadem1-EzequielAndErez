//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_PRINTCOMMAND_H
#define EX3_PRINTCOMMAND_H

using namespace std;

#include "Command.h"

class PrintCommand: public Command {

    int execute(vector<string> * v, int i);
};


#endif //EX3_PRINTCOMMAND_H
