/**
 * @file dynarr.h
 * @author Amar Campbell
 * @brief This is the dynamic array declaration header file
 * @copyright Copyright (c) 2026 Amar
 */

#ifndef INCLUDED_DYNARR_H
#define INCLUDED_DYNARR_H
#include <stddef.h>

// Array struct
struct array {
    size_t length;
    size_t capacity;
    size_t element_size;
    void* items;
};

// Aliases
typedef struct array Array;
typedef struct array* ArrayPtr;
typedef int (*Compare)(const void*, const void*);
typedef void (*Function)(void*);
typedef int (*Predicate)(const void*);

// Function Prototypes
/**
 * @brief appends items to the array
 *
 * @param arr pointer to the array
 * @param value Pointer to the value to append
 * @return int - 0 on success or 1 on error
 */
int append(ArrayPtr arr, const void* value);

/**
 * @brief find and remove all element of the array that is equal to value
 *
 * @param arr Pointer to the array
 * @param value pointer to the value to be removed from the array
 * @return int - 0 on success or 1 on error
 */
int remove_item(ArrayPtr arr, const void* value);

/**
 * @brief removes a value from the array at a given index
 *
 * @param arr Pointer to the array
 * @param index the index of the item to be removed from the array
 * @return int - 0 on success or 1 on error
 */
int remove_at(ArrayPtr arr,  size_t index);

/**
 * @brief get the value at a given index from the array
 *
 * @param arr Pointer to the array
 * @param index the position of the item to be return
 * @return void* to the item at the index
 */
void* get(ArrayPtr arr,  size_t index);

/**
 * @brief set the value at a given index of the array to a given value
 *
 * @param arr Pointer to arr
 * @param index the position to set the value to in the array
 * @param value the value to be set at the index
 * @return int - 0 fro success or 1 for error
 */
int set(ArrayPtr arr,  size_t index, const void* value);

/**
 * @brief checks if the array contains a given value
 *
 * @param arr Pointer to the array
 * @param value the value to be checked  for
 * @return int - 0 if the value is found success, negative (-1) if the value is not
 *         found or 1 for error
 */
int contains(ArrayPtr arr, const void* value);

/**
 * @brief Insert a value at a given index, shifting elements right
 *
 * @param arr   Pointer to the array
 * @param index Position to insert at
 * @param value Pointer to the value to insert
 * @return int - 0 on success or 1 on error
 */
int insert_at(ArrayPtr arr,  size_t index, const void* value);

/**
 * @brief reverse  the order of the array
 *
 * @param arr  Pointer to the array
 * @return int - 0 for success or 1 for error
 */
int reverse(ArrayPtr arr);

/**
 * @brief gets the index of the given value in the array
 *
 * @param arr Pointer to the array
 * @param value Pointer to the given value
 * @return int -1 for  error, the index of the value if successfully and -1 if it did
 * not find the value
 */
int index_of(ArrayPtr arr, const void* value);
/**
 * @brief shrink the array capacity to fit the length
 *
 * @param arr Pointer to arr
 * @return int -0 for success or 1 for error
 */
int shrink_to_fit(ArrayPtr arr);

/**
 * @brief
 *
 * @param arr Pointer to the array.
 * @param cmp Function pointer that compares 2 value and return a int.
 *            less than 0 (negative int) if the first element is smaller,
 *            0 if they are equal or 1 if the first element is larger.
 * @return int -0 forsuccess or 1 for error.
 */
int sort(ArrayPtr arr,  Compare cmp);

/**
 * @brief apply the function to each element of the array
 *
 * @param arr Pointer to the array
 * @param fn Function pointer that do something with the value in the array.
 * @return int - 0 for success or 1 for error
 */
int map(ArrayPtr arr,  Function func);

/**
 * @brief creates a new array with elements that pass the predicate
 *
 * @param arr Pointer to array
 * @param pred Function pointer that checks if value pass the predicate.
                0 if true and 1 if not true
 * @return void* Pointer to the new array
 */
ArrayPtr filter(ArrayPtr arr,  Predicate pred);

#endif
