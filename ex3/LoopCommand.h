//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_LOOPCOMMAND_H
#define EX3_LOOPCOMMAND_H


#include "Command.h"

class LoopCommand : public Command{
 int execute(vector<string> *v, int i) override;
};


#endif //EX3_LOOPCOMMAND_H
