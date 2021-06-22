#ifndef MAP_CREATE
#define MAP_CREATE

#include "defines.h"


struct tile_t{
	int value;
	char symbol;
};

struct ship_t{
	int startx;
	int starty;
	int endx;
	int endy;
	int type;
	int check_type;
	int hit;
	char direction;
};

void print_map(struct tile_t** map);

struct tile_t **create_empty_map();

void position_ship(int* x, int* y, char* direction);

int is_suitable(int x, int y, char direction, int type, struct tile_t** map, int random_flag );

void ships_change(int x, int y, int type, int endx, int endy, char direction);

void place_ship(int x, int y, char direction, int type, struct tile_t** map);

void delete_ship(struct ship_t* ship,  struct tile_t** map);

int check_ship_a(int x, int y, struct tile_t** map);

struct tile_t ** create_map(int player);

struct tile_t** random_map(int player, int mode);

#endif
