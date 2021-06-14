#ifndef MAP_CREATE
#define MAP_CREATE

#include "defines.h"


struct tile_t{
	int value;
	char symbol;
};

struct tile_t **create_empty_map();

void position_ship(int* x, int* y, char* direction);

int is_suitable(int x, int y, char direction, int type, struct tile_t** map );

void place_ship(int x, int y, char direction, int type, struct tile_t** map);

void delete_ship(int x, int y, struct tile_t** map);

void create_map(int player);


#endif