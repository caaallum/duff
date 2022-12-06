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

#include "sync.h"
#include "cli.h"
#include "io.h"
#include "log.h"
#include "mem.h"
#include "request.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEARCH_FORMAT "https://aur.archlinux.org/rpc/?v=5&type=search&arg=%s"
#define INSTALL_FORMAT "https://aur.archlinux.org/rpc/?v=5&type=info&arg=%s"

void
_sync_search_package(duff_package_t ***p, const char *package) {
    LOG_DEBUG("Searching for package %s\n", package);

    char *url = malloc(sizeof(char) + strlen(SEARCH_FORMAT) + strlen(package));
    sprintf(url, SEARCH_FORMAT, package);

    duff_response_t *res = duff_create_request(url);

    free(url);

    if (res->result_count == 0) {
        printf("No package with the name %s found\n", package);
        duff_response_free_all(res);
        return;
    }

    duff_package_list_append(p, res->response);

    // for (int i = 0; i < res->result_count; i++) {
    //     package_t *search = res->response[i];
    //     printf("%s %s (%d %d)\n\t%s\n", search->name, search->version, search->num_votes, search->popularity, search->description);
    // }

    duff_response_free(res);
}

void
_sync_install_package(const char *package) {
    LOG_DEBUG("Installing package %s", package);

    char *url = malloc(sizeof(char) + strlen(INSTALL_FORMAT) + strlen(package));
    sprintf(url, INSTALL_FORMAT, package);

    LOG_DEBUG("Creating install request url: %s", url);

    duff_response_t *res = duff_create_request(url);
    free(url);

    if (res->result_count == 0) {
        printf("No package with the name %s found\n", package);
        duff_response_free(res);
        return;
    }

    duff_package_t *install = res->response[0];

    struct cli_arg arg        = { .flags = CLI_ARG_FLAGS_OUTPUT_STDOUT };
    static char install_fmt[] = "git clone https://aur.archlinux.org/%s.git %s/%s";
    const char *cache_path    = get_cache_path();
    arg.command               = malloc(sizeof(char) + strlen(install_fmt) + (strlen(install->name) * 2) + strlen(cache_path));
    assert(arg.command);
    sprintf(arg.command, install_fmt, install->name, cache_path, install->name);

    cli_exec(&arg);

    if (arg.exit != 0) {
        LOG_ERROR("Failed to clone %s", install->name);
        goto end;
    }

    static char build_fmt[] = "cd %s/%s; makepkg -si";
    arg.command             = realloc(arg.command, sizeof(char) + strlen(build_fmt) + strlen(cache_path) + strlen(install->name));
    assert(arg.command);
    sprintf(arg.command, build_fmt, cache_path, install->name);

    cli_exec(&arg);

    if (arg.exit != 0) {
        LOG_ERROR("Failed to build %s", install->name);
        goto end;
    }

    LOG_DEBUG("Successfully installed %s", install->name);
end:
    free(arg.command);
    duff_response_free(res);
}

duff_package_t **
sync_search(char ***packages, int size) {
    duff_package_t **p = NULL;
    for (int i = 0; i < size; i++) {
        _sync_search_package(&p, (*packages)[i]);
    }
    return p;
}

void
sync_install(char ***packages, int size) {
    for (int i = 0; i < size; i++) {
        _sync_install_package((*packages)[i]);
    }
}
