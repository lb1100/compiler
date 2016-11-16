#ifndef GRAMMER_H
#define GRAMMER_H
#include "symbol.h"
#include "error.h"
#include "header.h"

#define GRAMMER_DEBUG
class Grammer
{
public:
    Grammer();
    virtual ~Grammer();
    void set_sym(Symbol* );
    void start();
protected:
    void num();

    void const_dec();
    void var_dec();

    void args_dec();
    void args_list();
    void call();


    void func_dec();
    void proc_dec();
    void main_dec();

    void expr();
    void term();
    void factor();


    void while_dec();
    void if_dec();
    void condition();
    void switch_dec();


    void return_dec();
    void read_dec();
    void write_dec();
    void statement();
    void statements();
    void compound_sentence();
private:
    inline bool is_type(){
        return (sym -> symbol == Type::RESERVED &&
        (sym -> reserved_type == Type::intsym ||
         sym -> reserved_type == Type::charsym));
    }
    inline bool is_proc_type(){
        return (sym -> symbol == Type::RESERVED &&
        (sym -> reserved_type == Type::intsym ||
         sym -> reserved_type == Type::charsym ||
         sym -> reserved_type == Type::voidsym));
    }
    Symbol *sym;
    string name;
    bool is_int;
    int number;
    int proc_type;
    int return_flg;
};

#endif // GRAMMER_H
