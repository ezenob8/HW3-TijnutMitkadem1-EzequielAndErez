//
// Created by Erez Rigevsky and Ezequiel Glocer on 27/12/2019.
//

#include "Lexer.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

//defines for strings with quote
#define quote "\""
#define quoteAndComma "\","
#define parenthesisAndQuote "(\""
#define quoteAndParenthesis "\")"

//delimiter defines
#define delimiter_as_char '|'
#define delimiter_as_string "|"
#define delimiterAndQuote "|\""
#define delimiterSimParenthesisQuote "|sim(\""
#define varAndDelimiter "var|"
#define equalBetweenDelimiters "|=|"
#define doubleEqualBetweenDelimiters "|==|"
#define differentBetweenDelimiters "|!=|"
#define lessOrEqualBetweenDelimiters "|<=|"
#define lessBetweenDelimiters "|<|"
#define biggerOrEqualBetweenDelimiters "|>=|"
#define biggerBetweenDelimiters "|>|"
#define delimiterAndOpenBracket "|{"

/*
 * This function translates a txt file to a separate vector of strings.
 */
vector<string> *Lexer::lex(const string &s) {
    ifstream input(s);
    auto *vec_strings = new vector<string>;
    string str;
    const char *strConst;
    int firstNoSpace;

    //each time getting a line from the file
    while (getline(input, str)) {
        //in the case we find a while loop in the file
        if (str.find("while") != -1) {
            strConst = str.c_str();
            str = str.substr(6, strlen(strConst) - 6); //while condition without the word while
            vec_strings->push_back("while");
            whileAndIfCondition(str, vec_strings); //splitting the while condition
            getline(input, str);
            while (str.find('}') == -1) {
                if(str.at(0) == '\t')
                    splitStringsToVector(str, vec_strings, '\t', 0);
                else
                {
                    firstNoSpace = str.find_first_not_of(' ', 0);
                    str = str.substr(firstNoSpace);
                    noWhileAndIfReplace(str);
                    splitStringsToVector(str, vec_strings, delimiter_as_char, -1);
                }
                getline(input, str);
            }
            vec_strings->push_back("}"); //putting { into the vector to know the end of the while loop
        } else if(strcmp(str.substr(0, 3).c_str(), "if ") == 0) {
            str = str.substr(3); //if condition without the word if
            vec_strings->push_back("if");
            whileAndIfCondition(str, vec_strings); //splitting the if condition
            getline(input, str);
            while (str.find('}') == -1) {
                if(str.at(0) == '\t')
                    splitStringsToVector(str, vec_strings, '\t', 0);
                else
                {
                    firstNoSpace = str.find_first_not_of(' ', 0);
                    str = str.substr(firstNoSpace);
                    noWhileAndIfReplace(str);
                    splitStringsToVector(str, vec_strings, delimiter_as_char, -1);
                }
                getline(input, str);
            }
            vec_strings->push_back("}"); //putting { into the vector to know the end of the if condition
        } else {
            noWhileAndIfReplace(str);
            splitStringsToVector(str, vec_strings, delimiter_as_char, -1);
        }
    }
    return vec_strings;
}

/*
 * This function was taken from StackOverFlow.
 *
 * The function receives three string arguments (str, toReplace and replacing),
 * and its purpose is to replace all toReplace occurrences in the str string by
 * the string called replacing.
 */
void Lexer::replaceAll(string &str, const string &toReplace, const string &replacing) {
    if (toReplace.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(toReplace, start_pos)) != string::npos) {
        str.replace(start_pos, toReplace.length(), replacing);
        // In case 'toReplace' contains 'replacing', like replacing 'x' with 'yx'
        start_pos += replacing.length();
    }
}

/*
 * This function does the correspondent replaces in a line of the txt file that
 * is not part of a while loop.
 */
void Lexer::noWhileAndIfReplace(string &str) {
    int simAndParenthesis = str.find("sim("); //finding "sim(" in str
    string afterReplace, beforeSimAndParenthesis;
    if (simAndParenthesis != -1) { //if "sim(" is in str
        /*
         * Both afterReplace and beforeSimAndParenthesis are a copy of everything
         * that is before "sim(" in str. We only do the correspondent replacement
         * in afterReplace and then we replace the occurrence of beforeSimAndParenthesis
         * in str by the string afterReplace.
         */
        afterReplace = str.substr(0, simAndParenthesis); //
        beforeSimAndParenthesis = str.substr(0, simAndParenthesis);
        //replacing all spaces before "sim(" by the char '|' in the string called afterReplace
        replaceAll(afterReplace, " ", delimiter_as_string);
        replaceAll(str, beforeSimAndParenthesis, afterReplace);
        replaceAll(str, delimiterSimParenthesisQuote, delimiter_as_string);
    }
    if (str.find("var") != -1) {
        replaceAll(str, "var ", varAndDelimiter);
    }
    if(str.find("Print(") == -1)
    {
        replaceAll(str, quoteAndComma, delimiter_as_string);
        replaceAll(str, parenthesisAndQuote, delimiter_as_string);
        replaceAll(str, quoteAndParenthesis, delimiter_as_string);
    } else {
        replaceAll(str, quoteAndParenthesis, quote);
        replaceAll(str, parenthesisAndQuote, delimiterAndQuote);
    }

    /*
     * Different situations of the char '='.
     * The char '=' could be joined by a space before, after
     * or before and after. We check every situation to do the
     * correspondent replacement to then split the string to
     * vectors.
     */
    if (str.find(" = ") != -1)
        replaceAll(str, " = ", equalBetweenDelimiters);
    else if (str.find(" =") != -1)
        replaceAll(str, " =", equalBetweenDelimiters);
    else if (str.find("= ") != -1)
        replaceAll(str, "= ", equalBetweenDelimiters);
    else if (str.find('=') != -1)
        replaceAll(str, "=", equalBetweenDelimiters);
    else {
        replaceAll(str, "(", delimiter_as_string);
        replaceAll(str, ")", delimiter_as_string);
    }
}

