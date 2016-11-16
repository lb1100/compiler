#ifndef ERROR_H
#define ERROR_H

#include "header.h"

using namespace std;
extern int error_count;
const int MAX_ERROR_MESSAGE = 100;
namespace Error{
    const string Error_message[MAX_ERROR_MESSAGE] = {
        "Exceed int range ", // 0
        "Leading zero", // 1
        "Alpha after number", // 2
        "Invalid char", // 3
        "Invalid char in string", //4
        "Invalid operator", //5
        "No type found", // 6
        "Operator = not found", //7
        "No number", //8
        "Need a char", // 9
        "Need an identifier", //10
        "Need a simicolon", //11
        "Need a lparent", //12
        "Need a rparent", //13
        "Need a left brace", //14
        "Need a right brace", //15

        "No main", //16
        "Main should be void", //17
        "Source coid should end here", //18

        "Unkown statement" , //19
        "There shouldn't be return" , //20
        "There should be a constant number/char", //21
        "Need a colon", //22
        "Invalid identifier", //23
        "There is nothing to printf", //24

        "Need a right bracket", //25
        "Need a assignment", //26
        "Array index <= zero", //27
    };
    const int EXCEED_INT_RANGE = 0;
    const int LEADING_ZERO = 1;
    const int ALPHA_AFTER_NUM = 2;
    const int INVALID_CHAR = 3;
    const int INVALID_CHAR_IN_STRING = 4;
    const int INVALID_OPERATOR = 5;
    const int NO_TYPE_FOUND = 6;
    const int EQUAL_NOT_FOUND = 7;
    const int NO_NUMBER = 8;
    const int CHAR_NEEDED = 9;
    const int NO_IDENT = 10;
    const int NO_SIMICOLON = 11;
    const int NO_LPARENT = 12;
    const int NO_RPARENT = 13;
    const int NO_LBRACE = 14;
    const int NO_RBRACE = 15;
    const int NO_MAIN = 16;
    const int MAIN_NOT_VOID = 17;
    const int SHOULD_END = 18;
    const int UNKNOWN_STATEMENT = 19;
    const int NO_RETURNS = 20;
    const int NO_CONSTANT = 21;
    const int NO_COLON = 22;
    const int INVALID_IDENT = 23;
    const int NO_PRINT = 24;
    const int NO_RBRACKET = 25;
    const int NO_ASSIGN = 26;
    const int ARRAY_BOUND_ERROR = 27;
}



namespace Fatal{
    const int NO_SOURCE_FILE = 0;
    const int NO_SUCH_FILE = 1;

    const string fatal_message[MAX_ERROR_MESSAGE] = {
        "No source file provided!",  // 0
        "No such file!" // 1
    };
}


void error(int );
void fatal(int );

#endif // ERROR_H
