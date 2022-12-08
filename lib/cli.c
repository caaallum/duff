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

#include "cli.h"
#include "mem.h"
#include <assert.h> /* assert */
#include <stdarg.h> /* va_list, va_strt, va_end */
#include <stdio.h>  /* popen, pclose */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen, strcpy */

cli_arg_t *
cli_arg_new(void) {
    cli_arg_t *arg = malloc(sizeof(cli_arg_t));
    assert(arg);

    arg->command = NULL;
    arg->flags   = CLI_ARG_FLAGS_NONE;
    arg->output  = NULL;
    arg->exit    = 0;

    return arg;
}

cli_arg_t *
cli_arg_build(unsigned int flags, const char *fmt, ...) {
    cli_arg_t *arg = cli_arg_new();

    va_list ap;
    va_start(ap, fmt);
    assert(vasprintf(&arg->command, fmt, ap) > 0);
    va_end(ap);
    arg->flags = flags;

    return arg;
}

void
cli_arg_rebuild(cli_arg_t **arg, unsigned int flags, const char *fmt, ...) {
    cli_arg_free(*arg);

    *arg = cli_arg_new();

    va_list ap;
    va_start(ap, fmt);
    assert(vasprintf(&(*arg)->command, fmt, ap) > 0);
    va_end(ap);
    (*arg)->flags = flags;
}

void
cli_exec(cli_arg_t *arg) {
    char buffer[128];
    FILE *pipe = popen(arg->command, "r");
    if (!pipe) {
        arg->exit = 1;
        return;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        if (arg->flags & CLI_ARG_FLAGS_OUTPUT_STDOUT) {
            fprintf(stdout, "%s", buffer);
        }

        if (arg->flags & CLI_ARG_FLAGS_GET_OUTPUT) {
            if (arg->output == NULL) {
                arg->output = malloc(sizeof(char) + strlen(buffer));
                assert(arg->output);
                if (arg->flags & CLI_ARG_FLAGS_REMOVE_NEWLINE) {
                    buffer[strcspn(buffer, "\n")] = 0;
                }
                strcpy(arg->output, buffer);
            } else {
                arg->output = realloc(arg->output, sizeof(char) + strlen(arg->output) + strlen(buffer));
                assert(arg->output);
                if (arg->flags & CLI_ARG_FLAGS_REMOVE_NEWLINE) {
                    buffer[strcspn(buffer, "\n")] = 0;
                }
                strcat(arg->output, buffer);
            }
        }
    }
    int status = pclose(pipe);
    arg->exit  = WEXITSTATUS(status);
}

void
cli_arg_set_command(cli_arg_t *arg, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    assert(vasprintf(&arg->command, fmt, ap) > 0);
    va_end(ap);
}

void
cli_arg_free(cli_arg_t *arg) {
    duff_free(arg->output);
    duff_free(arg->command);
    duff_free(arg);
}
