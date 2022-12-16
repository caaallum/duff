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
#include "mem.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

duff_package_t *
duff_package_new(void) {
    duff_package_t *p = malloc(sizeof(duff_package_t));
    assert(p);

    p->id              = 0;
    p->package_base_id = 0;
    p->popularity      = 0;
    p->num_votes       = 0;
    p->first_submitted = 0;
    p->last_modified   = 0;
    p->out_of_date     = 0;
    p->name            = NULL;
    p->description     = NULL;
    p->maintainer      = NULL;
    p->version         = NULL;
    p->url             = NULL;
    p->url_path        = NULL;
    p->package_base    = NULL;
    p->depends         = vector_init();
    p->groups          = vector_init();
    p->keywords        = vector_init();
    p->license         = vector_init();
    p->make_depends    = vector_init();

    return p;
}

duff_package_t *
duff_package_from_json(const cJSON *json) {
    duff_package_t *p       = NULL;
    const cJSON *item       = NULL;
    const cJSON *array_item = NULL;

    p = duff_package_new();

    item = cJSON_GetObjectItemCaseSensitive(json, "ID");
    if (cJSON_IsNumber(item)) {
        p->id = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "PackageBaseID");
    if (cJSON_IsNumber(item)) {
        p->package_base_id = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Popularity");
    if (cJSON_IsNumber(item)) {
        p->popularity = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "NumVotes");
    if (cJSON_IsNumber(item)) {
        p->num_votes = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "FirstSubmitted");
    if (cJSON_IsNumber(item)) {
        p->first_submitted = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "LastModified");
    if (cJSON_IsNumber(item)) {
        p->last_modified = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "OutOfDate");
    if (cJSON_IsNumber(item)) {
        p->out_of_date = item->valueint;
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Name");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->name, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Description");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->description, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Maintainer");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->maintainer, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Version");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->version, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "URL");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->url, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "URLPath");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->url_path, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "PackageBase");
    if (cJSON_IsString(item) && (item->valuestring != NULL)) {
        duff_set_string(&p->package_base, item->valuestring);
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Depends");
    cJSON_ArrayForEach(array_item, item) {
        if (cJSON_IsString(array_item) && (array_item->valuestring != NULL)) {
            duff_package_add_array(&p->depends, array_item->valuestring);
        }
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Groups");
    cJSON_ArrayForEach(array_item, item) {
        if (cJSON_IsString(array_item) && (array_item->valuestring != NULL)) {
            duff_package_add_array(&p->groups, array_item->valuestring);
        }
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "Keywords");
    cJSON_ArrayForEach(array_item, item) {
        if (cJSON_IsString(array_item) && (array_item->valuestring != NULL)) {
            duff_package_add_array(&p->keywords, array_item->valuestring);
        }
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "License");
    cJSON_ArrayForEach(array_item, item) {
        if (cJSON_IsString(array_item) && (array_item->valuestring != NULL)) {
            duff_package_add_array(&p->license, array_item->valuestring);
        }
    }

    item = cJSON_GetObjectItemCaseSensitive(json, "MakeDepends");
    cJSON_ArrayForEach(array_item, item) {
        if (cJSON_IsString(array_item) && (array_item->valuestring != NULL)) {
            duff_package_add_array(&p->make_depends, array_item->valuestring);
        }
    }

    return p;
}

void
duff_package_free(duff_package_t *p) {
    duff_free(p->name);
    duff_free(p->description);
    duff_free(p->maintainer);
    duff_free(p->version);
    duff_free(p->url);
    duff_free(p->url_path);
    duff_free(p->package_base);

    duff_free(p);
}
