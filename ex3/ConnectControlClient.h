//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_CONNECTCONTROLCLIENT_H
#define EX3_CONNECTCONTROLCLIENT_H


#include "Command.h"

//Client
class ConnectControlClient : public Command {
public:
    int execute(vector<string> *v, int i) override;

    int client(int client_socket);

};


#endif //EX3_CONNECTCONTROLCLIENT_H
