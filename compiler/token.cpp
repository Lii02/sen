#include "token.h"

token::token(stringA lexeme, int8_t flag)
{
    this->lexeme = lexeme;
    this->flag = flag;
}

void token::set_flag(int8_t flag)
{
    this->flag |= flag;
}

bool token::has_flag(int8_t flag) const
{
    return (this->flag & flag);
}