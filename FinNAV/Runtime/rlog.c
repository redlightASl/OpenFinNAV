#include "rlog.h"
#include "Defines.h"
#include "Driver.h"


#ifdef LIBROV_ENABLE_RLOG
struct logger {
    rlog_entry_t entry;
    rlog_level_enum log_level;
};
typedef struct logger logger_t;

static logger_t loggers[RLOG_MAX_COMMITOR];
static uint8_t log_msg[RLOG_MAX_LENGTH];


/**
 * @brief Init logger object
 */
void Rlog_init(void)
{
    memset(loggers, 0, sizeof(loggers));
}

/**
 * @brief Commit rlog entry function and its log level to logger object
 * @param  entry            rlog entry function
 * @param  log_level        log level
 * @return uint8_t
 */
uint8_t Rlog_commit(rlog_entry_t entry, rlog_level_enum log_level)
{
    int32_t free_slot = -1;
    for (uint32_t i = 0; i < RLOG_MAX_COMMITOR; i++)
    {
        if (loggers[i].entry == entry)
        {
            loggers[i].log_level = log_level; //update log level
            return ROV_TRUE;
        }
        else if (loggers[i].entry == ((rlog_entry_t)0))
        {
            free_slot = i;
        }
    }

    if (free_slot == -1) //logger object full
    {
        return ROV_FALSE;
    }

    loggers[free_slot].entry = entry; //update entry function and log level
    loggers[free_slot].log_level = log_level;
    return ROV_TRUE;
}

/**
 * @brief Uncommit rlog entry function from logger object
 * @param  entry            rlog entry function
 * @return uint8_t
 */
uint8_t Rlog_uncommit(rlog_entry_t entry)
{
    for (uint32_t i = 0; i < RLOG_MAX_COMMITOR; i++)
    {
        if (loggers[i].entry == entry)
        {
            loggers[i].entry = ((rlog_entry_t)0); // mark as empty
            return ROV_TRUE;
        }
    }
    return ROV_FALSE;
}

/**
 * @brief Check out names of log level
 * @param  log_level        log level
 * @return const char* the name of log level
 */
const char* Rlog_level_name(rlog_level_enum log_level)
{
    switch (log_level)
    {
    case RLOG_DEBUG:
        return "DEBUG";
    case RLOG_INFO:
        return "INFO";
    case RLOG_WARNING:
        return "WARNING";
    case RLOG_ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

/**
 * @brief send log message to rlog entry function
 * @param  log_level        The minimum log level required for a logger to log the message.
 * @param  format           The string used to log.
 * @param  ...              Format control
 * @return uint32_t the length of log message
 */
uint32_t rov_printf(rlog_level_enum log_level, const char* format, ...)
{
    uint16_t len;
    va_list args;
    va_start(args, format);
    len = vsnprintf((char*)log_msg, RLOG_MAX_LENGTH, format, args);
    va_end(args);

    for (uint32_t i = 0; i < RLOG_MAX_COMMITOR; i++)
    {
        if (loggers[i].entry != ((rlog_entry_t)0))
        {
            if (log_level >= loggers[i].log_level)
            {
                loggers[i].entry(log_level, (char*)log_msg);
            }
        }
    }

    return len;
}

void rlog_default_template(rlog_level_enum log_level, char* m)
{
    printf("[%s/%s]: %s\r\n", "main", Rlog_level_name(log_level), m);
}

void rlog_create(rlog_level_enum log_level)
{
    RLOG_INIT();
    RLOG_COMMIT(rlog_default_template, log_level);
}
#endif /* LIBROV_ENABLE_RLOG */



