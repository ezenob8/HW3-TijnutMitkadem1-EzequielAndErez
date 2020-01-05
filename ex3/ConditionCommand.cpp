//
// Created by Erez Rigevsky and Ezequiel Glocer on 21/12/2019.
//

#include "ConditionCommand.h"
#include "expressions/IsEquals.h"
#include "expressions/Value.h"
#include "expressions/IsNotEquals.h"
#include "expressions/IsSmaller.h"
#include "expressions/IsSmallerEquals.h"
#include "expressions/IsBigger.h"
#include "expressions/IsBiggerEquals.h"
#include "expressions/Interpreter.h"
#include "map"
#include "MapCommands.h"

using namespace std;

int ConditionCommand::execute(vector<string> *v, int i) {
    Interpreter *interpreter1 = new Interpreter();
    Interpreter *interpreter2 = new Interpreter();
    int i1 = i;
    string left = v->at(++i);
    i++;
    string right = v->at((++i));
    string setVariables;

    if (v->at(i - 1) == "<") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression <
        Expression *smaller = new IsSmaller(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        if (smaller->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete smaller;
    } else if (v->at(i - 1) == "<=") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression <=
        Expression *smallerEquals = new IsSmallerEquals(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        if (smallerEquals->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete smallerEquals;
    }else if (v->at(i - 1) == ">") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression >
        Expression *bigger = new IsBigger(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        if (bigger->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete bigger;
    }else if (v->at(i - 1) == ">=") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression >=
        Expression *biggerEquals = new IsBiggerEquals(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        if (biggerEquals->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete biggerEquals;
    } else if (v->at(i - 1) == "==") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression ==
        Expression *equals = new IsEquals(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        if (equals->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete equals;
    }else if (v->at(i - 1) == "!=") {
        //setting the variables of the interpreter of left
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (left.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter1->setVariables(setVariables);
        }
        Expression *expression1 = interpreter1->interpret(left);

        setVariables = "";
        //setting the variables of the interpreter of right
        for (auto &it : *Singleton::getInstance().getVarToSim()) {
            if (right.find(it.first) != -1) {
                setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
            }
        }
        if (setVariables != "") {
            interpreter2->setVariables(setVariables);
        }
        Expression *expression2 = interpreter1->interpret(right);

        //expression !=
        Expression *notEquals = new IsNotEquals(expression1, expression2);
        i++;
        if (v->at(i) == "{") {
            i++;
        }
        int i2 = i;
        while (notEquals->calculate()) {
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
        }
        delete notEquals;
    }
    return i - i1;
}
