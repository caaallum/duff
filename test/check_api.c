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

#include "../lib/request.h"
#include <check.h>
#include <stdlib.h>

START_TEST(check_api_search) {
    static char data[] = "{"
                         "\"resultcount\": 1,"
                         "\"results\": [{"
                         "\"Description\": \"AUR helper written in C99\","
                         "\"FirstSubmitted\": 1647632677,"
                         "\"ID\": 1053344,"
                         "\"LastModified\": 1647633534,"
                         "\"Maintainer\": \"caaallum\","
                         "\"Name\": \"duff\","
                         "\"NumVotes\": 0,"
                         "\"OutOfDate\": 1661479210,"
                         "\"PackageBase\": \"duff\","
                         "\"PackageBaseID\": 177039,"
                         "\"Popularity\": 0,"
                         "\"URL\": \"https://git.spei.rs/duff/log.html\","
                         "\"URLPath\": \"/duff.tar.gz\","
                         "\"Version\": \"0.1.0\""
                         "}],"
                         "\"type\": \"search\","
                         "\"version\": 5"
                         "}";

    duff_response_t *res = duff_response_parse(data);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(res->result_count, 1);
    ck_assert_str_eq(res->type, "search");
    ck_assert_int_eq(res->version, 5);

    duff_package_t *search = res->response[0];

    ck_assert_ptr_nonnull(search);
    ck_assert_int_eq(search->id, 1053344);
    ck_assert_int_eq(search->package_base_id, 177039);
    ck_assert_int_eq(search->popularity, 0);
    ck_assert_int_eq(search->num_votes, 0);
    ck_assert_int_eq(search->first_submitted, 1647632677);
    ck_assert_int_eq(search->last_modified, 1647633534);
    ck_assert_str_eq(search->description, "AUR helper written in C99");
    ck_assert_str_eq(search->maintainer, "caaallum");
    ck_assert_str_eq(search->name, "duff");
    ck_assert_int_eq(search->out_of_date, 1661479210);
    ck_assert_str_eq(search->package_base, "duff");
    ck_assert_str_eq(search->url, "https://git.spei.rs/duff/log.html");
    ck_assert_str_eq(search->url_path, "/duff.tar.gz");
    ck_assert_str_eq(search->version, "0.1.0");

    duff_response_free(res);
}
END_TEST

START_TEST(check_api_install) {
    static char data[] = "{"
                         "\"resultcount\": 1,"
                         "\"results\": [{"
                         "\"Depends\": [\"xz\", \"libmpc\" ],"
                         "\"Description\": \"AUR helper written in C99\","
                         "\"FirstSubmitted\": 1647632677,"
                         "\"Groups\": [\"duff\"],"
                         "\"ID\": 1053344,"
                         "\"Keywords\": [],"
                         "\"LastModified\": 1647633534,"
                         "\"License\": [\"GPL\"],"
                         "\"Maintainer\": \"caaallum\","
                         "\"MakeDepends\": [\"gmp\", \"gcc\"],"
                         "\"Name\": \"duff\","
                         "\"NumVotes\": 0,"
                         "\"OutOfDate\": 1661479210,"
                         "\"PackageBase\": \"duff\","
                         "\"PackageBaseID\": 177039,"
                         "\"Popularity\": 0,"
                         "\"URL\": \"https://git.spei.rs/duff/log.html\","
                         "\"URLPath\": \"/duff.tar.gz\","
                         "\"Version\": \"0.1.0\""
                         "}],"
                         "\"type\": \"multiinfo\","
                         "\"version\": 5"
                         "}";

    duff_response_t *res = duff_response_parse(data);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(res->result_count, 1);
    ck_assert_str_eq(res->type, "multiinfo");
    ck_assert_int_eq(res->version, 5);

    duff_package_t *install = res->response[0];

    ck_assert_ptr_nonnull(install);
    ck_assert_str_eq(install->depends[0], "xz");
    ck_assert_str_eq(install->depends[1], "libmpc");
    ck_assert_str_eq(install->description, "AUR helper written in C99");
    ck_assert_int_eq(install->first_submitted, 1647632677);
    ck_assert_str_eq(install->groups[0], "duff");
    ck_assert_int_eq(install->id, 1053344);
    ck_assert_ptr_null(install->keywords);
    ck_assert_int_eq(install->last_modified, 1647633534);
    ck_assert_str_eq(install->license[0], "GPL");
    ck_assert_str_eq(install->maintainer, "caaallum");
    ck_assert_str_eq(install->make_depends[0], "gmp");
    ck_assert_str_eq(install->make_depends[1], "gcc");
    ck_assert_str_eq(install->name, "duff");
    ck_assert_int_eq(install->num_votes, 0);
    ck_assert_int_eq(install->out_of_date, 1661479210);
    ck_assert_str_eq(install->package_base, "duff");
    ck_assert_int_eq(install->package_base_id, 177039);
    ck_assert_int_eq(install->popularity, 0);
    ck_assert_str_eq(install->url, "https://git.spei.rs/duff/log.html");
    ck_assert_str_eq(install->url_path, "/duff.tar.gz");
    ck_assert_str_eq(install->version, "0.1.0");

    duff_response_free(res);
}
END_TEST

Suite *
api_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("api");

    /* Core test cases */
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, check_api_search);
    tcase_add_test(tc_core, check_api_install);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed = 0;
    Suite *s;
    SRunner *sr;

    s  = api_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
