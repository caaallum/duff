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

#include "vector.h"
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, realloc, free */

#define INIT_CAPACITY 4

struct vector_t {
    void **items;
    int total;
    int capacity;
};

vector_t *
vector_init(void) {
    vector_t *v = malloc(sizeof(vector_t));
    assert(v);

    v->capacity = INIT_CAPACITY;
    v->total    = 0;
    v->items    = malloc(sizeof(void *) * v->capacity);
    assert(v->items);

    return v;
}

int
vector_total(vector_t *v) {
    assert(v);

    return v->total;
}

static void
vector__resize(vector_t *v, int capacity) {
    void **items = realloc(v->items, sizeof(void *) * capacity);
    assert(items);

    v->items    = items;
    v->capacity = capacity;
}

void
vector_add(vector_t *v, void *item) {
    assert(v);

    if (v->capacity == v->total) {
        vector__resize(v, v->capacity * 2);
    }

    v->items[v->total++] = item;
}

void
vector_add_vector(vector_t *v, vector_t *v2) {
    assert(v);
    assert(v2);

    for (int i = 0; i < v2->total; i++) {
        void *obj = v2->items[i];
        vector_add(v, obj);
    }
}

void
vector_set(vector_t *v, int index, void *item) {
    assert(v);

    if (index >= 0 && index < v->total) {
        v->items[index] = item;
    }
}

void *
vector_get(vector_t *v, int index) {
    assert(v);

    if (index >= 0 && index < v->total) {
        return v->items[index];
    }

    return NULL;
}

void
vector_foreach(vector_t *v, vector_callback callback, void *user_data) {
    assert(v);

    for (int i = 0; i < v->total; i++) {
        void *obj = v->items[i];
        if ((*callback)(obj, i, user_data) != 0) {
            break;
        }
    }
}

void
vector_delete(vector_t *v, int index) {
    assert(v);

    if (index < 0 || index >= v->total) {
        return;
    }

    v->items[index] = NULL;

    for (int i = index; i < v->total - 1; i++) {
        v->items[i]     = v->items[i + 1];
        v->items[i + 1] = NULL;
    }

    v->total--;

    if (v->total > 0 && v->total == v->capacity / 4) {
        vector__resize(v, v->capacity / 2);
    }
}

void
vector_free(vector_t *v) {
    free(v->items);
    free(v);
}

void
vector_free_all(vector_t *v, vector_callback callback) {
    for (int i = 0; i < vector_total(v); i++) {
        void *obj = v->items[i];
        (*callback)(obj, i, NULL);
    }
    vector_free(v);
}
