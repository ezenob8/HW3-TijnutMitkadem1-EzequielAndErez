//
//Created by Erez Rigevsky and Ezequiel Glocer on 23/12/2019.
//

#ifndef EX3_MAPSINGLETON_H
#define EX3_MAPSINGLETON_H


#include "Info.h"
#include <queue>
#include <map>
#include <mutex>
#include <thread>

class MapSingleton {
private:
    map<string, Info *> *varToSim = new map<string, Info *>;
    map<string, Info *> *simToVar = new map<string, Info *>;
    queue <string> *setToSimulator = new queue<string>;
    string to_stop = "";

    MapSingleton(MapSingleton const &);

    MapSingleton() {

    }

    void operator=(MapSingleton const &);

    mutex to_lock;

public:
    mutex &getMutex() {
        return this->to_lock;
    }

    static MapSingleton &getInstance() {
        static MapSingleton instance;
        return instance;
    }

    const string &getSignal() {
        return this->to_stop;
    }

    void setSignal(const string &str) {
        this->to_stop = str;
    }

    map<string, Info *> *getVarToSim() {
        return this->varToSim;
    }

    map<string, Info *> *getSimToVar() {
        return this->varToSim;

    }

    queue <string> *getQueueSim() {
        return this->setToSimulator;
    }

};

#endif //EX3_MAPSINGLETON_H
