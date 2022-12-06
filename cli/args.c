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

#include "args.h"
#include "log.h"
#include <assert.h>
#include <glib.h>

static gboolean version = FALSE;
static gboolean s       = FALSE;
static gboolean remove  = FALSE;
static gboolean upgrade = FALSE;

static gboolean search = FALSE;

args_t *
args_parse(int *argc, char ***argv) {
    GError *error = NULL;
    GOptionContext *context;
    static GOptionEntry entries[] = {
        /*  Program info */
        { "version", 'V', 0, G_OPTION_ARG_NONE, &version, "Display version information", NULL },

        /* Core options */
        { "sync", 'S', 0, G_OPTION_ARG_NONE, &s, "Sync", NULL },
        { "remove", 'R', 0, G_OPTION_ARG_NONE, &remove, "Remove", NULL },
        { "upgrade", 'U', 0, G_OPTION_ARG_NONE, &upgrade, "Upgrade", NULL },

        /* Extended options */
        { "search", 's', 0, G_OPTION_ARG_NONE, &search, "Search", NULL },

        { NULL, 0, 0, G_OPTION_ARG_NONE, NULL, NULL, NULL }
    };
    context = g_option_context_new(NULL);
    g_option_context_add_main_entries(context, entries, NULL);

    if (!g_option_context_parse(context, argc, argv, &error)) {
        g_print("%s\n\n", error->message);
        return NULL;
    }
    g_option_context_free(context);

    args_t *args = malloc(sizeof(args_t));
    assert(args);

    args->version = version;
    args->sync    = s;
    args->remove  = remove;
    args->upgrade = upgrade;
    args->search  = search;

    args->package_count = (*argc) - 1;
    args->packages      = NULL;
    if (args->package_count > 0) {
        args->packages = malloc(sizeof(char *) * args->package_count);
        for (int i = 1; i < *argc; i++) {
            args->packages[i - 1] = (*argv)[i];
        }
    }

    return args;
}

void
args_free(args_t *args) {
    if (args->packages != NULL) {
        free(args->packages);
    }
    free(args);
}
