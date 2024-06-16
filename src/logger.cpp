#include "logger.hpp"
#include <stdarg.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;
namespace logger {
LogLevel g_level = LogLevel::Info;

string time_now() {
    time_t timep;
    char time_string[20];
    time(&timep);
    tm& t = *localtime(&timep);
    snprintf(time_string, sizeof(time_string),
             "%04d-%02d-%02d %02d:%02d:%02d",
             t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    return time_string;
}

string level_string(LogLevel level) {
    switch (level) {
        case LogLevel::Debug:
            return "debug";
        case LogLevel::Verbose:
            return "verbose";
        case LogLevel::Info:
            return "info";
        case LogLevel::Warning:
            return "warning";
        case LogLevel::Error:
            return "error";
        case LogLevel::Fatal:
            return "fatal";
        default:
            return "unknown";
    }
}
void set_log_level(LogLevel level) {
    g_level = level;
}
void __make_log(const char* file, int line, LogLevel level, const char* format, ...) {
    va_list vl;
    va_start(vl, format);

    char buff[2000];
    int n = 0;
    auto now = time_now();
    n += snprintf(buff + n, sizeof(buff) - n, YELLOW "[%s]" CLEAR, now.c_str());

    if (level == LogLevel::Debug) {
        n += snprintf(buff + n, sizeof(buff) - n, DGREEN "[%s]" CLEAR, level_string(level).c_str());
    } else if (level == LogLevel::Verbose) {
        n += snprintf(buff + n, sizeof(buff) - n, PURPLE "[%s]" CLEAR, level_string(level).c_str());
    } else if (level == LogLevel::Info) {
        n += snprintf(buff + n, sizeof(buff) - n, GREEN "[%s]" CLEAR, level_string(level).c_str());
    } else if (level == LogLevel::Warning) {
        n += snprintf(buff + n, sizeof(buff) - n, BLUE "[%s]" CLEAR, level_string(level).c_str());
    } else if (level == LogLevel::Error || level == LogLevel::Fatal) {
        n += snprintf(buff + n, sizeof(buff) - n, RED "[%s]" CLEAR, level_string(level).c_str());
    }

    n += snprintf(buff + n, sizeof(buff) - n, "[%s:%d]", file, line);

    n += vsnprintf(buff + n, sizeof(buff) - n, format, vl);
    fprintf(stdout, "%s\n", buff);
    va_end(vl);

    if (level == LogLevel::Error || level == LogLevel::Fatal) {
        fflush(stdout);
        abort();
    }
}
}  // namespace logger
