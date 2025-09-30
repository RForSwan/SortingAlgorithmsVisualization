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

    log->file       = NULL;
    log->stream     = NULL;
    log->log_level  = log_level;
    log->lastOutput = calloc(1, sizeof(char));
    log->nb_occurence = 0;

    if(to_file)
    {
        log->file = fopen(LOG_FILE, "a");
        AssertNew(log->file);
    }
    if(to_stream) log->stream = stdout;

    return log;
}


void logger_destroy(Logger* log)
{
    if(log->lastOutput)
    {
        free(log->lastOutput);
        log->lastOutput = NULL;
    }
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



int logger_log(Logger* log, int log_level, const char* message, ...)
{
    // Check if log level is sufficient

    int err = 0;
    if(log_level > log->log_level) return LOG_IGNORED;

    // Setting access to variable arguments ( ... )

    va_list message_args;
    va_start(message_args, message);

    // Prepare strings

    char* time_str  = get_current_time_string();
    char* level_str = (char*)LOG_LEVELS_NAME[log_level];
    char  message_buffer[BUFFER_SIZE] = {'\0'};
    char* message_str                 = calloc(BUFFER_SIZE, sizeof(char));

    vsprintf(message_buffer, message, message_args);

    va_end(message_args);

    sprintf(message_str, "[%s][TYPE : %7s] -> %s ",time_str,level_str,message_buffer);


    if(strcmp(message_str, log->lastOutput) == 0)
    {
        log->nb_occurence++;
        free(message_str);
    }
    else
    {
        // Log to file and/or stream
        if(log->file)
        {

            if(log->nb_occurence != 0) fprintf(log->file,"[occurred %d times]\n", log->nb_occurence);
            else fprintf(log->file, "\n");
            err = fprintf(log->file, "%s", message_str);
            fflush(log->file);
            if(err < 0) return LOG_ERROR;
        }
        if(log->stream)
        {
            if(log->nb_occurence != 0) fprintf(log->stream,"[occurred %d times]\n", log->nb_occurence);
            else fprintf(log->stream,"\n");
            err = fprintf(log->stream, "%s", message_str);
            fflush(log->stream);
            if(err < 0) return LOG_ERROR;
        }

        free(log->lastOutput);
        log->lastOutput = message_str;
        log->nb_occurence = 0;
    }

    return LOG_OK;
}
