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
#include "args.h"
#include "config.h"
#include "../lib/log.h"
#include "../lib/sync.h"
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv) {
    LOG_INFO("Starting duff %s", VERSION);
    args_t *args = args_parse(&argc, &argv);

    int ret = duff_init();
    LOG_DEBUG("Init: %d", ret);
    if (args == NULL) {
        return EXIT_FAILURE;
    }

    if (args->version) {
        printf("duff %s\n", VERSION);
        printf("Copyright (C) 2022 Callum Speirs\n");
        printf("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n");
        printf("This is free software: you are free to change and redistribute it.\n");
        printf("There is NO WARRANTY, to the extent permitted by law.\n\n");
    }

    if (args->sync) {
        if (args->search) {
            duff_package_t **p = sync_search(&args->packages, args->package_count);
            for (int i = 0; p[i]; i++) {
                duff_package_t *search = p[i];
                printf("%s %s (%d %d)\n\t%s\n", search->name, search->version, search->num_votes, search->popularity, search->description);
            }
            duff_package_free_list(p);
            return EXIT_SUCCESS;
        }
        //sync_install(&args->packages, args->package_count);
    }

    args_free(args);
    return EXIT_SUCCESS;
}
