#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <syslog.h>
#include "logger.h"
#include <stdlib.h>

int current;

int initLogger(char *logType) {
    if(strcmp(logType,"stdout") == 0 || logType == ""){
        current = 0;
        printf("Initializing Logger on: stdout\n");
        closelog();
    }else if(strcmp(logType, "syslog") == 0){
        current = 1;
        printf("Initializing Logger on: syslog\n");
        openlog(NULL, LOG_NDELAY, LOG_USER); 
    }else{
        printf("Invalid Logger type \n");
        return -1;
    }
    return 0;
}

int infof(const char *format, ...){
    va_list values;
    va_start(values, format);
    int tmp = 0;
    if(current == 0){
        tmp = vprintf(format, values);
    }
    else{
        //openlog("syslog", LOG_PID | LOG_CONS | LOG_NOWAIT , LOG_SYSLOG);
        syslog(LOG_INFO, format, values);
    }
    va_end(values);
    return tmp;
}

int warnf(const char *format, ...){
    va_list values;
    int tmp = 0;
    va_start(values, format);
    if(current == 0){
        tmp = vprintf(format, values);
    }
    else{
        //openlog("syslog", LOG_PID | LOG_CONS | LOG_NOWAIT , LOG_SYSLOG);
        syslog(LOG_INFO, format, values);
    }
    va_end(values);
    return tmp;
}

int errorf(const char *format, ...){
    va_list values;
    int tmp = 0;
    va_start(values, format);
    if(current == 0){
        tmp = vprintf(format, values);
    }
    else{
        //openlog("syslog", LOG_PID | LOG_CONS | LOG_NOWAIT , LOG_SYSLOG);
        syslog(LOG_INFO, format, values);
        
    }
    va_end(values);
    return tmp;
}

int panicf(const char *format, ...){
    va_list values;
    int tmp = 0;
    va_start(values, format);
    if(current == 0){
        tmp = vprintf(format, values);
    }
    else{
        //openlog("syslog", LOG_PID | LOG_CONS | LOG_NOWAIT , LOG_SYSLOG);
        syslog(LOG_INFO, format, values);
        
    }
    va_end(values);
    abort();
    return -1;
}