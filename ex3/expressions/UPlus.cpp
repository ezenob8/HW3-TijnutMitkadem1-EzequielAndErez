//
// Created by erez on 06/11/2019.
//

#include "UPlus.h"

UPlus::UPlus(Expression *expression1) : UnaryExpression(expression1) {

}

double UPlus::calculate() {
    return this->expression->calculate();
}

UPlus::~UPlus() {
    delete this->expression;
}