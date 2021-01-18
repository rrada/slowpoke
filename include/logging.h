#ifdef LOGGING
#include <stdarg.h>

void log(const char* format, ...)
{
    char buf[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    Serial.print(buf);
}

#else // logging is disabled
#define log(...)
#endif