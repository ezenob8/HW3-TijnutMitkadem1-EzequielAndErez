//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H


#include "Command.h"
#include "Info.h"

class DefineVarCommand : public Command {
public:
    int execute(vector <string> *v, int i) override;
};


#endif //EX3_DEFINEVARCOMMAND_H
