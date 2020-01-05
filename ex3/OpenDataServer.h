//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_OPENDATASERVER_H
#define EX3_OPENDATASERVER_H

#include "Command.h"

class OpenDataServer : public Command {

public:
    //define the sim variable vector
    void DefineVarSim();

    int execute(vector<string> *v, int i) override;

    //server thread
    void server(int client_socket);
};


#endif //EX3_OPENDATASERVER_H
