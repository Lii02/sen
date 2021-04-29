#include "stringA.h"
#include <cstring>

stringA::stringA(const char* str)
{
    this->append(str);
}

stringA::stringA(const stringA& str)
{
    this->append(str.get_buffer());
}

const stringA& stringA::operator=(const stringA& str)
{
    this->append(str.get_buffer());
    return *this;
}

void stringA::append(char c)
{
    this->data.push(c);
}

void stringA::append(const char* str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        this->append(str[i]);
    }
    // Terminate the string
    this->append('\0');
}

const stringA& stringA::operator+=(char c)
{
    this->append(c);
    return *this;
}

const stringA& stringA::operator+=(const char* str)
{
    this->append(str);
    return *this;
}

char& stringA::operator[](int i)
{
    return data[i];
}

char* stringA::get_buffer() const
{
    return data.get();
}

size_t stringA::length() const
{
    return data.get_length();
}

bool stringA::empty() const
{
    return (data.get_length() == 0);
}

int stringA::find_first(char c, int start)
{
    for(size_t i = start; i < length(); i++)
    {
        // Return first occurance of character 
        if(data[i] == c) return i;
    }
    return STRINGA_NPOS;
}

stringA stringA::substring(int s, int e)
{
    stringA str;
    if(e < 0) e = this->length();
    for(int i = s; i < e; i++)
    {
        str += data[i];
    }
    str += '\0';
    return str;
}

bool stringA::operator==(const stringA& str)
{
    return (strcmp(data.get(), str.get_buffer()) == 0);
}