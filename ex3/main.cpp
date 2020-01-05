//
// Created by Erez Rigevsky and Ezequiel Glocer on 15/12/2019.
//

#include "list"
#include "vector"
#include "Lexer.h"
#include "Command.h"
#include "MapCommands.h"
#include <string>

using namespace std;

void parser(vector<string> *vector);

int main(int argc, char **argv) {
    try {
        string s = argv[1];
    } catch (exception) {
        throw "no file detected";
    }
    MapCommands::getInstance().DefineCommands();
    Lexer *lexer = new Lexer();
    parser(lexer->lex(argv[1]));
    return 0;
}

/*
 * The parser function receives the vector of strings and goes through
 * the vector of strings to execute the correspondent commands.
 */
void parser(vector<string> *vector) {
    int i = 0;
    while (i < vector->size()) {
        //is command in map (count>0)
        if (MapCommands::getInstance().getCommands()->count(vector->at(i)) > 0) {
            Command *c = (MapCommands::getInstance().getCommands()->find(vector->at(i)))->second;
            i += c->execute(vector, i);
        } else {
            i++;
        }
    }
}




