#include "lexer.h"

lexer::lexer(stringA* source, error_handler* ehandler)
{
    this->source = source;
    this->ehandler = ehandler;
}

void lexer::analyze()
{

}

dynamic_array<sourceobject<token>>* lexer::get_output()
{
    return &output;
}