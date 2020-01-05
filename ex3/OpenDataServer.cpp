//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "OpenDataServer.h"
#include "thread"
#include "expressions/Expression.h"
#include "expressions/Interpreter.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>

using namespace std;

void OpenDataServer::server(int client_socket) {
    char buffer[1024] = {0};
    string val = "";
    int index = 0;//place in the map
    int j = 0;
    //reading from simulator
    read(client_socket, buffer, 1024);
    //while not done
    while (Singleton::getInstance().getSignal() != "done") {
        //for every place in the simulator vector varSim until \n
        while (index < varSim->size()) {
            //add the char
            if (buffer[j] != '\n' && buffer[j] != ',') {
                val += buffer[j];
                j++;
            } else {
                //set the variables value
                if (Singleton::getInstance().getSimToVar()->find(varSim[index]) !=
                    Singleton::getInstance().getSimToVar()->end()) {
                    Singleton::getInstance().getSimToVar()->find(varSim[index])->second->setValue(stod(val));
                }
                if (buffer[j] == '\n') {
                    break;
                }
                index++;
                j++;
                val = "";
            }
        }
        read(client_socket, buffer, 1024);
        index = 0;
        j = 0;
    }
    close(client_socket);
}


int OpenDataServer::execute(vector<string> *v, int i) {
    auto *intr = new Interpreter();
    Expression *ex = intr->interpret(v->at(i + 1));
    double server_port = ex->calculate();//5400
    delete intr;
    delete ex;
    thread t1;
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address{}; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(server_port);
    //we need to convert our number to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        return -1;
    }

    //making socket listen to the port
    if (listen(socketfd, SOMAXCONN) == -1) {
        std::cerr << "Error during listening command" << std::endl;
        return -1;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }
    int ad_len = sizeof(address);
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &ad_len);

    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        return -1;
    }

    DefineVarSim();
    thread t(&OpenDataServer::server, this, client_socket);
    t.detach();
    return 2;
}

void OpenDataServer::DefineVarSim() {
    varSim[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
    varSim[1] = "/sim/time/warp";
    varSim[2] = "/controls/switches/magnetos";
    varSim[3] = "/instrumentation/heading-indicator/offset-deg";
    varSim[4] = "/instrumentation/altimeter/indicated-altitude-ft";
    varSim[5] = "/instrumentation/altimeter/pressure-alt-ft";
    varSim[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
    varSim[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
    varSim[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
    varSim[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
    varSim[10] = "/instrumentation/encoder/indicated-altitude-ft";
    varSim[11] = "/instrumentation/encoder/pressure-alt-ft";
    varSim[12] = "/instrumentation/gps/indicated-altitude-ft";
    varSim[13] = "/instrumentation/gps/indicated-ground-speed-kt";
    varSim[14] = "/instrumentation/gps/indicated-vertical-speed";
    varSim[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
    varSim[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
    varSim[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
    varSim[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
    varSim[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
    varSim[20] = "/controls/flight/aileron";
    varSim[21] = "/controls/flight/elevator";
    varSim[22] = "/controls/flight/rudder";
    varSim[23] = "/controls/flight/flaps";
    varSim[24] = "/controls/engines/engine/throttle";
    varSim[25] = "/controls/engines/current-engine/throttle";
    varSim[26] = "/controls/switches/master-avionics";
    varSim[27] = "/controls/switches/starter";
    varSim[28] = "/engines/active-engine/auto-start";
    varSim[29] = "/controls/flight/speedbrake";
    varSim[30] = "/sim/model/c172p/brake-parking";
    varSim[31] = "/controls/engines/engine/primer";
    varSim[32] = "/controls/engines/current-engine/mixture";
    varSim[33] = "/controls/switches/master-bat";
    varSim[34] = "/controls/switches/master-alt";
    varSim[35] = "/engines/engine/rpm";
}

