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

#ifndef __DUFF_PACKAGE_H
#define __DUFF_PACKAGE_H

#include <cJSON.h>
#include <vector.h>

typedef struct {
    int id;
    int package_base_id;
    int popularity;
    int num_votes;

    unsigned int first_submitted;
    unsigned int last_modified;
    unsigned int out_of_date;

    char *name;
    char *description;
    char *maintainer;
    char *version;
    char *url;
    char *url_path;
    char *package_base;

    vector_t *depends;
    vector_t *groups;
    vector_t *keywords;
    vector_t *license;
    vector_t *make_depends;
} duff_package_t;

/**
 * Create new package struct on the heap
 *
 * @returns newly created duff_package_t struct
 */
duff_package_t *duff_package_new(void);

/**
 * Create new package struct from json
 *
 * @param json cJSON json object
 *
 * @returns newly created duff_package_t struct
 */
duff_package_t *duff_package_from_json(const cJSON *json);

/**
 * Set string in duff_package_t struct
 *
 * @param dest pointer to char 
 * @param src char array
 */
void duff_package_set_string(char **dest, const char *src);

/**
 * Free package struct 
 *
 * @param p pointer to duff_package_t struct
 */
void duff_package_free(duff_package_t *p);

#endif /* __DUFF_PACKAGE_H */
