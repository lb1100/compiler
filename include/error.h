#ifndef ERROR_H
#define ERROR_H

#include "header.h"

using namespace std;
extern int error_count;
const int MAX_ERROR_MESSAGE = 100;
namespace Error{
    const string Error_message[MAX_ERROR_MESSAGE] = {
        "Exceed int range !", // 0
        "Leading zero", // 1
        "Alpha after number", // 2
        "Invalid char", // 3
        "Invalid char in string", //4
        ""
    };
    const int EXCEED_INT_RANGE = 0;
    const int LEADING_ZERO = 1;
    const int ALPHA_AFTER_NUM = 2;
    const int INVALID_CHAR = 3;
    const int INVALID_CHAR_IN_STRING = 4;
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
