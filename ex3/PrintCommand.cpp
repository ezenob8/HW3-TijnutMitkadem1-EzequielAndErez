//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "expressions/Interpreter.h"
#include <cstring>

using namespace std;

int PrintCommand::execute(vector<string> *v, int i) {
    string to_print = v->at(i + 1); //what to print
    if (to_print.find('"')!=-1) { //if to print is a string
        to_print = to_print.substr(1, to_print.size() - 2);//erase the "
        //if to_print is "done", the flight of the plane finished
        if (to_print == "done") {
            Singleton::getInstance().setSignal("done"); //set signal to done
        }
        cout << to_print << endl; //print
    } else {
        //to print is an expresion
        Interpreter *interpreter = new Interpreter();
        string setVariables = "";
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (to_print.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter->setVariables(setVariables);
        }
        Expression *expression2 = interpreter->interpret(to_print);
        cout << expression2->calculate() << endl;//print the result
        delete interpreter;
        delete expression2;
    }

    return 2; //we need to jump 2 places in the vector for the next command
}