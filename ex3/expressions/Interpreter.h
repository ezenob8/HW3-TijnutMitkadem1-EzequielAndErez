//
// Created by erez on 08/11/2019.
//

#ifndef EX1_CPP_INTERPRETER_H
#define EX1_CPP_INTERPRETER_H


#include "Expression.h"
#include <cstring>
#include <queue>
#include <stack>
#include <map>
using namespace std;

class Interpreter {
private:
    map<string, double> *variables;
    stack<char> *operators;
    queue<string> *components;
    stack<Expression *> *makeExpression;

    static bool isNumber(const std::string &s);

    int interpretErrors(string string1);

public:
    ~Interpreter();

    Interpreter();

    Expression *interpret(string str);

    void setVariables(string str);
};


#endif //EX1_CPP_INTERPRETER_H
