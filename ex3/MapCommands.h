//
// Created by Erez Rigevsky and Ezequiel Glocer on 30/12/2019.
//

#ifndef EX3_MAPCOMMANDS_H
#define EX3_MAPCOMMANDS_H

#include <string>
#include <map>
#include "Command.h"
#include "Command.h"
#include "OpenDataServer.h"
#include "ConnectControlClient.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "LoopCommand.h"
#include "AssignVarCommand.h"
#include "ConditionCommand.h"

using namespace std;

//Singleton map of the commands
class MapCommands {
private:
    map<string, Command *> *commands = new map<string, Command *>;

    MapCommands(MapCommands const &);

    MapCommands() {}

    void operator=(MapCommands const &);

public:
    //get the instance of the singleton
    static MapCommands &getInstance() {
        static MapCommands instance;
        return instance;
    }

    //get the map
    map<string, Command *> *getCommands() {
        return this->commands;
    }

    /*
     * Inserting the commands we will use for the simulator to the Map of commands.
     */
    void DefineCommands() {
        commands->insert({"openDataServer", new OpenDataServer()});
        commands->insert({"connectControlClient", new ConnectControlClient()});
        commands->insert({"var", new DefineVarCommand()});
        commands->insert({"Print", new PrintCommand()});
        commands->insert({"Sleep", new SleepCommand()});
        commands->insert({"while", new LoopCommand()});
        commands->insert({"=", new AssignVarCommand()});
        commands->insert({"if", new ConditionCommand()});
    }

};

#endif //EX3_MAPCOMMANDS_H