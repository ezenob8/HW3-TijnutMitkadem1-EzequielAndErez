//
// Created by erez on 05/11/2019.
//

#include "Variable.h"

using namespace std;

Variable::Variable(string theName, double theValue) : name(theName), value(theValue) {}

Variable &Variable::operator++() {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}


Variable &Variable::operator+=(double num1) {
    this->value += num1;
    return *this;
}

Variable &Variable::operator-=(double num1) {
    this->value -= num1;
    return *this;
}

Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

double Variable::calculate() {
    return this->value;
}

Variable::~Variable() {

}