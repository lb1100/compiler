#include "symbol.h"

using namespace std;
Symbol::Symbol()
{
}

Symbol::~Symbol()
{
    //dtor
}

void Symbol::getNewLine(){
    if (! fin->getline(buffer, 256)){
        ch = EOF;
        eof = true;
        return;
    }
    //cout <<"***" << buffer << endl;
    int n = strlen(buffer);
    buffer[n] = buffer[n+1] = ' ';
    buffer[n+2] = 0;
    cur = 0;
    ch = buffer[0];

}

void Symbol::setUp(const char* src){
    eof = false;
    if (src == NULL)
        fatal(Fatal::NO_SOURCE_FILE);
    fin = new ifstream(src, ios::in);
    if (!fin->is_open()){
        // no such file
        fatal(Fatal::NO_SUCH_FILE);
    }
    getNewLine();
    //getch();
}

void Symbol::getch(){
    if (ch == EOF) return;
    cur ++;
    if (!buffer[cur]){
        // process next line
        getNewLine();
        if (ch == EOF){
            eof = true;
            return;
        }

        //cur ++;
    }
    ch = buffer[cur];
}



void Symbol::skip(char chr=' '){
    do {
        getch();
    } while(ch!=' ' && ch!='\t' && chr!=ch);
}

int Symbol::read_num(){
    long long num;
    num = ch - '0';
    getch();
    if (num == 0 && isdigit(ch)) {
        error(Error::LEADING_ZERO);
        skip();
    }
    while(isdigit(ch)){
        num = num*10 + ch - '0';
        if (!is_uint(num)) {
            error(Error::EXCEED_INT_RANGE);
            skip();
            num = -1;
            break;
        }
        getch();
    }
    if (isalpha(ch)){
        error(Error::ALPHA_AFTER_NUM);
        skip();
    }
    return num;
}

bool Symbol::getNextSymbol(){
    while (ch == ' ' || ch == '\t')
        getch();
    // false --> EOF
    if (ch==EOF){
        eof = true;
        return false;
    }
    symbol = Type::ERROR;
    reserved_type = 0;
    /*
    if (ch == '+' || ch == '-'){
        int sgn = ch == '+' ? 1 : -1;
        with_operator = true;
        while (ch <= ' ' || ch <= '\t')
            getch();
        if (isdigit(ch)){
            num = read_num(sgn);
        } else {
            symbol = ch == '+' ? Type::PLUS : Type::MINUS;
            getch();
        }
        return true;
    }else
        with_operator = false;
    */

    if (isdigit(ch)){
        num = read_num();
        if (num>=0)
            symbol = num ? Type::U_NUM : Type::NUM;
        return true;
    }

    if (ch == '\''){
        getch();
        chr = ch;


        getch();
        if (ch == '\'') {
            if (!is_char(chr))
                error(Error::INVALID_CHAR);
            else{
                symbol = Type::CHAR;
                getch();
            }
        } else {
            skip('\'');
            getch();
        }
        return true;
    }

    if (ch == '\"'){
        int count = 0;
        getch();
        while(ch != '\"') {
            if (!in_string(ch)) {
                error(Error::INVALID_CHAR_IN_STRING);
                skip('\"');
                getch();
                return true;
            }
            text[count ++] = ch;
            getch();
        }
        text[count] = 0;
        name = text;
        symbol = Type::STRING;
        getch();
        return true;
    }

    if (ch == '+' || ch == '-') {
        symbol = ch == '+' ? Type::PLUS : Type::MINUS;
        getch();
        return true;
    }

    if (ch == '*' || ch == '/') {
        symbol = ch == '*' ? Type::MULTIPLY : Type::DIV;
        getch();
        return true;
    }

    if (ch == '='){
        getch();
        if (ch == '='){
            symbol = Type::EQUAL;
            getch();
        }else{
            symbol = Type::ASSIGN;
        }

        return true;
        return true;
    }

    if (ch == '<') {
        getch();
        if (ch == '='){
            symbol = Type::LESS_EQUAL;
            getch();
        }else{
            symbol = Type::LESS;
        }
        return true;
    }

    if (ch == '>') {
        getch();
        if (ch == '='){
            symbol = Type::GREATER_EQUAL;
            getch();
        }else{
            symbol = Type::GREATER;
        }
        return true;
    }

    if (ch == '!'){
        getch();
        if (ch == '='){
            symbol = Type::NOT_EQUAL;
            getch();
        }else
            error(Error::INVALID_CHAR);
        return true;
    }

    if (ch == '(' || ch == ')'){
        symbol = ch == '(' ? Type::LPARENT : Type::RPARENT;
        getch();
        return true;
    }

    if (ch == '[' || ch == ']'){
        symbol = ch == '[' ? Type::LBRACKET : Type::RBRACKET;
        getch();
        return true;
    }

    if (ch == '{' || ch == '}'){
        symbol = ch == '{' ? Type::LBRACE : Type::RBRACE;
        getch();
        return true;
    }

    if (ch==','){
        symbol = Type::COMMA;
        getch();
        return true;
    }

    if (ch == ';') {
        symbol = Type::SIMICOLON;
        getch();
        return true;
    }

    if (ch == ':') {
        symbol = Type::COLON;
        getch();
        return true;
    }

    if (isalpha(ch) || ch=='_'){
        int count = 0;
        do {
            text[count++] = ch;
            getch();
        }while(is_ident_char(ch));
        text[count] = 0;
        name = text;

        if (reserved_word.count(name)){
            symbol = Type::RESERVED;
            reserved_type = reserved_word_to_int[name];
        }
        else
            symbol = Type::IDENT;

        return true;
    }

    error(Error::INVALID_CHAR);
    return true;
}



namespace Type{

void init(){
    reserved_word.clear();

    reserved_word.insert("const");
    reserved_word.insert("int");
    reserved_word.insert("char");
    reserved_word.insert("void");
    reserved_word.insert("main");
    reserved_word.insert("if");
    reserved_word.insert("while");
    reserved_word.insert("switch");
    reserved_word.insert("case");
    reserved_word.insert("default");
    reserved_word.insert("scanf");
    reserved_word.insert("printf");
    reserved_word.insert("return");

    int num = 0;
    for(auto x : reserved_word) {
        reserved_word_to_int[x] = num ++;
    }


    //cout << reserved_word.size() << endl;
}

}
