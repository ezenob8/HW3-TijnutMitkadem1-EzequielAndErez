//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "SleepCommand.h"
#include "expressions/Interpreter.h"
#include <thread>
#include <chrono>

int execute(vector <string> *v, int i) {
    Interpreter* inter = new Interpreter();
    int time = inter->interpret(v->at(i+1))->calculate(); //the time to sleep
    this_thread::sleep_for(chrono::milliseconds(time)); //making the program sleep
    return 2; //we need to jump 2 places in the vector for the next command
}
