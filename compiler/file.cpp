#include "file.h"
#include <cstdio>

bool load_file(const char* path, stringA* str)
{
    FILE* file = fopen(path, "r");
    if(!file) return false;
    fseek(file, 0, SEEK_END);
	size_t len = ftell(file);
	rewind(file);
    char* data = new char[len + 1];
    fread(data, 1, len, file);
    data[len] = 0;
    *str = stringA(data);
    fclose(file);
    delete[] data;
    return true;
}