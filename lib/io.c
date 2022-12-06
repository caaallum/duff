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

#include "io.h"
#include <pwd.h>    /* getpwuid */
#include <stdlib.h> /* malloc */
#include <string.h> /* strcpy, strcat */
#include <unistd.h> /* getuid */

char *
get_home_dir(void) {
    char *dir_path = malloc(sizeof(char) + 256);
    uid_t uid      = getuid();

    struct passwd *pw = getpwuid(uid);
    if (pw == NULL) {
        strcpy(dir_path, "/");
        return dir_path;
    }

    strcpy(dir_path, pw->pw_dir);
    return dir_path;
}

char *
get_cache_path(void) {
    char *home = get_home_dir();

    strcat(home, "/.cache/duff");

    return home;
}
