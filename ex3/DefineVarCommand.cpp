//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "DefineVarCommand.h"
#include "expressions/Interpreter.h"
#include <mutex>
#include <iostream>

int DefineVarCommand::execute(vector<string> *v, int i) {
    //if the command looks like this: var x = ....
    if (v->at(i + 2) == "=") {
        string var = v->at(i + 1);
        string to_assign = v->at(i + 3);
        string setVariables = "";
        Interpreter *interpreter = new Interpreter();

        //setting the variables and values of the interpreter
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (to_assign.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter->setVariables(setVariables);
        }
        Expression *expression = interpreter->interpret(to_assign);
        double value = expression->calculate();
        Info *info = new Info();
        info->setValue(value);
        info->setSim("");
        Singleton::getInstance().getMutex().lock();
        Singleton::getInstance().getVarToSim()->insert({var, info});
        Singleton::getInstance().getMutex().unlock();
        delete interpreter;
    } else {
        //the command looks like this: var x = sim(...)
        string var = v->at(i + 1);
        string sim = v->at(i + 3);
        Info *info = new Info(sim);
        Singleton::getInstance().getMutex().lock();
        //insert to the first map in the singleton
        Singleton::getInstance().getVarToSim()->insert({var, info});
        if (v->at(i + 2) == "<-") {
            //insert to the second map in the singleton
            string var_Sim = v->at(i + 3);
            Singleton::getInstance().getSimToVar()->insert({var_Sim, info});
        }
        Singleton::getInstance().getMutex().unlock();
    }

    return 4; //we need to jump 4 places in the vector for the next command
}
