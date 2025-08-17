#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

char *safe_snprintf(const char *format, ...) {

    va_list args;
    va_start(args, format);
    int written = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *buffer = (char *)malloc(sizeof(char) * written + 1);
    va_start(args, format);
    vsnprintf(buffer, written + 1, format, args);
    va_end(args);

    buffer[written] = '\0';

    return buffer;
}

void lower(char *s) {
    char *p = s;
    while (*p != '\0') {
        *p = tolower(*p);
        p++;
    }
}