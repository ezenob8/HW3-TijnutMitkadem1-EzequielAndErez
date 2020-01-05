//
// Created by erez on 07/11/2019.
//

#include <iostream>
#include "Div.h"

Div::Div(Expression *expression1, Expression *expression2) : BinaryOperator(expression1, expression2) {

}

double Div::calculate() {
    if (this->right->calculate() == 0) {
        const char *exception = "Division by zero!";
        throw exception;
    } else {
        return this->left->calculate() / this->right->calculate();
    }
}

Div::~Div() {
    delete this->right;
    delete this->left;
}