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

#ifndef __LIB_DUFF_IO_H
#define __LIB_DUFF_IO_H

/**
 * Get current path to users home dir
 * 
 * @return gchar * dir path
 */
char *get_home_dir(void);

/**
 * Get path to cache dir
 *
 * @return gchar * full path to cache dir
 */
char *get_cache_path(void);

/**
 * Get if a directory already exists
 *
 * @returns 0 if exists
 */
int dir_exists(const char *dir);

#endif /* __LIB_DUFF_IO_H */
