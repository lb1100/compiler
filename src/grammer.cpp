#include "grammer.h"
using namespace std;

Grammer::Grammer()
{
    //ctor
    sym = 0;
}

Grammer::~Grammer()
{
    //dtor
}

void Grammer::set_sym(Symbol* sym){
    this->sym = sym;
}

void Grammer::num(){ // the second +/- or u_num
    int sgn=1;
    if (sym->symbol == Type::PLUS || sym->symbol == Type::MINUS) {
        sgn = sym->symbol == Type::PLUS ? 1 : -1;
        sym -> getNextSymbol();
    }
    if (sym -> symbol != Type::U_NUM){
        if (sym->symbol == Type::PLUS || sym->symbol == Type::MINUS)
            error(Error::INVALID_OPERATOR);
        else
            error(Error::NO_NUMBER);
    }else{
        number = sgn * (long long)sym->num;
        if (!::is_int(number)) {
            error(Error::EXCEED_INT_RANGE);
            number = 0;
        }
    }
    sym -> getNextSymbol();
}

void Grammer::const_dec(){
    while(sym -> symbol == Type::RESERVED &&
        sym->reserved_type == Type::constsym){

        sym -> getNextSymbol();

        // type
        if (!is_type()){
            error(Error::NO_TYPE_FOUND);

            #ifdef CHECK
            skip();
            fprintf(stderr,"not implement\n");
            #endif
        }
        int type = sym -> reserved_type == Type::intsym;
        #ifdef CHECK
        fprintf(stderr,"not implement\n");
        // type specify
        #endif
        sym -> getNextSymbol();

        // indent
        string id = sym -> name;
        sym -> getNextSymbol();
        if (sym -> symbol != Type::ASSIGN){
            error(Error::EQUAL_NOT_FOUND);
        }
        sym -> getNextSymbol();
        if (type){ // int
            num();
            #ifdef CHECK
            fprintf(stderr,"not implement\n");
            // id = number
            #endif

            #ifdef GRAMMER_DEBUG
            cout << "const dec:"  << id << "=" << number << endl;
            #endif
        }else{
            if (sym -> symbol != Type::CHAR){
                error(Error::CHAR_NEEDED);
            }
            #ifdef CHECK
            fprintf(stderr,"not implement\n");
            // id = sym->char
            #endif

            #ifdef GRAMMER_DEBUG
            cout << "const dec:"  << id << "= \'" << sym->chr << "\'" << endl;
            #endif
            sym -> getNextSymbol();
        }

        while (sym -> symbol == Type::COMMA) {
            sym -> getNextSymbol();
            if (sym -> symbol != Type::IDENT){
                error(Error::NO_IDENT);
            }

            string id = sym -> name;
            sym -> getNextSymbol();
            if (sym -> symbol != Type::ASSIGN){
                error(Error::EQUAL_NOT_FOUND);
            }

            sym -> getNextSymbol();
            if (type){ // int
                num();
                #ifdef CHECK
                fprintf(stderr,"not implement\n");
                // id = number
                #endif

                #ifdef GRAMMER_DEBUG
                cout << "const dec:"  << id << "=" << number << endl;
                #endif
            }else{
                if (sym -> symbol != Type::CHAR){
                    error(Error::CHAR_NEEDED);

                }
                #ifdef CHECK
                //skip();
                fprintf(stderr,"not implement\n");
                // id = sym->char
                #endif

                #ifdef GRAMMER_DEBUG
                cout << "const dec:"  << id << "= \'" << sym->chr << "\'" << endl;
                #endif
                sym -> getNextSymbol();
            }
        }

        if (sym -> symbol != Type::SIMICOLON){
            error(Error::NO_SIMICOLON);
        }
        sym -> getNextSymbol();
    }
}

