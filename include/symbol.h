#ifndef SYMBOL_HPP_INCLUDED
#define SYMBOL_HPP_INCLUDED

#include "header.h"
#include "error.h"
using namespace std;

extern set<string> reserved_word;
extern map<string, int> reserved_word_to_int;

namespace Type{

const string type_message[] = {
    "error", // 0
    "unsigned_num", // 1
    "num", // 2
    "char", // 3
    "string", //4
    // operator
    "plus\t\t+", // 5
    "minux\t\t-", // 6
    "multiply\t*", //7
    "div\t\t/", // 8
    "assign\t\t=", //9

    // cmp operator
    "eql\t\t==", // 10
    "greater\t>", // 11
    "less\t\t<", //12
    "greater_equal\t>=", // 13
    "less_equal\t<=", //14
    "not_equal\t!=",  //15

    // symbol
    "left_parenthesis\t(", // 16
    "right_parenthesis\t)", // 17
    "left_bracket\t[", //18
    "right_bracket\t]", //19
    "left_brace\t{", //20
    "right_brace\t}", //21
    "comma\t\t,", //22
    "simicolon\t;", //23
    "colon\t\t:", // 24

    "identifier", //25
    "reserved_word", //26
};

const int ERROR = 0;
const int U_NUM = 1;
const int NUM = 2;
const int CHAR = 3;
const int STRING = 4;

const int PLUS = 5;
const int MINUS = 6;
const int MULTIPLY = 7;
const int DIV = 8;
const int ASSIGN = 9;

const int EQUAL = 10;
const int GREATER = 11;
const int LESS = 12;
const int GREATER_EQUAL = 13;
const int LESS_EQUAL = 14;
const int NOT_EQUAL = 15;

const int LPARENT = 16;
const int RPARENT = 17;
const int LBRACKET = 18;
const int RBRACKET = 19;
const int LBRACE = 20;
const int RBRACE = 21;
const int COMMA = 22;
const int SIMICOLON = 23;
const int COLON = 24;

const int IDENT = 25;
const int RESERVED = 26;

enum RESERVED{
    casesym, charsym, constsym, defaultsym, ifsym,
    intsym, mainsym, printfsym, returnsym, scanfsym,
    switchsym, voidsym, whilesym
};
void init();

}


const int MAX_BUFFER_LENGTH = 256;

class Symbol{
public:
    int symbol;
    string name;
    int reserved_type;
    int num;
    char chr;
    bool eof;
    //bool with_operator;
    Symbol();
    void setUp(const char* );
    bool getNextSymbol();
    virtual ~Symbol();
private:
    char buffer[MAX_BUFFER_LENGTH];
    int n, cur;
    char ch;
    ifstream *fin;
    char text[MAX_BUFFER_LENGTH];
    const static long long maxint = 1LL << 32;

    inline void getch();
    inline void getNewLine();
    inline void skip(char);
    inline int read_num();
};




#endif // SYMBOL_HPP_INCLUDED
