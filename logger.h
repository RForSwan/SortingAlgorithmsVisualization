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


enum LOG_RETURN {
    LOG_OK,
    LOG_IGNORED,
    LOG_ERROR,
};

#define LOG_TO_FILE_Y  true
#define LOG_TO_FILE_N  false
#define LOG_TO_STREAM_Y true
#define LOG_TO_STREAM_N false

/// @brief Creates a logger instance
/// @param to_file Whether to log to file
/// @param to_stream Whether to log to stream (stdout)
/// @param log_level Minimum log level to log
/// @return Logger instance
Logger* logger_create(bool to_file, bool to_stream, int log_level);

/// @brief Destroys the logger instance
/// @param log Logger instance
void    logger_destroy(Logger* log);

/// @brief Logs a message with the sufficient log level
/// @param log Logger instance
/// @param log_level Log level of the message
/// @param message Message format (like printf)
/// @param ... Variable arguments for the message format
/// @return LOG_OK if logged, LOG_IGNORED if log level too low, LOG_ERROR if error
int     logger_log(Logger* log, int log_level, const char* message, ...);

#endif