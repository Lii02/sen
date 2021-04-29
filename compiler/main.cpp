#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "arg.h"
#include "file.h"
#include "error_handler.h"
#include "lexer.h"

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        printf("usage: sen [main file] [flags]\n");
        exit(0);
    }

    stringA main_file;
    bool loaded = load_file(argv[1], &main_file);
    if(!loaded)
    {
        printf("SEN: Failed to load: %s\n", argv[1]);
        exit(0);
    }

    arg_packet_t args = {0};
    for(int i = 2; i < argc; i++)
    {
        if(!strcmp(argv[i], "-d") || !strcmp(argv[i], "-debug"))
        {
            args.debug = true;
        }
        else if(!strcmp(argv[i], "-w") || !strcmp(argv[i], "-no_warnings"))
        {
            args.give_warnings = false;
        }
        else if(!strcmp(argv[i], "-m86"))
        {
            args.arch = 86;
        }
        else if(!strcmp(argv[i], "-m64"))
        {
            args.arch = 64;
        }
        else
        {
            printf("SEN: Unknown flag: %s\n", argv[i]);
        }
    }

    error_handler* ehandler = new error_handler(args.give_warnings);
    if(!main_file.empty())
    {
        lexer lex = lexer(&main_file, ehandler);
    }

    delete ehandler;
    return 0;
}