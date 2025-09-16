#ifndef _LOGGER_H_
#define _LOGGER_H_

///// INCLUDES /////


///// LOGGER /////

#define LOG_FILE "events.log"
#define BUFFER_SIZE 2048

typedef struct Logger_s {
    FILE* file;
    FILE* stream;

    int  log_level;

} Logger;

#define LOG_LEVEL_SILENT  0
#define LOG_LEVEL_FATAL   1
#define LOG_LEVEL_ERROR   2
#define LOG_LEVEL_WARNING 3
#define LOG_LEVEL_INFO    4
#define LOG_LEVEL_DEBUG   5
#define LOG_LEVEL_TRACE   6
#define LOG_LEVEL_VERBOSE 7

enum LOG_RETURN {
    LOG_OK,
    LOG_IGNORED,
    LOG_ERROR,
};

static const char* LOG_LEVELS_NAME[] = {
    "SILENT",
    "FATAL",
    "ERROR",
    "WARNING",
    "INFO",
    "DEBUG",
    "TRACE",
    "VERBOSE"
};

#define LOG_TO_FILE_Y  true
#define LOG_TO_FILE_N  false
#define LOG_TO_STREAM_Y true
#define LOG_TO_STREAM_N false

Logger* logger_create(bool to_file, bool to_stream, int log_level);
void    logger_destroy(Logger* log);
int     logger_log(Logger* log, int log_level, const char* message, ...);

#endif