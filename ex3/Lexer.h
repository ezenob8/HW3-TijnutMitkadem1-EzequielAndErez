//
// Created by Erez Rigevsky and Ezequiel Glocer on 27/12/2019.
//

#ifndef EX3_LEXER_H
#define EX3_LEXER_H

#include "string"
#include <vector>

using namespace std;

class Lexer {
private:
    static void replaceAll(string &str, const string &toReplace, const string &replacing);

    static void noWhileAndIfReplace(string &str);

    static void splitStringsToVector(const string &str, vector<string> *vec_str, char delimiter, int flag);

    static void whileAndIfCondition(string str, vector<string> *strings);

public:
    static vector<string> *lex(const string &s);
};

#endif //EX3_LEXER_H