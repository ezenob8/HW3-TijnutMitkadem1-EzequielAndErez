//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "ConnectControlClient.h"
#include "expressions/Interpreter.h"
#include <sys/socket.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <unistd.h>

using namespace std;

//Writing to client
int ConnectControlClient::client(int client_socket) {
    char buffer[1024];
    //while not done
    while (Singleton::getInstance().getSignal() != "done") {
        //if there is something in the set queue send it
        if (!Singleton::getInstance().getQueueSim()->empty()) {
            Singleton::getInstance().getMutex().lock();
            string str = Singleton::getInstance().getQueueSim()->front();
            Singleton::getInstance().getQueueSim()->pop();
            char buffer[str.size() + 1];
            copy(str.begin(), str.end(), buffer);
            buffer[str.size()] = '\0';
            int sent = send(client_socket, buffer, strlen(buffer), 0);
            if (sent == -1) {
                cout << "Writing Error...." << endl;
            }
            Singleton::getInstance().getMutex().unlock();
        }
    }
    close(client_socket);
}

int ConnectControlClient::execute(vector<string> *v, int i) {
    string client_ip = v->at(i + 1);
    Interpreter *intr = new Interpreter();
    Expression *ex = intr->interpret(v->at(i + 2));
    double client_port = ex->calculate();//5400
    delete intr;
    delete ex;
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) { //error
        cerr << "Could not create a socket" << endl;
        return -1;
    }

    //Creating a sockaddr obj to hold address of server
    sockaddr_in address{}; //it means IP4
    // Complete struct members
    address.sin_family = AF_INET;  //IPv4
    address.sin_addr.s_addr = inet_addr(client_ip.c_str()); //IP of the HOST
    address.sin_port = htons(client_port); // Port to connect
    //connecting to FlightGear
    if (connect(client_socket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "Could not connect to server" << endl;
        return -1;
    }
    thread client_thread(&ConnectControlClient::client, this, client_socket);
    client_thread.detach();

    return 3; //we need to jump 3 places in the vector for the next command
}

