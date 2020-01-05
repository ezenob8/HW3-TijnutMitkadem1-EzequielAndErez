//
// Created by erez on 08/11/2019.
//
#include <iostream>
#include "Interpreter.h"
#include "Value.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "UMinus.h"
#include "UPlus.h"

using namespace std;

//constructor
Interpreter::Interpreter() {
    this->operators = new stack<char>;
    this->components = new queue<string>;
    this->variables = new map<string, double>;
    this->makeExpression = new stack<Expression *>;
}

//destructor
Interpreter::~Interpreter() {
    delete this->variables;
    delete this->makeExpression;
    delete this->operators;
    delete (this->components);
}

//returns if a string is numeric
bool Interpreter::isNumber(const string &s) {
    return (strspn(s.c_str(), ".0123456789") == s.size());
}

bool isInside(const std::string &str, char c) {
    return str.find(c) != std::string::npos;
}

//sets the variables of the interpreter
void Interpreter::setVariables(string str) {
    std::string key;
    int lastEquals = 0;
    double value;
    unsigned int i = 0;
    int j = 0;
    while (i != str.length()) {
        if (str[i] == '=') {
            key = str.substr(j, i - j);
            if (!((key[0] >= 'a' && key[0] <= 'z') || key[0] == '_')) {
                const char *exception = "Bad input!";
                throw exception;
            }
            //between every 2 equals must be a ;. else- error!
            if (lastEquals != 0 && !isInside(str.substr(lastEquals, i - lastEquals + 1), ';')) {
                const char *exception = "Bad input!";
                throw exception;
            }
            lastEquals = i;
            j = i + 1;
        } else if (str[i] == ';') {
            value = stod(str.substr(j, i - j));

            if (this->variables->empty() ||
                (!this->variables->empty() && variables->find(key) == variables->end())) {
                variables->insert({key, value});
            } else {
                this->variables->find(key)->second = value;
            }
            j = i + 1;
        } else if (str[i] == '.') {
            if (i == 0 || i == str.length() - 1) {
                const char *exception = "Bad input!";
                throw exception;
            }
            if (!((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i + 1] >= '0' && str[i + 1] <= '9'))) {
                const char *exception = "illegal variable assignment!";
                throw exception;
            }
        } else if (str[i] == '_') {
            if (!(str[i - 1] >= 'a' && str[i - 1] <= 'z' &&
                  ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= '0' && str[i + 1] <= '9')))) {
                const char *exception = "illegal variable assignment!";
                throw exception;
            }
        } else if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') ||
                     (str[i] == '-' && isNumber(string(1, str[i + 1])) && str[i - 1] == '='))) {
            const char *exception = "illegal variable assignment!";
            throw exception;
        }

        if (i == str.length() - 1 && str[i] != ';') {
            value = stod(str.substr(j, i - j + 1));
            if (this->variables->empty() ||
                (!this->variables->empty() && variables->find(key) == variables->end())) {
                variables->insert({key, value});
            } else {
                this->variables->find(key)->second = value;
            }
        }
        i++;
    }
}

// function to check if brackets are balanced
int Interpreter::interpretErrors(string str) {
    stack<char> s;
    for (unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            s.push(str[i]);
            continue;
        }
        char x = str[i];
        if ((x >= '0' && x <= '9') || (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z') || (x == '+') || x == '-' ||
            x == '*' || x == '/') {
            continue;
        } else if (x == ')') {
            if (s.empty()) {
                return 0;
            }
            s.pop();
            continue;
        } else if (x == '.') {
            if (!((str[i - 1] >= '0' && str[i - 1] <= '9') && (str[i + 1] >= '0' && str[i + 1] <= '9'))) {
                return 0;
            }
            continue;
        } else if (x == '_') {
            if (i == 0 || i == str.length() - 1) {
                return 0;
            }
            if (!(str[i - 1] >= 'a' && str[i - 1] <= 'z' &&
                  ((str[i + 1] >= 'a' && str[i + 1] <= 'z') || (str[i + 1] >= '0' && str[i + 1] <= '9')))) {
                return 0;
            }
        } else if(x==32){
            continue;
        } else{
            return 0;
        }
    }
    // Check Empty Stack
    if (s.empty()) {
        return 1;
    } else {
        return 0;
    }
}