/*
 * Using code from thispointer.com to split to vectors.
 *
 * This function is for splitting a string to vectors. We have a
 * delimiter which tell us how to separate the string. Also we have
 * a flag which has 2 cases. In case flag is -1, we know that we need
 * to split a string that is not part of a while loop; else, we need to
 * do a split of a string that is part of a while loop.
 */
void Lexer::splitStringsToVector(const string &str, vector<string> *vec_str, char delimiter, int flag) {
    string strSplit;
    istringstream splitterStream(str);
    if (flag == -1) {
        while (getline(splitterStream, strSplit, delimiter)) {
            vec_str->push_back(strSplit);
        }
    } else {
        while (getline(splitterStream, strSplit, delimiter)) {
            if (flag % 2 == 1) { //getting the lines of the while loop
                noWhileAndIfReplace(strSplit);
                splitStringsToVector(strSplit, vec_str, delimiter_as_char, -1);
            }
            flag++;
        }
    }

}

/*
 * This function correspond to the while condition.
 * For each operand we have different situations of the
 * operand. The operand could be joined by a space before, after
 * or before and after. We check every situation to do the
 * correspondent replacement, and then we split the string to vectors.
 */
void Lexer::whileAndIfCondition(string str, vector<string> *strings) {
    if (str.find("==") != -1) {
        if (str.find(" == ") != -1)
            replaceAll(str, " == ", doubleEqualBetweenDelimiters);
        else if (str.find(" ==") != -1)
            replaceAll(str, " ==", doubleEqualBetweenDelimiters);
        else if (str.find("== ") != -1)
            replaceAll(str, "== ", doubleEqualBetweenDelimiters);
        else //if(str.find("==") != -1)
            replaceAll(str, "==", doubleEqualBetweenDelimiters);
    } else if (str.find("!=") != -1) {
        if (str.find(" != ") != -1)
            replaceAll(str, " != ", differentBetweenDelimiters);
        else if (str.find(" !=") != -1)
            replaceAll(str, " !=", differentBetweenDelimiters);
        else if (str.find("!= ") != -1)
            replaceAll(str, "!= ", differentBetweenDelimiters);
        else //if(str.find("!=") != -1)
            replaceAll(str, "!=", differentBetweenDelimiters);
    } else if (str.find("<=") != -1) {
        if (str.find(" <= ") != -1)
            replaceAll(str, " <= ", lessOrEqualBetweenDelimiters);
        else if (str.find(" <=") != -1)
            replaceAll(str, " <=", lessOrEqualBetweenDelimiters);
        else if (str.find("<= ") != -1)
            replaceAll(str, "<= ", lessOrEqualBetweenDelimiters);
        else //if(str.find("<=") != -1)
            replaceAll(str, "<=", lessOrEqualBetweenDelimiters);
    } else if (str.find('<') != -1) {
        if (str.find(" < ") != -1)
            replaceAll(str, " < ", lessBetweenDelimiters);
        else if (str.find(" <") != -1)
            replaceAll(str, " <", lessBetweenDelimiters);
        else if (str.find("< ") != -1)
            replaceAll(str, "< ", lessBetweenDelimiters);
        else //if(str.find("<") != -1)
            replaceAll(str, "<", lessBetweenDelimiters);
    } else if (str.find(">=") != -1) {
        if (str.find(" >= ") != -1)
            replaceAll(str, " >= ", biggerOrEqualBetweenDelimiters);
        else if (str.find(" >=") != -1)
            replaceAll(str, " >=", biggerOrEqualBetweenDelimiters);
        else if (str.find(">= ") != -1)
            replaceAll(str, ">= ", biggerOrEqualBetweenDelimiters);
        else //if(str.find(">=") != -1)
            replaceAll(str, ">=", biggerOrEqualBetweenDelimiters);
    } else if (str.find('>') != -1) {
        if (str.find(" > ") != -1)
            replaceAll(str, " > ", biggerBetweenDelimiters);
        else if (str.find(" >") != -1)
            replaceAll(str, " >", biggerBetweenDelimiters);
        else if (str.find("> ") != -1)
            replaceAll(str, "> ", biggerBetweenDelimiters);
        else //if(str.find(">") != -1)
            replaceAll(str, ">", biggerBetweenDelimiters);
    }
    if (str.find(" { ") != -1)
        replaceAll(str, " { ", delimiterAndOpenBracket);
    else if (str.find(" {") != -1)
        replaceAll(str, " {", delimiterAndOpenBracket);
    else if (str.find("{ ") != -1)
        replaceAll(str, "{ ", delimiterAndOpenBracket);
    else //if(str.find("{") != -1)
        replaceAll(str, "{", delimiterAndOpenBracket);
    splitStringsToVector(str, strings, delimiter_as_char, -1);
}