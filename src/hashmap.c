/**
 * @file hashmap.c
 * @author Amar Campbell
 * @brief This is the hashmap Implementation file
 * @copyright Copyright (c) 2026 Amar
 */

#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief hash the key and return bucket index
 *
 * @param map pointer to the map
 * @param key the string key to be hashed
 * @return size_t the bucket index in the map
 */
static size_t map_hash(size_t cap, const char* key) {

    if (key == NULL) {
        (void)fprintf(stderr, "The key is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    size_t bucket_idx = 0;
    size_t factor     = 31;
    for (size_t i = 0; i < strlen(key); i++) {
        bucket_idx = ((bucket_idx % cap) + (((size_t)key[i]) * factor) % cap) % cap;

        factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
    }
    return bucket_idx;
}

MapPtr map_create(size_t cap, size_t element_size) {
    MapPtr map = (MapPtr)calloc(1, sizeof(Map));
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        return NULL;
    }

    map->length = 0;
    if (cap == 0) {
        map->capacity = 100;
    } else {
        map->capacity = cap;
    }
    map->element_size = element_size;
    map->buckets      = (void**)calloc(map->capacity, sizeof(void*));
    if (map->buckets == NULL) {
        (void)fprintf(stderr, "The map->buckets is null in %s line# %d", __FILE__, __LINE__);
        free(map);
        return NULL;
    }
    return map;
}

MAP_ERROR_CODES map_put(MapPtr map, const char* key, const void* value) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    if (key == NULL) {
        (void)fprintf(stderr, "The key is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    if (value == NULL) {
        (void)fprintf(stderr, "The value is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    if (map->length != 0 && ((float)map->length) / (float)map->capacity >= LOAD_FACTOR) {
        map_resize(map, map->capacity * 2);
    }

    NodePtr new_node = calloc(1, sizeof(Node));
    if (new_node == NULL) {
        (void)fprintf(stderr, "The new_node is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    void* new_key = malloc(strlen(key) + 1);
    if (new_key == NULL) {
        (void)fprintf(stderr, "The new_key is null in %s line# %d", __FILE__, __LINE__);
        free(new_node);
        return (MAP_ERROR_RETURN_ERROR);
    }
    memmove(new_key, key, strlen(key) + 1);
    new_node->key = new_key;

    void* new_value = calloc(1, map->element_size);
    if (new_value == NULL) {
        (void)fprintf(stderr, "The new_value is null in %s line# %d", __FILE__, __LINE__);
        free(new_node->key);
        free(new_node);
        return (MAP_ERROR_RETURN_ERROR);
    }
    memmove(new_value, value, map->element_size);
    new_node->value = new_value;
    new_node->next  = NULL;

    size_t bucket_idx = map_hash(map->capacity, new_node->key);

    if (map->buckets[bucket_idx] == NULL) {
        map->buckets[bucket_idx] = new_node;
        map->length++;
        return MAP_ERROR_RETURN_SUCCESS;
    }

    NodePtr previous = NULL;
    NodePtr current  = map->buckets[bucket_idx];
    while (true) {
        if (current != NULL && memcmp(current->key, new_key, strlen(key) + 1) != 0) {
            previous = current;
            current  = current->next;
            continue;
        }

        if (current != NULL && memcmp(new_key, (current)->key, strlen((char*)new_key) + 1) == 0) {
            free((current)->value);
            (current)->value = new_value;
            free(new_key);
            free(new_node);
            break;
        }

        current        = new_node;
        previous->next = current;
        map->length++;
        break;
    }

    return MAP_ERROR_RETURN_SUCCESS;
}

void* map_get(MapPtr map, const char* key) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    if (key == NULL) {
        (void)fprintf(stderr, "The key is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    size_t bucket_idx = map_hash(map->capacity, key);

    if (map->buckets == NULL || bucket_idx > map->capacity || map->buckets[bucket_idx] == NULL) {
        return NULL;
    }

    NodePtr current = ((NodePtr)map->buckets[bucket_idx]);

    while (true) {
        if (current != NULL && memcmp(current->key, key, strlen(key) + 1) == 0) {
            break;
        }

        if (current != NULL && memcmp(current->key, key, strlen(key) + 1) != 0) {
            current = current->next;
            continue;
        }

        return NULL;
    }

    return current->value;
}

MAP_ERROR_CODES map_remove(MapPtr map, const char* key) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    if (key == NULL) {
        (void)fprintf(stderr, "The key is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    size_t bucket_idx = map_hash(map->capacity, key);

    if (bucket_idx >= map->capacity) {
        return (MAP_ERROR_OUT_OF_BOUND);
    }

    NodePtr previous = NULL;
    NodePtr current  = map->buckets[bucket_idx];
    if (current == NULL) {
        return (MAP_ERROR_NOT_FOUND);
    }
    NodePtr next = ((NodePtr)map->buckets[bucket_idx])->next;

    if (current != NULL && strcmp(current->key, key) == 0 && next == NULL) {
        free(current->key);
        free(current->value);
        free(current);
        current                  = NULL;
        map->buckets[bucket_idx] = NULL;
        map->length--;
        return MAP_ERROR_RETURN_SUCCESS;
    }

    if (current != NULL && strcmp(current->key, key) == 0 && next != NULL) {
        free(current->key);
        free(current->value);
        free(current);
        current                  = NULL;
        map->buckets[bucket_idx] = next;
        map->length--;
        return MAP_ERROR_RETURN_SUCCESS;
    }

    while (true) {
        if (strcmp(current->key, key) == 0) {
            free(current->key);
            free(current->value);
            previous->next = next;
            current->next  = NULL;
            free(current);
            map->length--;
            break;
        }
        previous = current;
        current  = next;
        if (current == NULL) {
            return (MAP_ERROR_NOT_FOUND);
        }
        next = current->next;
    }

    return MAP_ERROR_RETURN_SUCCESS;
}

bool map_contains(MapPtr map, const char* key) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    if (key == NULL) {
        (void)fprintf(stderr, "The key is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    size_t bucket_idx = map_hash(map->capacity, key);

    if (bucket_idx > map->capacity || map->length == 0) {
        return false;
    }

    NodePtr current = (NodePtr)map->buckets[bucket_idx];

    while (true) {
        if (current == NULL) {
            return false;
        }

        if (memcmp(current->key, key, strlen(key) + 1) == 0) {
            break;
        }

        current = current->next;
    }
    return true;
}

MAP_ERROR_CODES map_resize(MapPtr map, size_t new_cap) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    size_t new_cap_t;
    if (new_cap == 0) {
        new_cap_t = map->capacity * 2;
    } else {
        new_cap_t = new_cap;
    }

    void** new_buckets = (void**)calloc(new_cap_t, sizeof(void*));
    if (new_buckets == NULL) {
        (void)fprintf(stderr, "The new_buckets is null in %s line# %d", __FILE__, __LINE__);
        return (MAP_ERROR_RETURN_ERROR);
    }

    for (size_t i = 0; i < map->capacity; i++) {
        NodePtr map_bucket_current = map->buckets[i];

        while (map_bucket_current != NULL) {
            size_t bucket_idx               = map_hash(new_cap_t, map_bucket_current->key);
            NodePtr map_bucket_current_next = map_bucket_current->next;

            if (new_buckets[bucket_idx] == NULL) {
                map_bucket_current->next = NULL;
                new_buckets[bucket_idx]  = map_bucket_current;
                map_bucket_current       = map_bucket_current_next;
                continue;
            }

            NodePtr new_bucket_previous = NULL;
            NodePtr new_bucket_current  = ((NodePtr)new_buckets[bucket_idx]);
            while (true) {

                if (new_bucket_current == NULL) {
                    map_bucket_current->next  = NULL;
                    new_bucket_current        = map_bucket_current;
                    new_bucket_previous->next = new_bucket_current;
                    break;
                }
                new_bucket_previous = new_bucket_current;
                new_bucket_current  = new_bucket_previous->next;
            }
            map_bucket_current = map_bucket_current_next;
        }
    }

    free((void*)map->buckets);
    map->buckets  = new_buckets;
    map->capacity = new_cap_t;

    return (MAP_ERROR_RETURN_SUCCESS);
}
