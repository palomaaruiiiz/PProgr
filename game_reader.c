/**
 * @brief game reader module
 *
 * @file game_reader.c
 * @author Paloma Ruiz Matesanz
 * @version 2.0
 * @date 22-02-2021
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_reader.h"

STATUS game_load_spaces(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID, north = NO_ID, east = NO_ID, south = NO_ID, west = NO_ID, object= NO_ID;
  Space* space = NULL;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#s:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      north = atol(toks);
      toks = strtok(NULL, "|");
      east = atol(toks);
      toks = strtok(NULL, "|");
      south = atol(toks);
      toks = strtok(NULL, "|");
      west = atol(toks);
      toks = strtok(NULL, "|");
      object = atol(toks);
#ifdef DEBUG
      printf("Leido: %ld|%s|%ld|%ld|%ld|%ld|%ld\n", id, name, north, east, south, west, object);
#endif
      space = space_create(id);
      if (space != NULL) {
	space_set_name(space, name);
	space_set_north(space, north);
	space_set_east(space, east);
	space_set_south(space, south);
	space_set_west(space, west);
  space_set_object(space, object);
	game_add_space(game, space);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}

Space* game_reader_get_space(Game* game, Id id){
  int i = 0;

  if (id == NO_ID) {
    return NULL;
  }

  for (i = 0; game->spaces[i] != NULL; i++) {
    if (id == space_get_id(game->spaces[i])){
      return game->spaces[i];
    }
  }

  return NULL;
}

STATUS game_reader_load_objects(Game* game, char* filename) {
  FILE* file = NULL;
  char line[WORD_SIZE] = "";
  char name[WORD_SIZE] = "";
  char* toks = NULL;
  Id id = NO_ID;
  Object* object = NULL;
  Id spaceId = NO_ID;
  STATUS status = OK;

  if (!filename) {
    return ERROR;
  }

  file = fopen(filename, "r");
  if (file == NULL) {
    return ERROR;
  }

  while (fgets(line, WORD_SIZE, file)) {
    if (strncmp("#o:", line, 3) == 0) {
      toks = strtok(line + 3, "|");
      id = atol(toks);
      toks = strtok(NULL, "|");
      strcpy(name, toks);
      toks = strtok(NULL, "|");
      spaceId = atol(toks);

      printf("Leido: %ld|%s|%ld\n", id, name, spaceId);

      object = object_create(id);
      if (spaceId != NO_ID) {
        object_set_name(object, name);
        object_set_id(object, id);
        space_set_object(game_reader_get_space(game, spaceId), id);
        game_add_object(game, object);
      }
    }
  }

  if (ferror(file)) {
    status = ERROR;
  }

  fclose(file);

  return status;
}
