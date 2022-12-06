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

#include "response.h"
#include "cJSON.h"
#include "mem.h"
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* strlen, strcpy */

#include "log.h"

duff_response_t *
duff_response_new(void) {
    duff_response_t *r = malloc(sizeof(duff_response_t));
    assert(r);

    r->result_count = 0;
    r->response     = NULL;
    r->type         = NULL;
    r->version      = 0;

    return r;
}

duff_response_t *
duff_response_parse(const char *data) {
    duff_response_t *r      = NULL;
    const cJSON *item       = NULL;
    const cJSON *array_item = NULL;
    cJSON *json             = NULL;

    json = cJSON_Parse(data);
    if (json == NULL) {
        goto end;
    }

    r = duff_response_new();

    item = cJSON_GetObjectItemCaseSensitive(json, "resultcount");
    if (cJSON_IsNumber(item)) {
        r->result_count = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "type");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        r->type = malloc(sizeof(char) + strlen(item->valuestring));
        assert(r->type);
        strcpy(r->type, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "version");
    if (cJSON_IsNumber(item)) {
        r->version = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "results");
    if (cJSON_IsArray(item)) {
        r->response = malloc(sizeof(duff_package_t *) * r->result_count);
        for (int i = 0; i < r->result_count; i++) {
            array_item     = cJSON_GetArrayItem(item, i);
            r->response[i] = duff_package_from_json(array_item);
        }
    }

end:
    cJSON_Delete(json);
    return r;
}

void
duff_response_free(duff_response_t *r) {
    duff_free(r->type);
    duff_free(r);
}

void
duff_response_free_all(duff_response_t *r) {
    duff_free(r->type);
    for (int i = 0; i < r->result_count; i++) {
        duff_package_free(r->response[i]);
    }
    duff_free(r);
}