void Grammer::var_dec(){ // first var name in this->name, type in this->is_int, xx[ or xx,
    bool isarray = false;
    int array_num;
    if (sym -> symbol == Type::LBRACKET){
        sym -> getNextSymbol();
        isarray = true;
        num();
        array_num = number;
        if (number <= 0){
            error(Error::ARRAY_BOUND_ERROR);
        }
        if (sym -> symbol != Type::RBRACKET) {
            error(Error::NO_RBRACKET);
        }
        sym -> getNextSymbol();
    }
    #ifdef CHECK
    fprintf(stderr, "not implement\n");
    // declare name, int
    #endif

    #ifdef GRAMMER_DEBUG
    cout << "var dec : " << (is_int ? "int" : "char") << " " << name ;
    if (isarray) {
        cout << "[" << array_num << "]";
    }
    cout << endl;
    #endif
    //sym -> getNextSymbol();

    while(sym -> symbol == Type::COMMA){ // ,
        sym -> getNextSymbol();

        if (sym -> symbol != Type::IDENT){
            error(Error::NO_IDENT);
        }
        this -> name = sym -> name;

        isarray = false;
        if (sym -> symbol == Type::LBRACKET){
            sym -> getNextSymbol();
            isarray = true;
            num();
            array_num = number;
            if (number <= 0){
                error(Error::ARRAY_BOUND_ERROR);
            }
            if (sym -> symbol != Type::RBRACKET) {
                error(Error::NO_RBRACKET);
            }
            sym -> getNextSymbol();
        }
        #ifdef CHECK
        fprintf(stderr, "not implement\n");
        // declare name, int
        #endif

        cout << "var dec : " << (is_int ? "int" : "char") << " " << name ;
        if (isarray) {
            cout << "[" << array_num << "]";
        }
        cout << endl;
        sym -> getNextSymbol();
    }

    if (sym -> symbol != Type::SIMICOLON){
        error(Error::NO_SIMICOLON);
    } else
        sym -> getNextSymbol();
}

void Grammer::args_dec(){ // args declare

    if (sym -> symbol == Type::RPARENT){
        sym -> getNextSymbol();
        return;
    }
    if (!is_type()) {
        error(Error::NO_TYPE_FOUND);
    }
    is_int = sym->reserved_type == Type::intsym;
    sym -> getNextSymbol();
    if (sym -> symbol != Type::IDENT) {
        error(Error::NO_IDENT);
    }

    #ifdef CHECK
    fprintf(stderr, "not implement\n");
    #endif

    #ifdef GRAMMER_DEBUG
    cout << "parmeter: " << (is_int ? "int" : "char") << " " << sym->name << endl;
    #endif
    sym -> getNextSymbol();
    while(sym -> symbol == Type::COMMA){
        sym -> getNextSymbol();

        if (!is_type()) {
            error(Error::NO_TYPE_FOUND);
        }
        is_int = sym->reserved_type == Type::intsym;
        sym -> getNextSymbol();
        if (sym -> symbol != Type::IDENT) {
            error(Error::NO_IDENT);
        }

        #ifdef CHECK
        fprintf(stderr, "not implement\n");
        #endif

        #ifdef GRAMMER_DEBUG
        cout << "parmeter: " << (is_int ? "int" : "char") << " " << sym->name << endl;
        #endif
        sym -> getNextSymbol();
    }

    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();
}

void Grammer::args_list(){ // xxx(
    if (sym -> symbol == Type::RPARENT){
        sym -> getNextSymbol();
        return;
    }
    int num = 0;
    expr();
    num ++;
    #ifdef GRAMMER_DEBUG
    cout << "args_list : expr "  << num <<endl;
    #endif

    while(sym -> symbol == Type::COMMA){
        sym -> getNextSymbol();
        expr();
        #ifdef GRAMMER_DEBUG
        cout << "arg list expr " << num <<endl;
        #endif
    }
    cout << endl;
    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    #ifdef GRAMMER_DEBUG
        cout << "arg list end " << endl;
    #endif
    sym -> getNextSymbol();
}

