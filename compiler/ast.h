#ifndef AST_H
#define AST_H
#include "sourceobject.h"
#include "array.h"

template <class T>
struct ast_object
{
    sourceobject<T> object;
    dynamic_array<ast_object*> next;
    T* get()
    {
        return object.get_data();
    }
    size_t get_size() const
    {
        return next.get_length();
    }
};

template <class T>
class AST
{
private:
    dynamic_array<ast_object<T>*> objects;
public:
    AST()
    {
        
    }

    ~AST()
    {

    }
};

#endif