#ifndef STRINGA_H
#define STRINGA_H
#include "array.h"

#define STRINGA_NPOS -1

class stringA
{
private:
    dynamic_array<char> data;
public:
    stringA() = default;
    stringA(const char* str);
    stringA(const stringA& str);
    const stringA& operator=(const stringA& str);
    void append(char c);
    void append(const char* str);
    const stringA& operator+=(char c);
    const stringA& operator+=(const char* str);
    char& operator[](int i);
    char* get_buffer() const;
    size_t length() const;
    bool empty() const;
    int find_first(char c, int start = 0);
    stringA substring(int s, int e);
    bool operator==(const stringA& str);
};

#endif