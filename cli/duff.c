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

#include "../lib/duff.h"
#include "../lib/log.h"
#include "../lib/package.h"
#include "../lib/sync.h"
#include "args.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

int
vector_free_package(void *data, int index __attribute__((unused)), void *user_data __attribute__((unused))) {
    duff_package_free(data);
    return 0;
}

int
main(int argc, char **argv) {
    LOG_INFO("Starting duff %s", VERSION);
    struct gengetopt_args_info args_info;

    if (cmdline_parser(argc, argv, &args_info) != 0) {
        exit(1);
    }

    int ret = duff_init();
    LOG_DEBUG("Init: %d", ret);

    if (args_info.sync_flag) {
        if (args_info.search_flag) {
            duff_package_t **v = sync_search(&args->packages, args->package_count);
            for (int i = 0; v[i]; i++) {
                duff_package_t *search = v[i];
                printf("%s %s (%d %d)\n\t%s\n", search->name, search->version, search->num_votes, search->popularity, search->description);
            }

            duff_package_free_list(v);
            return EXIT_SUCCESS;
        }
        sync_install(&args->packages, args->package_count);
    }

    cmdline_parser_free(&args_info);
    return EXIT_SUCCESS;
}