//intepret the string to an expression
Expression *Interpreter::interpret(string str) {
    //input check
    if (interpretErrors(str) == 0) {
        const char *exception = "Bad input!";
        throw exception;
    }
    //input is fine

    unsigned int i = 0;
    string varnum = "";//the variable or the number to operate on
    string op;//the operator/operand
    while (i < str.length()) {
        //while we read a number or variable, put it togehter
        while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == '.') {
            varnum += str[i];
            i++;
        }
        if (varnum != "") {
            //varnum is a variable and is not defined in the variables map
            if (((varnum[0] >= 'a' && varnum[0] <= 'z') || varnum[0] == '_') &&
                this->variables->find(varnum) == this->variables->end()) {
                const char *exception = "variable not defined";
                throw exception;
            }
            this->components->push(varnum);//pust to the queue
            varnum = "";
        }
        //if the string hasn't ended
        if (i < str.length()) {
            switch (str[i]) {
                case '(':
                    operators->push(str[i]);
                    break;
                case ')':
                    //pop from stack and push to queue
                    while (this->operators->top() != '(') {
                        op = this->operators->top();
                        this->operators->pop();
                        this->components->push(op);
                        //if we reached '(' just pop
                        if (this->operators->top() == '(') {
                            this->operators->pop();
                            break;
                        }
                    }
                    break;
                case '*':
                case '/':
                    if (str[i + 1] == 0) {
                        const char *exception = "Division by zero";
                        throw exception;
                    } else if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '/' || str[i + 1] == '*') {
                        const char *exception = "illegal math expression!";
                        throw exception;
                    }

                    if (!this->operators->empty()) {
                        //if we meet another mul or div move the to the queue
                        //if not, just push to the stack
                        while ((operators->top() == '*' || operators->top() == '/') && !this->operators->empty()) {
                            op = this->operators->top();
                            this->operators->pop();
                            this->components->push(op);
                        }
                    }
                    this->operators->push(str[i]);
                    break;
                case '+':
                case '-':
                    if (str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '/' || str[i + 1] == '*') {
                        cout << "illegal math expression" << endl;
                    }
                    //the sign is an unary
                    if (i == 0 || str[i - 1] == '(') {
                        if (str[i] == '+') {
                            this->operators->push('p');
                        } else {
                            this->operators->push('m');
                        }
                    }
                        //the sign is an operator
                    else {
                        if (!this->operators->empty()) {
                            //if we meet ever other operator, move it to the queue
                            //if not, just push to the stack
                            while (!this->operators->empty() &&
                                   (operators->top() == '*' || operators->top() == '/' || operators->top() == '+' ||
                                    operators->top() == '-' || operators->top() == 'p' || operators->top() == 'm')
                                    ) {
                                op = this->operators->top();
                                this->operators->pop();
                                this->components->push(op);
                            }
                        }
                        this->operators->push(str[i]);
                    }
                    break;
                    //we've met any other character that's bad input
                default:
                    break;
            }
        }
        i++;
    }
    //if an operator was left in the stack
    while (!operators->empty()) {
        op = this->operators->top();
        this->operators->pop();
        this->components->push(op);
    }
    //at this point , we achieved the postfix expression
    //now we will make it an expression
    while (!this->components->empty()) {
        op = this->components->front();
        this->components->pop();
        if (isNumber(op)) {
            Value *value = new Value(stod(op));
            this->makeExpression->push(value);
        } else if (op == "+") {
            if (!this->makeExpression->empty()) {
                Expression *expression1 = this->makeExpression->top();
                this->makeExpression->pop();
                Expression *expression2 = this->makeExpression->top();
                this->makeExpression->pop();
                Plus *plus = new Plus(expression2, expression1);
                this->makeExpression->push(plus);
            } else {
                const char *exception = "Error";
                throw exception;
            }

        } else if (op == "-") {
            if (!this->makeExpression->empty()) {
                Expression *expression1 = this->makeExpression->top();
                this->makeExpression->pop();
                Expression *expression2 = this->makeExpression->top();
                this->makeExpression->pop();
                Minus *minus = new Minus(expression2, expression1);
                this->makeExpression->push(minus);
            } else {
                const char *exception = "Error";
                throw exception;
            }
        } else if (op == "*") {
            Expression *expression1 = this->makeExpression->top();
            this->makeExpression->pop();
            if (!this->makeExpression->empty()) {
                Expression *expression2 = this->makeExpression->top();
                this->makeExpression->pop();
                Mul *mul = new Mul(expression2, expression1);
                this->makeExpression->push(mul);
            } else {
                const char *exception = "Error";
                throw exception;
            }
        } else if (op == "/") {
            if (!this->makeExpression->empty()) {
                Expression *expression1 = this->makeExpression->top();
                this->makeExpression->pop();
                Expression *expression2 = this->makeExpression->top();
                this->makeExpression->pop();
                Div *div = new Div(expression2, expression1);
                this->makeExpression->push(div);
            } else {
                const char *exception = "Error";
                throw exception;
            }

        } else if (op == "m") {
            if (!this->makeExpression->empty()) {
                Expression *expression1 = this->makeExpression->top();
                this->makeExpression->pop();
                UMinus *uMinus = new UMinus(expression1);
                this->makeExpression->push(uMinus);
            } else {
                const char *exception = "Error";
                throw exception;
            }

        } else if (op == "p") {
            if (!this->makeExpression->empty()) {
                Expression *expression1 = this->makeExpression->top();
                this->makeExpression->pop();
                UPlus *uPlus = new UPlus(expression1);
                this->makeExpression->push(uPlus);
            } else {
                const char *exception = "Error";
                throw exception;
            }
        } else {
            Variable *variable = new Variable(op, variables->find(op)->second);
            this->makeExpression->push(variable);
        }
    }
    //final expression
    Expression *final = this->makeExpression->top();
    return final;
}


