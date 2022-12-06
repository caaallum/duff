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

#include "request.h"
#include "package.h"
#include <assert.h> /* assert */
#include <curl/curl.h>
#include <stdlib.h> /* realloc */
#include <string.h> /* memcpy */

struct curl_response {
    char *ptr;
    size_t size;
};

size_t
curl_response_write(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize           = size * nmemb;
    struct curl_response *res = (struct curl_response *) userp;

    char *ptr = realloc(res->ptr, res->size + realsize + 1);
    if (ptr == NULL) {
        return 0;
    }

    res->ptr = ptr;
    memcpy(&(res->ptr[res->size]), data, realsize);
    res->size += realsize;
    res->ptr[res->size] = 0;

    return realsize;
}

duff_response_t *
duff_create_request(const char *url) {
    assert(url);

    struct curl_response res = { 0 };
    CURL *curl               = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 10L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_response_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res);

        curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);

    duff_response_t *response = duff_response_parse(res.ptr);
    free(res.ptr);

    return response;
}

duff_package_t **
duff_create_request_get_packages(const char *url) {
    duff_response_t *res = duff_create_request(url);

    duff_package_t **packages = res->response;

    duff_response_free(res);

    return packages;
}