void Grammer::expr(){
    level++;
    int num = 0;
    if (sym -> symbol == Type::PLUS || sym -> symbol == Type::MINUS){
        #ifdef GRAMMER_DEBUG
        OUT();cout << "expr " << (sym -> symbol == Type::PLUS ? "+" : "-")  << endl;
        #endif
        sym -> getNextSymbol();
    }
    term();
    num++;
    #ifdef GRAMMER_DEBUG
    OUT();cout << "expr t" << num  << endl;
    #endif
    while (sym -> symbol == Type::PLUS || sym -> symbol == Type::MINUS) {
        bool plus = sym -> symbol == Type::PLUS;
        sym -> getNextSymbol();
        term();
        #ifdef GRAMMER_DEBUG
        OUT();cout << "expr " << (plus?"+":"-")  << " t" << num  << endl;
        #endif
    }
    level--;
}

void Grammer::term(){
    level ++;
    int num = 0;
    factor();
    num ++;
    #ifdef GRAMMER_DEBUG
    OUT();cout << "term f" << num << endl;
    #endif
    while(sym -> symbol == Type::MULTIPLY || sym -> symbol == Type::DIV){
        bool mul = sym -> symbol == Type::MULTIPLY;
        sym -> getNextSymbol();
        factor();
        num++;
        #ifdef GRAMMER_DEBUG
        OUT();cout << "term " << (mul ? "*" : "/") << " f" << num << endl;
        #endif
    }
    level--;
}

void Grammer::factor(){
    // signed number
    if (sym -> symbol == Type::PLUS || sym -> symbol == Type::MINUS){
        num();
        #ifdef GRAMMER_DEBUG
        OUT();cout << "factor " << number << endl;
        #endif
        sym -> getNextSymbol();
        return ;
    }

    // number
    if (sym -> symbol == Type::U_NUM || sym -> symbol == Type::NUM){
        #ifdef GRAMMER_DEBUG
        OUT();cout << "factor " << sym->num << endl;
        #endif
        this -> number = sym -> num;
        sym -> getNextSymbol();
        return ;
    }

    // char
    if (sym -> symbol == Type::CHAR){
        #ifdef GRAMMER_DEBUG
        OUT();cout << "factor " << sym->chr << endl;
        #endif
        this -> number = sym -> chr;
        sym -> getNextSymbol();
        return ;
    }

    // ident
    if (sym -> symbol == Type::IDENT){
        string name_x = sym -> name;
        sym -> getNextSymbol();
        if (sym -> symbol == Type::LPARENT){ //call
            call();
            OUT();cout << "factor __call " << name_x << endl;
        } else if (sym -> symbol == Type::LBRACKET) { // x[
            sym -> getNextSymbol();
            expr();
            if (sym -> symbol != Type:: RBRACKET) {
                error(Error::NO_RBRACKET);
            }
            #ifdef GRAMMER_DEBUG
            OUT();cout << "factor " << name_x << "[expr]" << endl;
            #endif
            sym -> getNextSymbol();
        } else {
            #ifdef GRAMMER_DEBUG
            OUT();cout << "factor " << name_x << endl;
            #endif
            //sym -> getNextSymbol();
            return;
        }
    }
}

void Grammer::condition(){
    int oper;
    expr();
    if (sym -> symbol >= Type::EQUAL && sym -> symbol <= Type::NOT_EQUAL){
        oper = sym -> symbol;
        sym -> getNextSymbol();
    } else {
        #ifdef GRAMMER_DEBUG
        cout << "condition : expr" << endl;
        #endif
        return;
    }
    expr();

    #ifdef GRAMMER_DEBUG
    string s = Type :: type_message[oper];
    int i;
    for(i=s.length(); s[i]!='\t'; i--);
    s = s.substr(i+1,s.length() - i - 1);
    cout << "condition : exprA " << s << " exprB" << endl;
    #endif
}

void Grammer::if_dec(){ // if
    #ifdef GRAMMER_DEBUG
    cout << "if dec " << endl;
    #endif
    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();

    condition();

    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();

    statement();
    #ifdef GRAMMER_DEBUG
    cout << "if dec end" << endl;
    #endif
}

void Grammer::while_dec(){
    #ifdef GRAMMER_DEBUG
    cout << "while dec:" << endl;
    #endif
    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();
    condition();
    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();
    statement();
    #ifdef GRAMMER_DEBUG
    cout << "while end:" << endl;
    #endif
}

