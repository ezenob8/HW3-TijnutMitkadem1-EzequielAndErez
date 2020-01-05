//
// Created by Erez Rigevsky and Ezequiel Glocer on 21/12/2019.
//

#ifndef EX3_CONDITIONCOMMAND_H
#define EX3_CONDITIONCOMMAND_H


#include "Command.h"

//if command
class ConditionCommand : public Command {
    int execute(vector <string> *v, int i) override;
};

#endif //EX3_CONDITIONCOMMAND_H
