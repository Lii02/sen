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
    dynamic_array<stringA> keywords, datatypes;
    stringA* source;
    stringA path;
    error_handler* ehandler;
    uint32_t counter, line, start;

    bool is_end() const;
    char advance();
    bool match(char expected);
    char peek();
    void handle_string();
    void handle_number();
    bool is_digit(char c) const;
    char peek_next() const;
    bool is_alpha(char c) const;
    bool is_alphanumeric(char c) const;
    void handle_identifier_keyword_datatype();
    void assemble_arrays();
    sourceobject<token> create_token(int8_t flag);
    sourceobject<token> create_token(int8_t flag, stringA str);
public:
    lexer(stringA* source, stringA path, error_handler* ehandler);
    void analyze();
    dynamic_array<sourceobject<token>>* get_output();
    void post_debug();
};

#endif