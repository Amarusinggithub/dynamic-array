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
#include <stdint.h>
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
    struct node* next;
};

typedef struct map Map;
typedef Map* MapPtr;
typedef struct node Node;
typedef Node* NodePtr;

static inline char* map_error_to_str(const MAP_ERROR_CODES code) {

    switch (code) {
        case MAP_ERROR_RETURN_SUCCESS:
            return "Success";
        case MAP_ERROR_RETURN_ERROR:
            return "Error";
        case MAP_ERROR_OUT_OF_BOUND:
            return "Out of Bound";
        case MAP_ERROR_NOT_FOUND:
            return "Not Found";
        case MAP_ERROR_EMPTY_BUCKET:
            return "Empty";
        default:
            return "Error code does not Exist";
    }
}

/**
 * @brief Create the map
 *
 * @param cap The number of buckets in the map
 * @return pointer to map
 */
MapPtr map_create(size_t cap, size_t element_size, MAP_ERROR_CODES* err);

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
void* map_get(const Map* map, const char* key, MAP_ERROR_CODES* err);

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
bool map_contains(const Map* map, const char* key, MAP_ERROR_CODES* err);

/**
 * @brief return the length of the map
 *
 * @param map Pointer to the map
 * @return size_t the length of the  map
 */
static inline size_t map_size(const Map* map, MAP_ERROR_CODES* err) {
    if (err == NULL) {
#ifdef DEBUG
        (void)fprintf(stderr, "[%s] The err is null in %s line# %d",
                      map_error_to_str(MAP_ERROR_RETURN_ERROR), __FILE__, __LINE__);
#endif
        return MAP_ERROR_RETURN_ERROR;
    }
    if (map == NULL) {
#ifdef DEBUG
        (void)fprintf(stderr, "[%s] The Map is null in %s line# %d",
                      map_error_to_str(MAP_ERROR_RETURN_ERROR), __FILE__, __LINE__);
#endif
        *err = MAP_ERROR_RETURN_ERROR;
        return (SIZE_MAX);
    }

    *err = MAP_ERROR_RETURN_SUCCESS;
    return map->length;
}

/**
 * @brief
 *
 * @param map
 * @return true
 * @return false
 */
static inline bool map_is_empty(const Map* map, MAP_ERROR_CODES* err) {
    if (err == NULL) {
#ifdef DEBUG
        (void)fprintf(stderr, "[%s] The err is null in %s line# %d",
                      map_error_to_str(MAP_ERROR_RETURN_ERROR), __FILE__, __LINE__);
#endif
        return false;
    }
    if (map == NULL) {
#ifdef DEBUG
        (void)fprintf(stderr, "[%s] The Map is null in %s line# %d",
                      map_error_to_str(MAP_ERROR_RETURN_ERROR), __FILE__, __LINE__);
#endif
        *err = MAP_ERROR_RETURN_ERROR;
        return false;
    }

    if (map->length != 0) {
        *err = MAP_ERROR_RETURN_SUCCESS;
        return false;
    }

    *err = MAP_ERROR_RETURN_SUCCESS;
    return true;
}

/**
 * @brief Resize the map capacity
 *
 * @param map Pointer to the map
 * @param new_cap the new capacity
 * @return MAP_ERROR_CODES map error codes
 */
MAP_ERROR_CODES map_resize(MapPtr map, size_t new_cap);

/**
 * @brief Clear the nodes of the buckets
 *
 * @param map Pointer to the map
 * @return MAP_ERROR_CODES map error codes
 */
MAP_ERROR_CODES map_clear(MapPtr map);

/**
 * @brief Free map
 *
 * @param map Pointer to map
 * @return MAP_ERROR_CODES map error codes
 */
MAP_ERROR_CODES map_free(MapPtr map);

#endif
