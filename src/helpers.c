/* Header */
#include "helpers.h"
/* std */
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _game_log(const char *func,
               const char *fmt,
               ...)
{
    const int k_buffer_size = 1024;
    char buffer[k_buffer_size];

    /* Reset the buffer */
    memset(buffer, 0, k_buffer_size);

    /* Build the buffer with the variadic args list */
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buffer, k_buffer_size, fmt, ap);
    va_end(ap);

    /* Print the message and abort */
    fprintf(stdout, "[gamelog] (%s): %s\n", func, buffer);
}
