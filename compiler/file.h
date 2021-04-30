#ifndef FILE_H
#define FILE_H
#include "stringa.h"

typedef struct
{
    stringA source;
    bool loaded;
} file_t;

file_t* load_file(const char* path);

#endif