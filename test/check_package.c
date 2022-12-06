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

#include "package.h"
#include <check.h>
#include <stdlib.h>

START_TEST(check_package_init) {
    duff_package_t *p = duff_package_new();

    ck_assert_ptr_nonnull(p);

    ck_assert_int_eq(p->id, 0);
    ck_assert_int_eq(p->package_base_id, 0);
    ck_assert_int_eq(p->popularity, 0);
    ck_assert_int_eq(p->num_votes, 0);
    ck_assert_int_eq(p->first_submitted, 0);
    ck_assert_int_eq(p->last_modified, 0);
    ck_assert_int_eq(p->out_of_date, 0);
    ck_assert_ptr_null(p->name);
    ck_assert_ptr_null(p->description);
    ck_assert_ptr_null(p->maintainer);
    ck_assert_ptr_null(p->version);
    ck_assert_ptr_null(p->url);
    ck_assert_ptr_null(p->url_path);
    ck_assert_ptr_null(p->package_base);
    ck_assert_ptr_null(p->depends);
    ck_assert_ptr_null(p->groups);
    ck_assert_ptr_null(p->keywords);
    ck_assert_ptr_null(p->license);
    ck_assert_ptr_null(p->make_depends);

    duff_package_free(p);
}
END_TEST

START_TEST(check_package_str) {
    duff_package_t *p = duff_package_new();

    char name[]         = "Name",
         description[]  = "Description",
         maintainer[]   = "Maintainer",
         version[]      = "Version",
         url[]          = "Url",
         url_path[]     = "Url Path",
         package_base[] = "Package Base";

    duff_package_set_string(&p->name, name);
    duff_package_set_string(&p->description, description);
    duff_package_set_string(&p->maintainer, maintainer);
    duff_package_set_string(&p->version, version);
    duff_package_set_string(&p->url, url);
    duff_package_set_string(&p->url_path, url_path);
    duff_package_set_string(&p->package_base, package_base);

    ck_assert_str_eq(p->name, name);
    ck_assert_str_eq(p->description, description);
    ck_assert_str_eq(p->maintainer, maintainer);
    ck_assert_str_eq(p->version, version);
    ck_assert_str_eq(p->url, url);
    ck_assert_str_eq(p->url_path, url_path);
    ck_assert_str_eq(p->package_base, package_base);

    duff_package_free(p);
}
END_TEST

START_TEST(check_package_array) {
    duff_package_t *p = duff_package_new();

    char depends0[] = "Depends 0",
         depends1[] = "Depends 1",
         depends2[] = "Depends 2";

    duff_package_add_array(&p->depends, depends0);
    duff_package_add_array(&p->depends, depends1);
    duff_package_add_array(&p->depends, depends2);

    ck_assert_str_eq(p->depends[0], depends0);
    ck_assert_str_eq(p->depends[1], depends1);
    ck_assert_str_eq(p->depends[2], depends2);

    char groups0[] = "Group 0";

    duff_package_add_array(&p->groups, groups0);

    ck_assert_str_eq(p->groups[0], groups0);

    char keywords0[] = "Keyword 0",
         keywords1[] = "Keyword 1",
         keywords2[] = "Keyword 2",
         keywords3[] = "Keyword 3",
         keywords4[] = "Keyword 4";

    duff_package_add_array(&p->keywords, keywords0);
    duff_package_add_array(&p->keywords, keywords1);
    duff_package_add_array(&p->keywords, keywords2);
    duff_package_add_array(&p->keywords, keywords3);
    duff_package_add_array(&p->keywords, keywords4);

    ck_assert_str_eq(p->keywords[0], keywords0);
    ck_assert_str_eq(p->keywords[1], keywords1);
    ck_assert_str_eq(p->keywords[2], keywords2);
    ck_assert_str_eq(p->keywords[3], keywords3);
    ck_assert_str_eq(p->keywords[4], keywords4);

    duff_package_free(p);
}
END_TEST

Suite *
package_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("package_t");

    /* Core test cases */
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, check_package_init);
    tcase_add_test(tc_core, check_package_str);
    tcase_add_test(tc_core, check_package_array);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s  = package_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
