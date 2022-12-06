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

#ifndef __LIB_DUFF_RESPONSE_H
#define __LIB_DUFF_RESPONSE_H

#include "package.h"

typedef struct {
    int result_count;
    duff_package_t **response;
    char *type;
    int version;
} duff_response_t;

/**
 * Create new response struct
 *
 * @returns newly created duff_response_t struct
 */
duff_response_t *duff_response_new(void);

/**
 * Parse response struct from json string
 *
 * @returns newly populated duff_response_t struct
 */
duff_response_t *duff_response_parse(const char *data);

/**
 * Free data only in response struct
 *
 * @param duff_response_t 
 */
void duff_response_free(duff_response_t *r);

/**
 * Free all data in response struct
 * including packages
 *
 * @param duff_response_t
 */
void duff_response_free_all(duff_response_t *r);

#endif /* !__LIB_DUFF_RESPONSE_H */
