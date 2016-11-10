#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <ctype.h>
#include <algorithm>
#include <set>


using namespace std;

const long long max_uint = 1LL << 32;
const long long max_int = 1LL << 31;

inline bool is_uint(long long s){
    return s <= max_uint;
}
inline bool is_int(long long s){
    return s>= - max_int && s < max_int;
}

inline bool is_char(char ch){
    return ch == '_' || isalpha(ch) || isdigit(ch) || ch == '+'
     || ch == '-' || ch == '*' || ch == '/';
}

inline bool in_string(char ch){
    return ch>=32 && ch<=126 && ch!=33;
}

inline bool is_ident_char(char ch){
    return isalpha(ch) || isdigit(ch) || ch == '_';
}

#endif // HEADER_H_INCLUDED
