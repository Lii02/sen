#ifndef LEXER_H
#define LEXER_H
#include "array.h"
#include "sourceobject.h"
#include "token.h"
#include "error_handler.h"

class lexer
{
private:
    dynamic_array<sourceobject<token>> output;
    stringA* source;
    error_handler* ehandler;
public:
    lexer(stringA* source, error_handler* ehandler);
    void analyze();
    dynamic_array<sourceobject<token>>* get_output();
};

#endif