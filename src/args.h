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

#ifndef __DUFF_ARGS_H
#define __DUFF_ARGS_H

#include <stdbool.h>

typedef struct {
    /* Program info */
    bool version;

    /* Core options */
    bool sync;
    bool remove;
    bool upgrade;

    /* Extended options */
    bool search;

    /* Packages */
    char **packages;
    int package_count;
} args_t;

args_t *args_parse(int *argc, char ***argv);

void args_free(args_t *args);

#endif /* !__DUFF_ARGS_H */
