//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "LoopCommand.h"
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

int LoopCommand::execute(vector<string> *v, int i) {
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
        bool again = false;//to do again or not
        while (smaller->calculate()) {
            if (again) {
                i = i2;//do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            smaller = new IsSmaller(expression1, expression2);
            if (smaller->calculate()) {
                again = true;//do it again
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
        bool again = false; //to do again or not
        while (smallerEquals->calculate()) {
            if (again) {
                i = i2; //do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            smallerEquals = new IsSmallerEquals(expression1, expression2);
            if (smallerEquals->calculate()) {
                again = true;//do it again
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
        bool again = false;//to do again or not
        while (bigger->calculate()) {
            if (again) {
                i = i2;//do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            bigger = new IsBigger(expression1, expression2);
            if (bigger->calculate()) {
                again = true;//do it again
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
        bool again = false;//to do again or not
        while (biggerEquals->calculate()) {
            if (again) {
                i = i2;//do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            biggerEquals = new IsBiggerEquals(expression1, expression2);
            if (biggerEquals->calculate()) {
                again = true; //do it again
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
        bool again = false;//to do again or not
        while (equals->calculate()) {
            if (again) {
                i = i2; //do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            equals = new IsEquals(expression1, expression2);
            if (equals->calculate()) {
                again = true; //do it again
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
        bool again = false;//to do again or not
        while (notEquals->calculate()) {
            if (again) {
                i = i2; //do it again
                again = false;
            }
            //do all the commands in the scope
            while (v->at(i) != "}") {
                if (MapCommands::getInstance().getCommands()->count(v->at(i)) > 0) {
                    Command *c = (MapCommands::getInstance().getCommands()->find(v->at(i)))->second;
                    i += c->execute(v, i);
                } else {
                    i++;
                }
            }
            //resetting the variables of interpreter left
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
            //resetting the variables of interpreter right
            for (auto &it : *Singleton::getInstance().getVarToSim()) {
                if (right.find(it.first) != -1) {
                    setVariables += it.first + "=" + to_string(it.second->getValue()) + ";";
                }
            }
            if (setVariables != "") {
                interpreter2->setVariables(setVariables);
            }
            Expression *expression2 = interpreter1->interpret(right);
            notEquals = new IsNotEquals(expression1, expression2);
            if (notEquals->calculate()) {
                again = true; //do it again
            }
        }
        delete notEquals;
    }
    return i - i1;
}
