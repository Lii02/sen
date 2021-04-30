#include "file.h"
#include <cstdio>
#include <cstring>

file_t* load_file(const char* path)
{
    file_t* f = new file_t();
    FILE* file = fopen(path, "r");
    if(!file)
    {
        f->loaded = false;
        return f;
    }
    fseek(file, 0, SEEK_END);
	size_t len = ftell(file);
	rewind(file);
    char* data = new char[len + 1];
    memset(data, 0, len + 1);
    fread((void*)data, 1, len, file);
    data[len] = '\0';
    f->source.append(data);
    fclose(file);
    delete[] data;
    f->loaded = true;
    return f;
}