void Grammer::call(){ // xxx(
    #ifdef GRAMMER_DEBUG
    cout << "call " << this->name << endl;
    #endif
    sym->getNextSymbol();
    args_list();
}

void Grammer::read_dec(){ // scanf
    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::IDENT){
        error(Error::NO_IDENT);
    }
    #ifdef GRAMMER_DEBUG
    cout << "scanf " << sym -> name << endl;
    #endif
    sym -> getNextSymbol();

    while(sym->symbol == Type::COMMA){
        sym -> getNextSymbol();
        if (sym -> symbol != Type::IDENT){
            error(Error::NO_IDENT);
        }
        #ifdef GRAMMER_DEBUG
        cout << "scanf " << sym -> name << endl;
        #endif
        sym -> getNextSymbol();
    }

    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::SIMICOLON){
        error(Error::NO_SIMICOLON);
    }
    sym -> getNextSymbol();
}

void Grammer::write_dec(){ // printf
    int flg = 0;
    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol == Type::STRING){
        #ifdef GRAMMER_DEBUG
        cout << "printf \"" << sym -> name << "\" " <<  endl;
        #endif
        sym -> getNextSymbol();
        flg = 1;
    }

    if (sym -> symbol != Type::RPARENT){
        if (flg){
            if (sym -> symbol != Type::COMMA){
                error(Error::NO_COMMA);
            }
            sym -> getNextSymbol();
        }
        expr();
        #ifdef GRAMMER_DEBUG
        cout << "printf " << "expr" <<  endl;
        #endif
        flg = 1;
        //sym -> getNextSymbol();
    }

    if (sym -> symbol == Type::RPARENT){
        if (!flg){
            error(Error::NO_PRINT);
        }
        sym -> getNextSymbol();
    } else {
        error(Error::NO_RPARENT);
    }

    if (sym -> symbol != Type::SIMICOLON){
        error(Error::NO_SIMICOLON);
    }
    sym -> getNextSymbol();
}

void Grammer::switch_dec(){ //switch
    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();
    expr();
    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::LBRACE){
        error(Error::NO_LBRACE);
    }
    sym -> getNextSymbol();

    while(sym -> symbol == Type::RESERVED &&
        sym -> reserved_type == Type::casesym){
        sym -> getNextSymbol();
        if (sym -> symbol == Type::CHAR) {
            #ifdef GRAMMER_DEBUG
            cout << "case " << sym -> chr << " " << endl;
            #endif
            sym -> getNextSymbol();
        } else if (sym -> symbol == Type::PLUS || sym -> symbol == Type::MINUS){
            num();
            #ifdef GRAMMER_DEBUG
            cout << "case  " << this->number << endl;
            #endif
        } else if (sym -> symbol == Type::U_NUM){
            #ifdef GRAMMER_DEBUG
            cout << "case " << sym->num << endl;
            #endif
            sym -> getNextSymbol();
        } else {
            error(Error::NO_CONSTANT);
        }

        if (sym -> symbol != Type::COLON){
            error(Error::NO_COLON);
        }
        sym -> getNextSymbol();

        statement();
    }

    //default
    if (sym -> symbol == Type::RESERVED &&
        sym -> reserved_type == Type::defaultsym){
        sym -> getNextSymbol();

        if (sym -> symbol != Type::COLON){
            error(Error::NO_COLON);
        }
        sym -> getNextSymbol();

        statement();
    }

    if (sym -> symbol != Type::RBRACE){
        error(Error::NO_RBRACE);
    }
    sym -> getNextSymbol();
}

void Grammer::return_dec(){ // 0 no return , 1 return (xxx), 2 return;
    if (return_flg == 0){
        error(Error::NO_RETURNS);
    } else if (return_flg == 1){
        if (sym -> symbol != Type::LPARENT){
            error(Error::NO_LPARENT);
        }
        sym -> getNextSymbol();
        expr();
        #ifdef GRAMMER_DEBUG
        cout << "return expr" << endl;
        #endif
        if (sym -> symbol != Type::RPARENT){
            error(Error::NO_RPARENT);
        }
        sym -> getNextSymbol();
        if (sym -> symbol != Type::SIMICOLON){
            error(Error::NO_SIMICOLON);
        }
        sym -> getNextSymbol();
    } else if (return_flg == 2){
        //sym -> getNextSymbol();
        #ifdef GRAMMER_DEBUG
        cout << "return " << endl;
        #endif
        if (sym -> symbol != Type::SIMICOLON){
            error(Error::NO_SIMICOLON);
        }
        sym -> getNextSymbol();
    }
}

