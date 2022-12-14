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

    for (int i = 0; i < res->result_count; i++) {
        duff_package_list_add(p, res->response[i]);
    }

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

    const char *cache_path = get_cache_path();
    char clone_path[256];
    sprintf(clone_path, "%s/%s", cache_path, install->name);

    if (dir_exists(clone_path) == 0) { /* Build files already exist */
    }

    cli_arg_t *arg = cli_arg_build(CLI_ARG_FLAGS_OUTPUT_STDOUT, "git clone https://aur.archlinux.org/%s.git %s/%s", install->name, cache_path, install->name);
    cli_exec(arg);

    if (arg->exit != 0) {
        LOG_ERROR("Failed to clone %s", install->name);
        goto end;
    }

    cli_arg_rebuild(&arg, CLI_ARG_FLAGS_OUTPUT_STDOUT, "cd %s/%s; makepkg -si", cache_path, install->name);

    cli_exec(arg);
    if (arg->exit != 0) {
        LOG_ERROR("Failed to build %s", install->name);
        goto end;
    }
    LOG_DEBUG("Successfully installed %s", install->name);
end:
    cli_arg_free(arg);
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
