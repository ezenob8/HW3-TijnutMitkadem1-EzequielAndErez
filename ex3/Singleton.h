//
// Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_SINGLETON_H
#define EX3_SINGLETON_H

#include "Info.h"
#include <queue>
#include <map>
#include <mutex>
#include <thread>

//Singleton var maps
class Singleton {
private:
    map<string, Info *> *varToSim = new map<string, Info *>; //-> map
    map<string, Info *> *simToVar = new map<string, Info *>; //<- map
    queue <string> *setToSimulator = new queue<string>; //string queue to send to simulator
    string to_stop = "";

    Singleton(Singleton const &);

    Singleton() {}

    void operator=(Singleton const &);

    mutex to_lock;

public:
    //to lock threads
    mutex &getMutex() {
        return this->to_lock;
    }

    //get the instance of the
    static Singleton &getInstance() {
        static Singleton instance;
        return instance;
    }

    //get the signal of the singleton
    const string &getSignal() {
        return this->to_stop;
    }

    //set the signal
    void setSignal(const string &str) {
        this->to_stop = str;
    }

    //get map ->
    map<string, Info *> *getVarToSim() {
        return this->varToSim;
    }

    //get map <-
    map<string, Info *> *getSimToVar() {
        return this->varToSim;

    }

    //get set to sim queue
    queue <string> *getQueueSim() {
        return this->setToSimulator;
    }

};

#endif //EX3_SINGLETON_H
