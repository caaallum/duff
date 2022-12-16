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

#include "../src/vector.h"
#include <check.h>
#include <stdlib.h>

START_TEST(check_vector_init) {
    vector_t *v = vector_init();

    ck_assert_ptr_nonnull(v);
    ck_assert_int_eq(vector_total(v), 0);

    vector_free(v);
}
END_TEST

START_TEST(check_vector_add) {
    static char index0[] = "index0";
    static char index1[] = "index1";

    vector_t *v = vector_init();

    vector_add(v, index0);
    ck_assert_int_eq(vector_total(v), 1);

    vector_add(v, index1);
    ck_assert_int_eq(vector_total(v), 2);

    ck_assert_str_eq(vector_get(v, 0), index0);
    ck_assert_str_eq(vector_get(v, 1), index1);

    vector_free(v);
}
END_TEST

START_TEST(check_vector_set) {
    static char index0[] = "index0";
    static char index1[] = "index1";
    static char index2[] = "index2";

    static char replace[] = "replace";

    vector_t *v = vector_init();

    vector_add(v, index0);
    vector_add(v, index1);
    vector_add(v, index2);

    ck_assert_str_eq(vector_get(v, 0), index0);
    ck_assert_str_eq(vector_get(v, 1), index1);
    ck_assert_str_eq(vector_get(v, 2), index2);

    vector_set(v, 1, replace);

    ck_assert_str_eq(vector_get(v, 0), index0);
    ck_assert_str_eq(vector_get(v, 1), replace);
    ck_assert_str_eq(vector_get(v, 2), index2);

    vector_free(v);
}
END_TEST

START_TEST(check_vector_add_vector) {
    static char v1_0[] = "v1_0";
    static char v1_1[] = "v1_1";
    static char v1_2[] = "v1_2";

    static char v2_0[] = "v2_0";
    static char v2_1[] = "v2_1";

    vector_t *v1 = vector_init();
    vector_t *v2 = vector_init();

    vector_add(v1, v1_0);
    vector_add(v1, v1_1);
    vector_add(v1, v1_2);
    ck_assert_str_eq(vector_get(v1, 0), v1_0);
    ck_assert_str_eq(vector_get(v1, 1), v1_1);
    ck_assert_str_eq(vector_get(v1, 2), v1_2);

    vector_add(v2, v2_0);
    vector_add(v2, v2_1);
    ck_assert_str_eq(vector_get(v2, 0), v2_0);
    ck_assert_str_eq(vector_get(v2, 1), v2_1);

    vector_add_vector(v1, v2);

    ck_assert_str_eq(vector_get(v1, 0), v1_0);
    ck_assert_str_eq(vector_get(v1, 1), v1_1);
    ck_assert_str_eq(vector_get(v1, 2), v1_2);
    ck_assert_str_eq(vector_get(v1, 3), v2_0);
    ck_assert_str_eq(vector_get(v1, 4), v2_1);

    vector_free(v1);
    vector_free(v2);
}
END_TEST

Suite *
vector_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("vector");

    /* Core test cases */
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, check_vector_init);
    tcase_add_test(tc_core, check_vector_add);
    tcase_add_test(tc_core, check_vector_set);
    tcase_add_test(tc_core, check_vector_add_vector);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s  = vector_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
