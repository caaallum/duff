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
#include <check.h>
#include <stdarg.h>
#include <stdlib.h>

static gchar **
create_args(int num_args, ...) {
    gchar **argv = malloc(sizeof(gchar *) * num_args);

    va_list ptr;

    va_start(ptr, num_args);

    for (int i = 0; i < num_args; i++) {
        argv[i] = va_arg(ptr, gchar *);
    }

    va_end(ptr);

    return argv;
}

START_TEST(check_no_args) {
    gint argc    = 1;
    gchar **argv = create_args(argc, "duff");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);

    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_all_args) {
    gint argc    = 8;
    gchar **argv = create_args(argc, "duff", "-V", "-S", "-R", "-U", "-s", "test1", "test2");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);

    ck_assert_int_eq(args->version, TRUE);
    ck_assert_int_eq(args->sync, TRUE);
    ck_assert_int_eq(args->remove, TRUE);
    ck_assert_int_eq(args->upgrade, TRUE);
    ck_assert_int_eq(args->search, TRUE);

    ck_assert_ptr_nonnull(args->packages);
    ck_assert_str_eq(args->packages[0], "test1");
    ck_assert_str_eq(args->packages[1], "test2");

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_version) {
    gint argc    = 2;
    gchar **argv = create_args(argc, "duff", "-V");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, TRUE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_sync) {
    gint argc    = 2;
    gchar **argv = create_args(argc, "duff", "-S");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, TRUE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_remove) {
    gint argc    = 2;
    gchar **argv = create_args(argc, "duff", "-R");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, TRUE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_upgrade) {
    gint argc    = 2;
    gchar **argv = create_args(argc, "duff", "-U");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, TRUE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_search) {
    gint argc    = 2;
    gchar **argv = create_args(argc, "duff", "-s");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, TRUE);
    ck_assert_ptr_null(args->packages);

    free(argv);
    args_free(args);
}
END_TEST

START_TEST(check_arg_packages) {
    gint argc    = 4;
    gchar **argv = create_args(argc, "duff", "package1", "package2", "package3");

    args_t *args = args_parse(&argc, &argv);

    ck_assert_ptr_nonnull(args);
    ck_assert_int_eq(args->version, FALSE);
    ck_assert_int_eq(args->sync, FALSE);
    ck_assert_int_eq(args->remove, FALSE);
    ck_assert_int_eq(args->upgrade, FALSE);
    ck_assert_int_eq(args->search, FALSE);
    ck_assert_ptr_nonnull(args->packages);

    ck_assert_str_eq(args->packages[0], "package1");
    ck_assert_str_eq(args->packages[1], "package2");
    ck_assert_str_eq(args->packages[2], "package3");

    free(argv);
    args_free(args);
}
END_TEST

Suite *
args_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("args");

    /* Core test cases */
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, check_no_args);
    tcase_add_test(tc_core, check_all_args);
    tcase_add_test(tc_core, check_arg_version);
    tcase_add_test(tc_core, check_arg_sync);
    tcase_add_test(tc_core, check_arg_remove);
    tcase_add_test(tc_core, check_arg_upgrade);
    tcase_add_test(tc_core, check_arg_search);
    tcase_add_test(tc_core, check_arg_packages);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s  = args_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
