#include "error_handler.h"
#include <cstring>
#include <cstdio>

error_handler::error_handler(bool give_warnings)
{
    this->give_warnings = give_warnings;
    this->reset_stats();
}

void error_handler::reset_stats()
{
    memset(&pack, 0, sizeof(error_packet_t));
}

void error_handler::report_error_token(const char* msg, sourceobject<token> src)
{
    printf("SEN : Error: %s\n", msg);
    printf("\tLocation: [%s:%d]\n", src.get_path().get_buffer(), src.get_line());
    this->pack.errors++;
}

void error_handler::post() const
{
    if(give_warnings)
    {
        if (pack.errors == 0)
        {
            printf("");
        }
        else
        {
        }
    }
    else
    {
        if (pack.errors == 0)
        {
        }
        else
        {
        }
    }
}