void Grammer::statement(){
    // if
    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::ifsym){
        sym -> getNextSymbol();
        if_dec();
        return ;
    }

    // while

    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::whilesym){
        sym -> getNextSymbol();
        while_dec();
        return ;
    }

    // statements
    if (sym -> symbol == Type::LBRACE) { // {
        sym -> getNextSymbol();
        statements();
        if (sym -> symbol != Type::RBRACE) {
            error(Error::NO_RBRACE);
        }
        sym -> getNextSymbol();

        return;
    }


    if (sym -> symbol == Type::IDENT){
        //call
        string name_x;
        name_x = sym -> name;
        this -> name = sym -> name;
        sym -> getNextSymbol();
        if (sym -> symbol == Type::LPARENT){ // call
            call();
            if (sym -> symbol != Type::SIMICOLON){
                error(Error::NO_SIMICOLON);
            }
            sym -> getNextSymbol();

        } else if (sym -> symbol == Type::ASSIGN){//assignment x=
            sym -> getNextSymbol();
            expr();
            #ifdef GRAMMER_DEBUG
            cout << "assignment " << name_x << " =  expr" << endl;
            #endif
            if (sym -> symbol != Type::SIMICOLON){
                error(Error::NO_SIMICOLON);
            }
            sym ->getNextSymbol();
        } else if (sym -> symbol == Type::LBRACKET){//assignment x[a]=
            sym -> getNextSymbol();
            expr();
            if (sym -> symbol != Type::RBRACKET){
                error(Error::NO_RBRACKET);
            }
            sym -> getNextSymbol();
            if (sym -> symbol != Type::ASSIGN){
                error(Error::NO_ASSIGN);
            }
            sym -> getNextSymbol();
            expr();

            #ifdef GRAMMER_DEBUG
            cout << "assignment " << name_x << "[exprA] = exprB" << endl;
            #endif
            if (sym -> symbol != Type::SIMICOLON){
                error(Error::NO_SIMICOLON);
            }
            sym ->getNextSymbol();
        } else{
            error(Error::INVALID_IDENT);
            sym -> getNextSymbol();
        }
        return;
    }



    // write
    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::printfsym){
        sym -> getNextSymbol();
        write_dec();
        return ;
    }

    // read
    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::scanfsym){
        sym -> getNextSymbol();
        read_dec();
        return ;
    }

    // nothing ;
    if (sym -> symbol == Type::SIMICOLON){
        sym -> getNextSymbol();
        return ;
    }

    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::switchsym){
        sym -> getNextSymbol();
        switch_dec();
        return;
    }

    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::returnsym){
        sym -> getNextSymbol();
        return_dec();
        return;
    }

    error(Error::UNKNOWN_STATEMENT);
    sym -> getNextSymbol();
}

void Grammer::statements(){// 0 no return, 1 return (xxx), 2 return;
    while (sym -> symbol != Type::RBRACE) {
        statement();
    }
    //if (sym -> symbol == Type::RBRACE)
    //    sym -> getNextSymbol();
}

void Grammer::compound_sentence(){
    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::constsym){
        const_dec();
    }

    // var dec
    while (is_type()){
        this->is_int = sym -> reserved_type == Type::intsym;
        sym -> getNextSymbol();
        if (sym -> symbol != Type::IDENT) {
            error(Error::NO_IDENT);
        }
        this -> name = sym->name;

        sym -> getNextSymbol();
        var_dec();
    }

    statements();
    /*
    if (sym -> symbol != Type::LBRACE){
        error(Error::NO_LBRACE);
    }
    sym -> getNextSymbol();
    */
}

