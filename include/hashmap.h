/**
 * @file hashmap.h
 * @author Amar Campbell
 * @brief This is the hashmap declaration header file
 * @copyright Copyright (c) 2026 Amar
 */
#ifndef INCLUDED_HASHMAP
#define INCLUDED_HASHMAP
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define LOAD_FACTOR 0.75

typedef enum {
    MAP_ERROR_RETURN_SUCCESS,
    MAP_ERROR_RETURN_ERROR,
    MAP_ERROR_NOT_FOUND,
    MAP_ERROR_OUT_OF_BOUND,
    MAP_ERROR_EMPTY_BUCKET
} MAP_ERROR_CODES;

struct map {
    size_t element_size;
    size_t length;
    size_t capacity;
    void** buckets;
};

struct node {
    char* key;
    void* value;
    void* next;
};

typedef struct map Map;
typedef Map* MapPtr;
typedef struct node Node;
typedef Node* NodePtr;

/**
 * @brief Create the map
 *
 * @param cap The number of buckets in the map
 * @return pointer to map
 */
MapPtr map_create(size_t cap, size_t element_size);

/**
 * @brief add a node in the map
 *
 * @param map Pointer to the map
 * @param key the skey for the value
 * @param value the value to add
 * @return MAP_ERROR_CODES the enum error codes
 */
MAP_ERROR_CODES map_put(MapPtr map, const char* key, const void* value);

/**
 * @brief get the value base on the key
 *
 * @param map Pointer to the map
 * @param key the key of the value in the map
 * @return void* pointer to the value
 */
void* map_get(MapPtr map, const char* key);

/**
 * @brief remove the node with that key
 *
 * @param map Pointer to the
 * @param key
 * @return MAP_ERROR_CODES the enum error codes
 */
MAP_ERROR_CODES map_remove(MapPtr map, const char* key);

/**
 * @brief check if map contains a node with the key
 *
 * @param map Pointer to the map
 * @param key the key of the node
 * @return true if found
 * @return false if not found
 */
bool map_contains(MapPtr map, const char* key);

/**
 * @brief return the length of the map
 *
 * @param map Pointer to the map
 * @return size_t the length of the  map
 */
inline size_t map_size(MapPtr map) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    return map->length;
}

/**
 * @brief
 *
 * @param map
 * @return true
 * @return false
 */
inline bool map_is_empty(MapPtr map) {
    if (map == NULL) {
        (void)fprintf(stderr, "The Map is null in %s line# %d", __FILE__, __LINE__);
        exit(MAP_ERROR_RETURN_ERROR);
    }

    if (map->length != 0) {
        return false;
    }

    return true;
}

/**
 * @brief Resize the map capacity
 * 
 * @param map Pointer to the map
 * @param new_cap the new capacity
 * @return MAP_ERROR_CODES map error codes
 */
MAP_ERROR_CODES map_resize(MapPtr map,  size_t new_cap);

#endif
