#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include <cstdint>
#include "sourceobject.h"
#include "token.h"

struct error_packet_t
{
    uint32_t errors;
    uint32_t warnings;
    uint32_t notes;
};

class error_handler
{
private:
    bool give_warnings;
    error_packet_t pack;
public:
    error_handler(bool give_warnings = true);
    void reset_stats();
    void report_error_token(const char* msg, sourceobject<token> src);
    void post() const;
};

#endif