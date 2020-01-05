//
// Created by Erez Rigevsky and Ezequiel Glocer on 16/12/2019.
//

#ifndef EX3_ASSIGNVARCOMMAND_H
#define EX3_ASSIGNVARCOMMAND_H

#include "ConnectControlClient.h"

//Changes the value of a variable and tells the client what command to send to the variable
class AssignVarCommand: public ConnectControlClient {
    int execute(vector<string> *v, int i) override;
};

#endif //EX3_ASSIGNVARCOMMAND_H