void Grammer::func_dec(){ // int/char xxx(,
    #ifdef GRAMMER_DEBUG
    cout << "function dec:  " << (is_int? "int":"char") << " " << name << endl;
    #endif
    args_dec();
    if (sym -> symbol != Type::LBRACE){
        error(Error::NO_LBRACE);
    }
    sym -> getNextSymbol();
    this -> return_flg = 1;
    compound_sentence();
    if (sym -> symbol != Type::RBRACE){
        error(Error::NO_RBRACE);
    }
    sym -> getNextSymbol();
}

void Grammer::proc_dec(){ // void xxx(,
    #ifdef GRAMMER_DEBUG
    cout << "procedure declare : void " << this->name <<endl;
    #endif
    args_dec();
    if (sym -> symbol != Type::LBRACE){
        error(Error::NO_LBRACE);
    }
    sym -> getNextSymbol();
    this -> return_flg = 2;
    compound_sentence();
    if (sym -> symbol != Type::RBRACE){
        error(Error::NO_RBRACE);
    }
    sym -> getNextSymbol();

}

void Grammer::start(){
    sym -> getNextSymbol();

    if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::constsym ){
        const_dec();
    }
    this -> return_flg = 0;
    // var dec
    while (is_type()){
        this->is_int = sym -> reserved_type == Type::intsym;
        sym -> getNextSymbol();
        if (sym -> symbol != Type::IDENT) {
            error(Error::NO_IDENT);
        }
        this -> name = sym->name;



        sym -> getNextSymbol();

        if (sym -> symbol == Type::LPARENT){ // function
            sym -> getNextSymbol();
            func_dec();
            break;
        }

        #ifdef CHECK
        fprintf(stderr, "not implement\n");
        #endif

        var_dec();
        /*
        #ifdef GRAMMER_DEBUG
        cout << "var dec: " << (is_int ? "int" : "char") << " " << name << endl;
        #endif

        //sym -> getNextSymbol();


        while(sym -> symbol == Type::COMMA){
            sym -> getNextSymbol();
            if (sym -> symbol != Type::IDENT){
                error(Error::NO_IDENT);
            }
            sym -> getNextSymbol();
        }

        if (sym -> symbol != Type::SIMICOLON) {
            error(Error::NO_SIMICOLON);
        }
        sym -> getNextSymbol();
        */
    }

    proc_type = -1;
    // procedure / function
    while(is_proc_type()){
        proc_type = sym -> reserved_type;
        sym -> getNextSymbol();
        if (sym -> symbol != Type::IDENT){
            if (sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::mainsym) {
                break;
            }
            error(Error::NO_IDENT);
        }
        this -> name = sym -> name;

        sym -> getNextSymbol();
        if (sym -> symbol != Type::LPARENT){
            error(Error::NO_LPARENT);
        } else
            sym -> getNextSymbol();

        if (proc_type == Type::voidsym){
            #ifdef GRAMMER_DEBUG
            cout << "procedure dec: " << this -> name << endl;
            #endif
            proc_dec();
        }else{
            #ifdef GRAMMER_DEBUG
            cout << "function dec: " << (proc_type == Type::intsym ? "int" : "char") <<
                " " << this -> name << endl;
            #endif
            func_dec();
        }


        proc_type = -1;
    }


    while (!(sym -> symbol == Type::RESERVED && sym -> reserved_type == Type::mainsym)) {
        if (!sym -> getNextSymbol()) {
            error(Error::NO_MAIN);
            return ;
        }
    }

    // main
    if (proc_type != Type::voidsym){
        error(Error::MAIN_NOT_VOID);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::LPARENT){
        error(Error::NO_LPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::RPARENT){
        error(Error::NO_RPARENT);
    }
    sym -> getNextSymbol();

    if (sym -> symbol != Type::LBRACE){
        error(Error::NO_LBRACE);
    }
    sym -> getNextSymbol();
    this -> return_flg = 2;
    compound_sentence();

    if (sym -> symbol != Type::RBRACE){
        error(Error::NO_RBRACE);
    }

    if (sym -> getNextSymbol()){
        error(Error::SHOULD_END);
    }
}
