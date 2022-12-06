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

#include "../lib/cli.h"
#include <check.h>
#include <stdlib.h>

START_TEST(check_echo) {
    struct cli_arg arg = {
        .command = "echo test",
        .flags   = CLI_ARG_FLAGS_GET_OUTPUT | CLI_ARG_FLAGS_REMOVE_NEWLINE,
        .exit    = 1
    };
    cli_exec(&arg);

    ck_assert_str_eq(arg.output, "test");
    ck_assert_int_eq(arg.exit, 0);

    cli_arg_free(&arg);
}
END_TEST

START_TEST(check_echo_newline) {
    struct cli_arg arg = {
        .command = "echo test",
        .flags   = CLI_ARG_FLAGS_GET_OUTPUT,
    };
    cli_exec(&arg);

    ck_assert_str_eq(arg.output, "test\n");
    ck_assert_int_eq(arg.exit, 0);

    cli_arg_free(&arg);
}

START_TEST(check_fail) {
    struct cli_arg arg = {
        .command = "false",
        .flags   = CLI_ARG_FLAGS_NONE,
        .exit    = 0
    };
    cli_exec(&arg);

    ck_assert_ptr_null(arg.output);
    ck_assert_int_eq(arg.exit, 1);

    cli_arg_free(&arg);
}

Suite *
cli_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("cli");

    /* Core test cases */
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, check_echo);
    tcase_add_test(tc_core, check_fail);
    tcase_add_test(tc_core, check_echo_newline);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s  = cli_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
