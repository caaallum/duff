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

#ifndef __LIB_DUFF_VECTOR_H
#define __LIB_DUFF_VECTOR_H

typedef struct vector_t vector_t;

typedef int (*vector_callback)(void *obj, int index, void *user_data);

/**
 * Init empty vector
 *
 * @returns newly create vector
 */
vector_t *vector_init(void);

/**
 * Get total number of items in vector
 *
 * @param v vector
 *
 * @returns total
 */
int vector_total(vector_t *v);

/**
 * Add item to end of vector
 *
 * @param v vector
 * @param item item to add
 */
void vector_add(vector_t *v, void *item);

/**
 * Add items from one vector to end of another
 *
 * @param v vector to add to
 * @param v2 vector to add from
 */
void vector_add_vector(vector_t *v, vector_t *v2);

/**
 * Set item at given index of vector
 *
 * @param v vector
 * @param index index of item to set
 * @param item item to set
 */
void vector_set(vector_t *v, int index, void *item);

/**
 * Get item at given index
 *
 * @param v vector
 * @param index
 *
 * @returns item on success NULL on fail
 */
void *vector_get(vector_t *v, int index);

/**
 * Delete item in vector at givem index
 *
 * @param v vector
 * @param index
 */
void vector_delete(vector_t *v, int index);

/**
 * Loop items in vector
 *
 * @param v vector
 * @param callback callback function
 * @param user_data user data to pass into callback
 */
void vector_foreach(vector_t *v, vector_callback callback, void *user_data);

/**
 * Free vector struct
 *
 * @param v vector
 */
void vector_free(vector_t *v);

/**
 * Free vector struct and allow function to call for each object
 *
 * @param v vector
 * @param callback object callback
 */
void vector_free_all(vector_t *v, vector_callback callback);

#endif /* !__LIB_DUFF_VECTOR_H */
