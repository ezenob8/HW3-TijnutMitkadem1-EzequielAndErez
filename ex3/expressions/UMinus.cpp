//
// Created by erez on 06/11/2019.
//

#include "UMinus.h"

UMinus::UMinus(Expression *expression1) : UnaryExpression(expression1) {

}

double UMinus::calculate() {
    return -1 * this->expression->calculate();
}

UMinus::~UMinus() {
    delete this->expression;
}
