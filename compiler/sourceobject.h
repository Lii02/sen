#ifndef SRCOBJECT_H
#define SRCOBJECT_H
#include <cstdint>
#include "stringA.h"

template <class T>
class sourceobject
{
private:
    T data;
    stringA path;
    uint64_t line;
public:
    sourceobject(stringA path, uint64_t line, T data)
    {
        this->path = path;
        this->line = line;
        this->data = data;
    }

    T& get_data() const
    {
        return data;
    }

    stringA get_path() const
    {
        return path;
    }

    uint64_t get_line() const
    {
        return line;
    }
};

#endif