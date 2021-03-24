/**
 * @brief Provides functionality for id sets
 *
 * @file set.h
 * @author Lucas Piorno Palomo
 * @version 1.0
 * @date 08-03-2021
 * @copyright GNU Public License
 */

#ifndef SET_H
#define SET_H

#include "types.h"
#include <stdlib.h>

#define SET_MAX_SIZE 100

typedef struct _Set Set;

/**
 * @brief Creates a new set and initializes its fiels.
 * @return Returns a pointer to a Set structure.
 **/
Set *set_create();

int set_size(const Set *set);

/**
 * @brief Destroys the given set and deallocates memory.
 *
 * @param set Pointer to the set to be deallocated.
 *
 * @return Returns OK if the set could be destroyed, ERROR otherwise.
 **/
STATUS set_destroy(Set *set);

/**
 * @brief Adds a new Id to the set.
 *
 * @param set Pointer to the set.
 * @param id Id to be added.
 *
 * @return Returns OK if the Id could be added, ERROR otherwise.
 **/
STATUS set_add(Set *set, Id id);

/**
 * @brief Removes an id from the structure.
 *
 * @param set Pointer to the set.
 * @param id Id to be removed
 *
 * @return Returns OK if the id could be removed, ERROR otherwise.
 **/

/* STATUS set_del(Set *set, Id id);*/

STATUS set_del(Set* set, Id id);

Id* set_get_Id(const Set *set);

/**
 * @brief Prints the contents of a set.
 *
 * @param f Pointer to the output file.
 * @param set Pointer to the set to be deallocated.
 *
 * @return Returns OK if the set could be printed, ERROR otherwise.
 **/
STATUS set_print(FILE *f, Set *set);

#endif
