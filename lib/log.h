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

#ifndef __LIB_DUFF_LOG_H
#define __LIB_DUFF_LOG_H

#include "config.h"

enum {
    LOG_LEVEL_TRACE,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL
};

#ifdef LOG_ENABLED
#define LOG_TRACE(...) log_log(LOG_LEVEL_TRACE, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_DEBUG(...) log_log(LOG_LEVEL_DEBUG, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) log_log(LOG_LEVEL_INFO, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) log_log(LOG_LEVEL_WARN, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) log_log(LOG_LEVEL_ERROR, __FILE_NAME__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) log_log(LOG_LEVEL_FATAL, __FILE_NAME__, __LINE__, __VA_ARGS__)
#else
#define LOG_TRACE(...)
#define LOG_DEBUG(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)
#endif /* !LOG_ENABLED */

void log_log(int level, const char *file, int line, const char *fmt, ...);

#endif /* !__LIB_DUFF_LOG_H */
