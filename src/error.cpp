#include "error.h"

void error(int error_num){
    std::cout << "Error : " << Error::Error_message[error_num] << std::endl;
    error_count ++;
}

void fatal(int fatal_num){
    std::cout << "Fatal : " << Fatal::fatal_message[fatal_num] << std::endl;
    exit(-1);
}
