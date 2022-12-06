/*
 * This file is part of duff.
 *
 * duff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * duff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with duff.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Copyright (C) 2022 callum speirs
 * https://github.com/caaallum/duff
 */

#include "log.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static const char *level_strings[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

static const char *level_colors[] = {
    "\x1b[94m", /* Trace */
    "\x1b[36m", /* Debug */
    "\x1b[32m", /* Info */
    "\x1b[33m", /* Warning */
    "\x1b[31m", /* Error */
    "\x1b[35m"  /* Fatal */
};

void
log_log(int level, const char *file, int line, const char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);
    time_t t = time(NULL);

    char buf[16];
    buf[strftime(buf, sizeof(buf), "%H:%M:%S", localtime(&t))] = '\0';

    fprintf(stderr, "[%s]-[%s%-5s\x1b[0m \x1b[90m%s:%d\x1b[0m]: ",
            buf, level_colors[level], level_strings[level],
            file, line);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");

    fflush(stderr);
    va_end(ap);
}
