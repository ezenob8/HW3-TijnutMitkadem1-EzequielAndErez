//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#ifndef EX3_SLEEPCOMMAND_H
#define EX3_SLEEPCOMMAND_H

#include "Command.h"
#include "expressions/Interpreter.h"
#include <thread>
#include <chrono>

class SleepCommand: public Command {
   int execute(vector<string> *v, int i) override{
       //sleep for x milliseconds
       Interpreter* inter = new Interpreter();
       int time = inter->interpret(v->at(i+1))->calculate();
       this_thread::sleep_for(chrono::milliseconds(time));
       return 2;
   }
};


#endif //EX3_SLEEPCOMMAND_H
