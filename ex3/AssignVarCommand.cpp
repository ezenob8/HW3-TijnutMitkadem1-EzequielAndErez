//
// Created by Erez Rigevsky and Ezequiel Glocer on 16/12/2019.
//

#include "AssignVarCommand.h"
#include "ConnectControlClient.h"
#include "expressions/Interpreter.h"
#include <mutex>

int AssignVarCommand::execute(vector<string> *v, int i) {
    string var = v->at(i - 1); //the variable to put value in
    string right = v->at(i + 1); //the value to put
    string setVariables = ""; //string to set the variables of the interpreter
    Interpreter *interpreter = new Interpreter();

    //setting the variables and values of the interpreter
    for (auto &it : *Singleton::getInstance().getVarToSim()) {
        if (right.find(it.first) != -1) { //variable exists in the map
            setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
        }
    }
    //expression includes variables
    if (setVariables != "") {
        interpreter->setVariables(setVariables);
    }

    Expression *expression = interpreter->interpret(right);
    double value = expression->calculate(); //the value to put
    Singleton::getInstance().getMutex().lock();
    //put the value in the map
    Singleton::getInstance().getVarToSim()->find(var)->second->setValue(value);

    string sim = Singleton::getInstance().getVarToSim()->find(var)->second->getSim();
    //the string to send to the simulator
    string str = "set " + sim + " " + to_string(value)+"\r\n";
    //put the string in the setQueue
    Singleton::getInstance().getQueueSim()->push(str);
    Singleton::getInstance().getMutex().unlock();
    delete interpreter;
    delete expression;
    return 2;//we need to jump 2 places in the vector for the next command
}
