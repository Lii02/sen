#include "lexer.h"
#include <cstdio>

lexer::lexer(stringA* source, stringA path, error_handler* ehandler)
{
    this->source = source;
    this->path = path;
    this->ehandler = ehandler;
    this->counter = 0;
    this->line = 1;
    this->start = 0;
    this->assemble_arrays();
}

void lexer::analyze()
{
    while(!is_end())
    {
        char c = advance();
        start = counter;

        switch(c)
        {
        case '(': output.push(create_token(SEPERATOR_TOKEN)); break;
        case ')': output.push(create_token(SEPERATOR_TOKEN)); break;
        case '{': output.push(create_token(SEPERATOR_TOKEN)); break;
        case '}': output.push(create_token(SEPERATOR_TOKEN)); break;
        case '[': output.push(create_token(SEPERATOR_TOKEN)); break;
        case ']': output.push(create_token(SEPERATOR_TOKEN)); break;
        case ',': output.push(create_token(SEPERATOR_TOKEN)); break;
        case '.': output.push(create_token(SEPERATOR_TOKEN)); break;
        case ';': output.push(create_token(SEPERATOR_TOKEN)); break;
        case '-': output.push(create_token(OPERATOR_TOKEN)); break;
        case '+': output.push(create_token(OPERATOR_TOKEN)); break;
        case '*': output.push(create_token(OPERATOR_TOKEN)); break; 
        case '!':
            if(match('='))
            {
                start = counter - 2;
            }
            output.push(create_token(OPERATOR_TOKEN));
            break;
        case '=':
            if(match('='))
            {
                start = counter - 2;
            }
            output.push(create_token(OPERATOR_TOKEN));
            break;
        case '<':
            if(match('='))
            {
                start = counter - 2;
            }
            output.push(create_token(OPERATOR_TOKEN));
            break;
        case '>':
            if(match('='))
            {
                start = counter - 2;
            }
            output.push(create_token(OPERATOR_TOKEN));
            break;
        case '/':
            if(match('/'))
            {
                // Single-line comment
                while (peek() != '\n' && !is_end()) advance();
            }
            else if(match('*'))
            {
                // Multi-line comment
                handle_multiline_comment();
            }
            else
            {
                output.push(create_token(OPERATOR_TOKEN));
            }
            break;
        case ' ':
        case '\r':
        case '\0':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            line++;
            break;
        case '\"':
            handle_string();
            break;
        case '$':
            handle_macros();
            break;
        default:
            if(is_digit(c))
            {
                handle_number();
            }
            else if(is_alpha(c))
            {
                handle_identifier_keyword_datatype();
            }
            else
            {
                auto token = create_token(INVALID_TOKEN);
                char msg[255];
                sprintf(msg, "Invalid token: \'%c\'", c);
                ehandler->report_error_token(msg, token);
            }
            break;
        }
    }
}

bool lexer::is_end() const
{
    return (counter >= source->length());
}

char lexer::advance()
{
    return source->at(counter++);
}

bool lexer::match(char expected)
{
    if(is_end()) return false;
    if (source->at(counter) != expected) return false;

    this->counter++;
    return true;
}

char lexer::peek()
{
    if(is_end()) return '\0';
    return source->at(counter);
}

void lexer::handle_string()
{
    while(peek() != '\"' && !is_end())
    {
        if(peek() == '\n') line++;
        advance();
    }

    if(is_end())
    {
        ehandler->report_error_general("Unterminated string", line, path);
    }

    auto lexeme = source->substring(start - 1, counter + 1);
    output.push(create_token(STRING_LITERAL_TOKEN, lexeme));
    advance();
}

bool lexer::is_digit(char c) const
{
    return c >= '0' && c <= '9';
}

void lexer::handle_number()
{
    start = counter;
    while(is_digit(peek())) advance();

    int8_t flag = INT_LITERAL_TOKEN;
    if (peek() == '.' && is_digit(peek_next()))
    {
        // Consume the "."
        advance();
        flag = FLOAT_LITERAL_TOKEN;

        while (is_digit(peek())) advance();
    }

    auto token = create_token(flag, source->substring(start - 1, counter));
    output.push(token);
}

char lexer::peek_next() const
{
    if (counter + 1 >= source->length()) return '\0';
    return source->at(counter + 1);
}

bool lexer::is_alpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool lexer::is_alphanumeric(char c) const
{
    return is_alpha(c) || is_digit(c);
}

void lexer::handle_identifier_keyword_datatype()
{
    start = counter - 1;
    while(is_alphanumeric(peek())) advance();
    int8_t flag = IDENTIFIER_TOKEN;
    auto lexeme = source->substring(start, counter);

    for(size_t i = 0; i < datatypes.get_length(); i++)
    {
        if(datatypes[i] == lexeme)
            flag = DATATYPE_TOKEN;
    }

    for(size_t i = 0; i < keywords.get_length(); i++)
    {
        if(keywords[i] == lexeme)
            flag = KEYWORD_TOKEN;
    }

    auto token = create_token(flag);
    output.push(token);
}

sourceobject<token> lexer::create_token(int8_t flag)
{
    stringA lexeme = source->substring(start, counter);
    sourceobject<token> obj = sourceobject<token>(path, line, token(lexeme, flag));
    return obj;
}

void lexer::assemble_arrays()
{
    // Keywords
    keywords.push("print");

    // Datatypes
    datatypes.push("byte");
    datatypes.push("short");
    datatypes.push("int");
    datatypes.push("long");
}

void lexer::handle_multiline_comment()
{
    while(!is_end())
    {
        advance();
        if(match('\n')) line++;
        if(match('*') && advance() == '/')
        {
            line++;
            break;
        }
    }

    if(is_end())
    {
        ehandler->report_error_general("Unterminated multi-line comment(line approximation).", line, path);
    }
}

void lexer::handle_macros()
{
    start = counter - 1;
    while(is_alpha(peek()) && !is_end()) advance();
    auto lexeme = source->substring(start, counter);
    
    for(size_t i = 0; i < macros.get_length(); i++)
    {
        if(lexeme == macros[i])
        {
            auto token = create_token(MACRO_TOKEN, lexeme);
            output.push(token);
            return;
        }
    }

    char msg[255];
    sprintf(msg, "Invalid macro: %s", lexeme.get_buffer());
    ehandler->report_error_general(msg, line, path);
}

sourceobject<token> lexer::create_token(int8_t flag, stringA str)
{
    sourceobject<token> obj = sourceobject<token>(path, line, token(str, flag));
    return obj;
}

dynamic_array<sourceobject<token>>* lexer::get_output()
{
    return &output;
}

void lexer::post_debug()
{
    for(int i = 0; i < output.get_length(); i++)
    {
        printf("SEN~ Token %d: \'%s\' flag: %d | file: %s line: %d\n", i, output[i].get_data()->lexeme.get_buffer(), output[i].get_data()->flag, path.get_buffer(), output[i].get_line());
    }
}