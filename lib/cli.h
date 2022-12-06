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

#ifndef __LIB_DUFF_CLI_H
#define __LIB_DUFF_CLI_H

#define CLI_ARG_FLAGS_NONE 0
#define CLI_ARG_FLAGS_REMOVE_NEWLINE 1
#define CLI_ARG_FLAGS_GET_OUTPUT 1 << 1
#define CLI_ARG_FLAGS_OUTPUT_STDOUT 1 << 2

struct cli_arg {
    char *command;
    int flags;
    char *output;
    int exit;
};

/**
 * Exec command
 *
 * @param arg arguments to pass to cli
 */
void cli_exec(struct cli_arg *arg);

/**
 * Free output from cli
 *
 * @param arg
 */
void cli_arg_free(struct cli_arg *arg);

#endif /* __LIB_DUF_CLI_H */
