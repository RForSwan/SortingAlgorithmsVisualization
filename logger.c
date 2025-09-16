#include "settings.h"

///// PRIVATE /////

char* get_current_time_string()
{
    time_t now;
    time(&now);
    char* time_str = ctime(&now);
    time_str[strlen(time_str)-1] = '\0'; // Remove newline
    return time_str;
}

///// PUBLIC /////

Logger* logger_create(bool to_file, bool to_stream, int log_level)
{
    Logger *log = calloc(1,sizeof(Logger));
    AssertNew(log);

    log->file      = NULL;
    log->stream    = NULL;
    log->log_level = log_level;

    if(to_file)
    {
        log->file = fopen(LOG_FILE, "w");
        fseek(log->file, 0, SEEK_END);
        AssertNew(log->file);
    }
    if(to_stream) log->stream = stdout;

    return log;
}

void logger_destroy(Logger* log)
{
    if(log->file)
    {
        fclose(log->file);
        log->file = NULL;
    }
    if(log->stream)
    {
        log->stream = NULL;
    }
    free(log);
}


/// @brief Logs a message with the sufficient log level
/// @param log Logger instance
/// @param log_level Log level of the message
/// @param message Message format (like printf)
/// @param ... Variable arguments for the message format
/// @return LOG_OK if logged, LOG_IGNORED if log level too low, LOG_ERROR if error
int logger_log(Logger* log, int log_level, const char* message, ...)
{
    // Check if log level is sufficient

    int err = 0;
    if(log_level > log->log_level) return LOG_IGNORED;

    // Setting access to variable arguments ( ... )

    va_list message_args;
    va_start(message_args, message);

    // Prepare strings

    char* time_str                 = get_current_time_string();
    char* level_str                = (char*)LOG_LEVELS_NAME[log_level];
    char  message_str[BUFFER_SIZE] = {'\0'};

    vsprintf(message_str, message, message_args);

    va_end(message_args);

    // Log to file and/or stream
    if(log->file)
    {
        err = fprintf(log->file,"[%s][TYPE : %7s] -> %s\n",
                      time_str,level_str,message_str);
        if(err < 0) return LOG_ERROR;
    }
    if(log->stream)
    {
        err = fprintf(log->stream,"[%s][TYPE : %7s] -> %s\n",
                      time_str,level_str,message_str);
        if(err < 0) return LOG_ERROR;
    }

    return LOG_OK;
}
