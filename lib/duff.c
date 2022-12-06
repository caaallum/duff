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

#include "duff.h"
#include "io.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int
create_cache_dir(void) {
    struct stat st        = { 0 };
    const char *cache_dir = get_cache_path();

    mkdir(cache_dir, 0700);
    return stat(cache_dir, &st);
}

int
duff_init(void) {
    int ret;

    ret = create_cache_dir();

    return ret;
}
