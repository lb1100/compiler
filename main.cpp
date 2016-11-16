#include "header.h"
#include "parameter.h"
#include "symbol.h"
#include "error.h"
#include "grammer.h"
using namespace std;

Symbol sym;
Grammer grammer;

void scan_and_print_token(){
    int count = 0;
    while(sym.getNextSymbol()){
    //while(true){
        int s = sym.symbol;
        if (s == 0){ // error
            cout << count << "\t:\t" << Type::type_message[0] << endl;
        } else
        if (s <= 2){ // number
            cout << count << "\t:\t" << Type::type_message[s] << "\t" << sym.num << endl;
        } else
        if (s == 3){ // char
            cout << count << "\t:\t" << Type::type_message[s] << "\t\t\'" <<
                sym.chr << "\'" << endl;
        } else
        if (s == 4){ // string
            cout << count << "\t:\t" << Type::type_message[s] << "\t\t\"" <<
                sym.name << "\"" << endl;
        } else
        if (s <=24){ // operator
            cout << count << "\t:\t" << Type::type_message[s] << endl;
        }else{ //reserved_word / identifier
            cout << count << "\t:\t" << Type::type_message[s] << "\t" << sym.name << endl;
        }
        count ++;
    }
}
char *file;
void init(){
    //freopen("out.txt","w",stdout);
    //sym.setUp("source.txt");
    sym.setUp(file);
    //freopen("out.txt","w",stdout);
    Type::init();

    grammer.set_sym(&sym);
}


int main(int argc, char **argv)
{
    freopen("out.txt","w", stdout);

    if (argc==2){
        file = argv[1];
    }else{
        file = "14061187_test.txt";
    }
    init();
    grammer.start();

    //scan_and_print_token();
    return 0;
}
