#ifndef TOKEN_H
#define TOKEN_H
#include "stringa.h"
#include <cstdint>

#define INVALID_TOKEN -1
#define KEYWORD_TOKEN 0
#define DATATYPE_TOKEN 1
#define IDENTIFIER_TOKEN 2
#define OPERATOR_TOKEN 3
#define INT_LITERAL_TOKEN 4
#define SEPERATOR_TOKEN 5
#define STRING_LITERAL_TOKEN 6
#define COMMENT_TOKEN 7
#define MACRO_TOKEN 8
#define CHAR_LITERAL_TOKEN 9
#define FLOAT_LITERAL_TOKEN 10

class token
{
public:
    stringA lexeme;
    int8_t flag;

    token(stringA lexeme, int8_t flag);
    token() = default;
    void set_flag(int8_t flag);
    bool has_flag(int8_t flag) const;
};

#endif